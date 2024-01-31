#include "CT_RhyTurtle.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "joObject.h"
#include "AttackCollider.h"
#include "Player.h"
#include "DamageNum.h"

float CT_RhyTurtle::m_fRespawnTime = 0.f;
HDC CT_RhyTurtle::m_Pixel = nullptr;

CT_RhyTurtle::CT_RhyTurtle()
	: m_eState(State::End)
	, m_bRight(true)
	, m_fStateTime(0.f)
	, m_fNowTime(0.f)
	, m_fSpeed(0.f)
{
}

CT_RhyTurtle::~CT_RhyTurtle()
{
}

void CT_RhyTurtle::Initialize()
{
	m_iMaxHp = 500000;
	m_iHp = m_iMaxHp;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(150.f, 87.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetUseGravity(false);

	m_vAttackCollOffset = Vec2(104.f, 0.f);

	m_pAttackColl = Instantiate<AttackCollider>(eLayerType::LT_MONSTER_EFFECT);
	m_pAttackColl->SetOwner(this);
	m_pAttackColl->SetCollisionSize(Vec2(80.f, 50.f));
	m_pAttackColl->SetCollisionOnOff(true);
	m_pAttackColl->SetCollisionOffset(m_vAttackCollOffset);

	m_fSpeed = 120.f;

	JoTexture* pLeftTex = ResourceMgr::Find<JoTexture>(L"CT_RhyTurtle_L");
	JoTexture* pRightTex = ResourceMgr::Find<JoTexture>(L"CT_RhyTurtle_R");

	m_pAnimator->CreateAnimation(L"Turtle_Idle_L", pLeftTex, Vec2(0.f, 0.f), Vec2(148.f, 87.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Turtle_Idle_R", pRightTex, Vec2(0.f, 0.f), Vec2(148.f, 87.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Turtle_Move_L", pLeftTex, Vec2(148.f * 6.f, 0.f), Vec2(148.f, 87.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Turtle_Move_R", pRightTex, Vec2(148.f * 6.f, 0.f), Vec2(148.f, 87.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Turtle_Attack_L", pLeftTex, Vec2(0.f, 88.f), Vec2(268.f, 105.f), Vec2(-28.f, -4.f), 11, 0.15f);
	m_pAnimator->CreateAnimation(L"Turtle_Attack_R", pRightTex, Vec2(0.f, 88.f), Vec2(268.f, 105.f), Vec2(28.f, -4.f), 11, 0.15f);
	m_pAnimator->CreateAnimation(L"Turtle_Dead_L", pLeftTex, Vec2(0.f, 192.f), Vec2(272.f, 234.f), Vec2(38.f, -22.f), 15, 0.1f);
	m_pAnimator->CreateAnimation(L"Turtle_Dead_R", pRightTex, Vec2(0.f, 192.f), Vec2(272.f, 234.f), Vec2(-38.f, -22.f), 15, 0.1f);

	Events* pEvent_Attack_L = m_pAnimator->GetEvents(L"Turtle_Attack_L");
	pEvent_Attack_L->frameEvents[6] = bind(&AttackCollider::SetHitOn, m_pAttackColl);
	pEvent_Attack_L->frameEvents[9] = bind(&AttackCollider::SetHitOff, m_pAttackColl);
	pEvent_Attack_L->EndEvent = bind(&CT_RhyTurtle::SetState_Move, this);
	Events* pEvent_Attack_R = m_pAnimator->GetEvents(L"Turtle_Attack_R");
	pEvent_Attack_R->frameEvents[6] = bind(&AttackCollider::SetHitOn, m_pAttackColl);
	pEvent_Attack_R->frameEvents[9] = bind(&AttackCollider::SetHitOff, m_pAttackColl);
	pEvent_Attack_R->EndEvent = bind(&CT_RhyTurtle::SetState_Move, this);

	Events* pEvent_Dead_L = m_pAnimator->GetEvents(L"Turtle_Dead_L");
	pEvent_Dead_L->EndEvent = bind(&CT_RhyTurtle::SetState_Respawn, this);
	Events* pEvent_Dead_R = m_pAnimator->GetEvents(L"Turtle_Dead_R");
	pEvent_Dead_R->EndEvent = bind(&CT_RhyTurtle::SetState_Respawn, this);

	m_fStateTime = 1.f;
	SetState_Idle();
}

void CT_RhyTurtle::Update()
{
	switch (m_eState)
	{
	case CT_RhyTurtle::State::Respawn:
		Respawn();
		break;
	case CT_RhyTurtle::State::Idle:
		Idle();
		break;
	case CT_RhyTurtle::State::Move:
		Move();
		break;
	case CT_RhyTurtle::State::Attack:
		Attack();
		break;
	case CT_RhyTurtle::State::Dead:
		Dead();
		break;
	}

	m_pRigidbody->Update();
	m_pAnimator->Update();
}

void CT_RhyTurtle::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}


void CT_RhyTurtle::OnCollisionStay(Collider* _pOther)
{
	Player* _pPlayer = dynamic_cast<Player*>(_pOther->GetOwner());
	if (_pPlayer)
	{
		HitInfo _info = { 300, 1 };
		_pPlayer->Hit(_info);
	}
}

void CT_RhyTurtle::Hit(const HitInfo& _hitInfo)
{
	AddHp(-_hitInfo.iDamage);
	DamageNum* pDNum = Instantiate<DamageNum>(eLayerType::LT_UI);
	pDNum->Init_Number(std::to_string(_hitInfo.iDamage));
	pDNum->SetCritical(_hitInfo.bCritical);

	Vec2 vRenderPos = GetPos();
	JoTexture* pDamageTex = pDNum->GetDamageTex();
	vRenderPos.y -= float(pDamageTex->GetHeight()) * 0.5f * _hitInfo.iHitCount;

	pDNum->SetPos(vRenderPos);
}

void CT_RhyTurtle::Idle()
{
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_fNowTime >= m_fStateTime)
	{
		SetState_Move();
	}
		
}

void CT_RhyTurtle::Move()
{
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_fNowTime >= m_fStateTime)
	{
		SetState_Idle();
	}
	
	Check_RightLeft();
}

