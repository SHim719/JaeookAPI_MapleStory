#include "Skill_Obj.h"
#include "Enemy.h"

Skill_Obj::Skill_Obj()
	: m_pOwner{}
	, m_pSkillTex(nullptr)
	, m_pHitEffect(nullptr)
	, m_vOffset{}
	, m_iMaxEnemyCount(0)
	, m_iMaxHitCount(0)
	, m_iPerHitCount(0)
	, m_vecAttInfo{}
{
}

Skill_Obj::~Skill_Obj()
{
}

Vec2 Skill_Obj::GetOverlappedRectPos(Collider* other) const
{
	Vec2 vSize = m_pCollider->GetSize();
	Vec2 vPos = GetPos();
	vPos += m_pCollider->GetOffset();

	Vec2 vOtherSize = other->GetSize();
	Vec2 vOtherPos = other->GetOwner()->GetPos();
	vOtherPos += other->GetOffset();

	float fLeftPos = vPos.x - vSize.x * 0.5f;
	float fRightPos = vPos.x + vSize.x * 0.5f;

	float fOtherLeftPos = vOtherPos.x - vOtherSize.x * 0.5f;
	float fOtherRightPos = vOtherPos.x + vOtherSize.x * 0.5f;

	float fTopPos = vPos.y - vSize.y * 0.5f;
	float fBottomPos = vPos.y + vSize.y * 0.5f;

	float fOtherTopPos = vOtherPos.y - vOtherSize.y * 0.5f;
	float fOtherBottomPos = vOtherPos.y + vOtherSize.y * 0.5f;

	float fFinalLeft = max(fLeftPos, fOtherLeftPos);
	float fFinalRight = min(fRightPos, fOtherRightPos);
	float fFinalTop = max(fTopPos, fOtherTopPos);
	float fFinalBottom = min(fBottomPos, fOtherBottomPos);

	Vec2 vMidPos = { (fFinalLeft + fFinalRight) * 0.5f, (fFinalTop + fFinalBottom) * 0.5f };

	Vec2 vOffset = { float(rand() % 100 - 50), float(rand() % 100 - 50) };

	return vMidPos + vOffset;
}

void Skill_Obj::push_AttackInfo(Collider* _pOther)
{
	if (m_vecAttInfo.size() >= m_iMaxEnemyCount) return;
	if (false == _pOther->GetOwner()->IsActive())
		return;

	AttackInfo info{};
	info.pHitObj = dynamic_cast<Enemy*>(_pOther->GetOwner());

	if (info.pHitObj == nullptr)
		return;

	int iHitCount = m_iMaxHitCount / m_iPerHitCount;
	for (int i = 0; i < iHitCount; ++i)
		info.vecEffectPos.push_back(GetOverlappedRectPos(_pOther));

	info.iHitCount = 0;
	info.fNowTime = 100.f;

	m_vecAttInfo.push_back(info);
}
