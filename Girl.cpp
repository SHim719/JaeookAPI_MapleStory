#include "Girl.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"

Girl::Girl()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_vecDials{}
	, m_tRect{}
{ 
}

Girl::~Girl()
{
}

void Girl::Initialize()
{
	m_pTexture = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(99.f, 114.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�_�̸�");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�_��ȭ");

	SetPos({ 1241.f, 813.f });

	m_tRect.left = LONG(GetPos().x - 99.f);
	m_tRect.right = LONG(GetPos().x + 99.f);
	m_tRect.top = LONG(GetPos().y - 114.f);
	m_tRect.bottom = LONG(GetPos().y + 114.f);

	//m_vecDials.push_back({ L"���� �ִ� �÷��� Ŭ�����ϸ� ������ ��" , 1 });
	//m_vecDials.push_back({ L"�����ٶ� ���ٻ������\nīŸ���� ������\n��ȸ�ϰ��־�� �츮 ������ �� �� ���� ������ ������ �����ڰ� ���� �ع����ž�" , 0 });

}

void Girl::Update()
{
	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsActiveUIs())
			return;
		MyDialogBox* pDialBox = UIMgr::Get_UI_Instance<MyDialogBox>(UI_Enums::UI_Dialog);
		if (pDialBox == nullptr || pDialBox->IsActive())
			return;

		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Rect();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				SoundMgr::Play(L"Bt_Click");
				pDialBox->SetActive(true);
				pDialBox->Set_Dialog(&m_vecDials);
				pDialBox->Set_NpcTex(m_pDialTex);
				pDialBox->Set_NpcNameTex(m_pDialNameTex);
			}
		}

	}

	m_pAnimator->Update();
}

void Girl::LateUpdate()
{
}

void Girl::Render()
{
	m_pAnimator->Render();
}

void Girl::Release()
{
}

bool Girl::Check_Rect()
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
