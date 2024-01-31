#include "Esfesia.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"

Esfesia::Esfesia()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_vecDials{}
	, m_vecDials2{}
	, m_tRect{}
	, m_bSuccessed(false)
	, m_eState(Esfesia_State::First)
	, ChangeScene_ToGame(nullptr)
{
}

Esfesia::~Esfesia()
{
}

void Esfesia::Initialize()
{
	SetPos({ 993.f, 608.f });

	m_pTexture = ResourceMgr::Find<JoTexture>(L"������þ�");
	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"������þ�_�̸�");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"������þ�_��ȭ");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(72.f, 82.f), Vec2::Zero, 6, 0.2f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	ChangeScene_ToGame = [&]() ->void {  SceneMgr::Reservation_ChangeScene(L"Scene_Totem", { -100.f, -100.f }); };

	m_tRect.left = LONG(GetPos().x - 36.f);
	m_tRect.right = LONG(GetPos().x + 36.f);
	m_tRect.top = LONG(GetPos().y - 41.f);
	m_tRect.bottom = LONG(GetPos().y + 41.f);

	m_vecDials.push_back({ L"�ű� ��! �� �� �����ֶ�!" , 1 });
	m_vecDials.push_back({ L"����?." , 0 });
	m_vecDials.push_back({ L"���� ����� ���� ���۵��� �ʹ� ����.�ʰ� �� �ϼ���\n������." , 1 });
	m_vecDials.push_back({ L"�׷� �˰ھ�." , 0 });
	m_vecDials.push_back({ L"�� ������ ����! �׷��ϱ� 40�� ������ ��Ź�Ұ�." , 1 });
	m_vecDials.push_back({ L"���������α�.." , 0 });

	m_vecDials2.push_back({ L"�ٽ� �����Ұ�." , 0 });
	m_vecDials2.push_back({ L"�����غ�!" , 1 });
}

void Esfesia::Update()
{
	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsActiveUIs())
			return;
		MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
		if (pDialBox == nullptr || pDialBox->IsActive())
			return;

		if (m_eState != Frieto_State::End)
		{
			Quest* _pQuest = QuestMgr::Get_NowQuest();
			if (_pQuest)
			{
				if (_pQuest->IsSatisfied())
					m_eState = Frieto_State::End;
			}
		}

		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Rect();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				SoundMgr::Play(L"Bt_Click");
				switch (m_eState)
				{
				case Frieto_State::First:
					First(pDialBox);
					break;
				case Frieto_State::Second:
					Second(pDialBox);
					break;
				case Frieto_State::End:
					break;
				}
			}
		}
	}

	m_pAnimator->Update();
}

void Esfesia::LateUpdate()
{
}

void Esfesia::Render()
{
}

void Esfesia::Release()
{
}

bool Esfesia::Check_Rect()
{
	return false;
}

void Esfesia::First(MyDialogBox* _pBox)
{
}

void Esfesia::Second(MyDialogBox* _pBox)
{
}

void Esfesia::End(MyDialogBox* _pBox)
{
}
