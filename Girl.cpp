#include "Girl.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "MyDialogBox.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "SceneMgr.h"


Girl::Girl()
	: m_pTexture(nullptr)
	, m_pDialNameTex(nullptr)
	, m_pDialTex(nullptr)
	, m_pNameBarTex(nullptr)
	, m_vecDials{}
	, m_tRect{}
	, m_eState(Girl_State::End)
	, m_pInventory(nullptr)
	, m_pToken(nullptr)
{ 
}

Girl::~Girl()
{
}

void Girl::Initialize()
{
	m_pToken = ItemDatabase::FindItemData(L"�÷��� ��ǥ");

	m_pTexture = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(99.f, 114.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	m_pDialNameTex = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�_�̸�");
	m_pDialTex = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�_��ȭ");
	m_pNameBarTex = ResourceMgr::Find<JoTexture>(L"�ǹ��� �ҳ�_Bar");

	SetPos({ 1241.f, 813.f });

	m_tRect.left = LONG(GetPos().x - 99.f);
	m_tRect.right = LONG(GetPos().x + 99.f);
	m_tRect.top = LONG(GetPos().y - 114.f);
	m_tRect.bottom = LONG(GetPos().y + 114.f);

	m_vecDials.push_back({ L"����..?", 0 });
	m_vecDials.push_back({ L"�� ������? ���⿡ ��� ���Ծ�?", 1 });
	m_vecDials.push_back({ L"�����ǿ�忡�� ���� ��Ŵٰ� � ���ۿ� �����µ� ����� ���ϴ� �����̿���.", 0 });
	m_vecDials.push_back({ L"�׷�����. �׷��� ����� �ڷ����� ���� �� ����.", 1 });
	m_vecDials.push_back({ L"��?", 0 });
	m_vecDials.push_back({ L"����� ���� �����̾�. ���� ������ �̿��ؼ� �ٱ����� ������ �� �־�.", 1 });
	m_vecDials.push_back({ L"�� �׷�? �׷� � ���� ��������.", 0 });
	m_vecDials.push_back({ L"�װ�..", 1 });
	m_vecDials.push_back({ L"���� ���ڰԵ� ������ ���� ������ �� �� ���¾�.", 1 });
	m_vecDials.push_back({ L"??.. �׷� ���� ������ ���� ȸ���Ǵµ�?", 0 });
	m_vecDials.push_back({ L"�������κ��� ���� �ῡ ��� 1000������ ���ϰŶ�� ������..", 1 });
	m_vecDials.push_back({ L"��?? �׷� ������ ���⼭ �ľ� ������� �ž�?", 0 });
	m_vecDials.push_back({ L"����� �־�.", 1 });
	m_vecDials.push_back({ L"���� 4���� ��Ż�� ������? ��Ż�� ����� ������ �÷��� ��ǥ�� ȹ���ؼ� ������ ������ �����.", 1 });
	m_vecDials.push_back({ L"�� ��ǥ�� ������ �ָ�?", 0 });
	m_vecDials.push_back({ L"���� �� ��ǥ�� ������ �̿��� �ʸ� ������ ������ �� �־�.", 1 });
	m_vecDials.push_back({ L"���⼭ �ľ����� �� �����ϱ� �� ����ۿ� ���°ǰ�..", 0 });
	m_vecDials.push_back({ L"�˾Ҿ�. �ʿ��� ��ǥ�� ������ �ٰ�.", 0 });
	m_vecDials.push_back({ L"������ ��Ż�� �̰�� ����Ǿ� �־�. �װ��� � ������� ���縮�� ������ ����. ������.", 1 });

	m_vecDials2.push_back({ L"���� ��ǥ 4���� ������ �ʾҾ�.", 1 });

	m_vecDials3.push_back({ L"��ǥ 4���� ��� �Ծ�!", 0 });
	m_vecDials3.push_back({ L"����߾�. ��ǥ�� ���� �̿��ؼ� �ʸ� �ٱ����� �����ٰ�.", 1 });
	m_vecDials3.push_back({ L"���� ���� �����ִ� ��", 0 });


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
				if (m_eState == Girl_State::Second)
				{
					if (m_pInventory->FindItem(m_pToken) == 4)
						Set_End();
				}
				SoundMgr::Play(L"Bt_Click");
				pDialBox->SetActive(true);
				pDialBox->Set_NpcTex(m_pDialTex);
				pDialBox->Set_NpcNameTex(m_pDialNameTex);

				switch (m_eState)
				{
				case Girl::Girl_State::First:
					First(pDialBox);
					break;
				case Girl::Girl_State::Second:
					Second(pDialBox);
					break;
				case Girl::Girl_State::End:
					End(pDialBox);
					break;
				}
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
	
	Vec2 vPos = GetPos();
	vPos = Camera::CalcRenderPos(vPos);

	vPos.y += 70.f;
	RenderMgr::RenderImage(m_pNameBarTex,
		vPos.x - m_pNameBarTex->GetWidth() * 0.5f, vPos.y - m_pNameBarTex->GetHeight() * 0.5f
		, vPos.x + m_pNameBarTex->GetWidth() * 0.5f, vPos.y + m_pNameBarTex->GetHeight() * 0.5f);
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

void Girl::First(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials);
	pDialBox->Set_Function(bind(&Girl::Set_Second, this));
}

void Girl::Second(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials2);
}

void Girl::End(MyDialogBox* pDialBox)
{
	pDialBox->Set_Dialog(&m_vecDials3);
	pDialBox->Set_Function(bind(&Girl::Change_Scene_Title, this));
}

void Girl::Change_Scene_Title()
{
	SoundMgr::Play(L"Light");
	SceneMgr::Reservation_ChangeScene(L"Scene_Title", Vec2(-1.f, -1.f));
}