void CT_RhyTurtle::Attack()
{

}

void CT_RhyTurtle::Dead()
{
	
}

void CT_RhyTurtle::Respawn()
{
	static float m_fNowTime = 0.f;

	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= m_fRespawnTime)
	{
		m_fNowTime = 0.f;
		m_bRight = false;
		SetPos(m_vRespawnPos);

		m_pAttackColl->SetCollisionOnOff(true);
		m_pCollider->SetCollisionActive();
		m_iHp = m_iMaxHp;
		SetState_Idle();
	}
}

void CT_RhyTurtle::SetState_Idle()
{
	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_fStateTime = float(rand() % 2 + 1);
	m_fNowTime = 0.f;

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Turtle_Idle_R", true);
	else
		m_pAnimator->PlayAnimation(L"Turtle_Idle_L", true);

	m_eState = State::Idle;
}

void CT_RhyTurtle::SetState_Move()
{
	m_fStateTime = float(rand() % 4 + 1);
	m_fNowTime = 0.f;

	if (m_bRight)
	{
		m_pAnimator->PlayAnimation(L"Turtle_Move_R", true);
		m_pRigidbody->SetVelocity(Vec2(m_fSpeed, 0.f));
	}	
	else
	{
		m_pAnimator->PlayAnimation(L"Turtle_Move_L", true);
		m_pRigidbody->SetVelocity(Vec2(-m_fSpeed, 0.f));
	}
		
	m_eState = State::Move;
}

void CT_RhyTurtle::SetState_Attack()
{
	if (m_eState == State::Attack)
		return;

	SoundMgr::Play(L"Rhyno_Attack");
	m_pRigidbody->SetVelocity(Vec2::Zero);

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Turtle_Attack_R", false);
	else
		m_pAnimator->PlayAnimation(L"Turtle_Attack_L", false);

	m_eState = State::Attack;
}

void CT_RhyTurtle::SetState_Dead()
{
	if (m_eState == State::Dead)
		return;
	Enemy::SetState_Dead();
	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_pAttackColl->SetCollisionOnOff(false);
	m_pCollider->SetCollisionInactive();

	SoundMgr::Play(L"Rhyno_Die");

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Turtle_Dead_R", false);
	else
		m_pAnimator->PlayAnimation(L"Turtle_Dead_L", false);

	m_eState = State::Dead;
}

void CT_RhyTurtle::SetState_Respawn()
{
	if (m_eState == State::Respawn)
		return;
	m_pAnimator->SetActiveAnim(nullptr);
	m_eState = State::Respawn;
}
void CT_RhyTurtle::Check_RightLeft()
{
	int iOffset = m_bRight ? 1 : -1;
	Vec2 vPos = GetPos();
	COLORREF color = GetPixel(m_Pixel, (int)vPos.x + iOffset, (int)vPos.y);

	if (color == RGB(255, 125, 0))
	{
		if (m_bRight)
		{
			SetPos(vPos);
			m_bRight = false;
			m_pAnimator->PlayAnimation(L"Turtle_Move_L", true);
			m_pRigidbody->SetVelocity(Vec2(-m_fSpeed, 0.f));
			m_pAttackColl->SetCollisionOffset(-m_vAttackCollOffset);
		}
		else
		{
			SetPos(vPos);
			m_bRight = true;
			m_pAnimator->PlayAnimation(L"Turtle_Move_R", true);
			m_pRigidbody->SetVelocity(Vec2(m_fSpeed, 0.f));
			m_pAttackColl->SetCollisionOffset(m_vAttackCollOffset);
		}

		m_fStateTime += 1.f;
	}
}
