#include "Scene_Title.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "BackGround.h"
#include "Player.h"
#include "UIMgr.h"
#include "joObject.h"
#include "Title_Button.h"
#include "Camera.h"

Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Initialize()
{
	UIMgr::SetCanUseUI(false);
	BackGround* m_pTitleScreen = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"TitleScreen");
	m_pTitleScreen->SetBgTex(pBGTex);

	float texWidth = (float)pBGTex->GetWidth();
	float texHeight = (float)pBGTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);
	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	Player* m_pPlayer = new Player;
	m_pPlayer->Initialize();
	s_pMainPlayer = m_pPlayer;
	m_pPlayer->SetPos({ 1141.f, 851.f });

	Instantiate<Title_Button>(eLayerType::LT_UI)->SetPos({ 500.f, 450.f });

	SoundMgr::Play(L"TitleBGM");
}

void Scene_Title::OnEnter()
{
}

void Scene_Title::OnExit()
{
	Release();
	SoundMgr::Stop(L"TitleBGM");
}
