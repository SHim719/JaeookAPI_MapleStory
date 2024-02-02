#include "Esfesia.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "QuestMgr.h"
#include "SceneMgr.h"
#include "ItemDatabase.h"
#include "Item_Obj.h"
#include "joObject.h"

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
	SetPos({ 1272.f, 581.f });

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
	m_vecDials.push_back({ L"����?" , 0 });
	m_vecDials.push_back({ L"���� ����� ���� ���۵��� �ʹ� ����.�ʰ� �� �ϼ��� ������." , 1 });
	m_vecDials.push_back({ L"�׷� �˰ھ�." , 0 });
	m_vecDials.push_back({ L"�� ������ ����! �׷��ϱ� 30�� ������ ��Ź�Ұ�." , 1 });
	m_vecDials.push_back({ L"���������α�.." , 0 });

	m_vecDials2.push_back({ L"�����̾�?" , 1 });

	m_vecDials3.push_back({ L"����. �� ���п� ���� �پ���.", 1 });
	m_vecDials3.push_back({ L"�������� �÷��� ��ǥ�� �ٰ�! ������ �� ��Ź��^^", 1 });
	m_vecDials3.push_back({ L"(..���� ���⸦ �����߰ڴ�.)", 0 });
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

		if (m_eState != Esfesia_State::End)
		{
			Quest* _pQuest = QuestMgr::Get_NowQuest();
			if (_pQuest)
			{
				if (_pQuest->IsSatisfied())
				{
					_pQuest->Set_Clear(true);
					m_eState = Esfesia_State::Third;
				}
					
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
				case Esfesia_State::First:
					First(pDialBox);
					break;
				case Esfesia_State::Second:
					Second(pDialBox);
					break;
				case Esfesia_State::Third:
					Third(pDialBox);
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
	m_pAnimator->Render();
}

void Esfesia::Release()
{
}

bool Esfesia::Check_Rect()
{
	Vec2 vMousePos = KeyMgr::GetWorldMousePos();

	if (vMousePos.x >= m_tRect.left
		&& vMousePos.y >= m_tRect.top
		&& vMousePos.x <= m_tRect.right
		&& vMousePos.y <= m_tRect.bottom)
	{
		return true;
	}

	return false;
}

void Esfesia::First(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(ChangeScene_ToGame);

	if (QuestMgr::Get_NowQuest() == nullptr)
	{
		Quest* pQuest = new Quest;
		pQuest->Set_QuestNumber(3);
		QuestMgr::Set_NowQuest(pQuest);
	}

	m_eState = Esfesia_State::Second;
}

void Esfesia::Second(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials2);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(ChangeScene_ToGame);
}

void Esfesia::Third(MyDialogBox* _pBox)
{
	_pBox->SetActive(true);
	_pBox->Set_Dialog(&m_vecDials3);
	_pBox->Set_NpcTex(m_pDialTex);
	_pBox->Set_NpcNameTex(m_pDialNameTex);
	_pBox->Set_Function(bind(&Esfesia::Drop_Item, this));
}

void Esfesia::Drop_Item()
{
	Item* pItem = ItemDatabase::FindItemData(L"�÷��� ��ǥ");
	Item_Obj* pObj = Instantiate<Item_Obj>(eLayerType::LT_ITEM);
	pObj->SetPos(GetPos());
	pObj->SetItem(pItem);
	pObj->SetCount(1);
	SoundMgr::Play(L"Release_Item");
	m_eState = Esfesia_State::End;
}
