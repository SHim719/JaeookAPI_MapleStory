#include "Scene_Eagle_Prev.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "Totem_Player.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Frieto.h"

Scene_Eagle_Prev::Scene_Eagle_Prev()
{
}

Scene_Eagle_Prev::~Scene_Eagle_Prev()
{
}

void Scene_Eagle_Prev::Initialize()
{
	m_vLimitPosX.x = 0.f;
	m_vLimitPosX.y = 1349.f;

	//Totem_Pixel
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_������");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"BG_������_Pixel")->Get_BmpDC();

	float texWidth = (float)pBGTex->GetWidth();
	float texHeight = (float)pBGTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	Frieto* pFrieto = Instantiate<Frieto>(eLayerType::LT_NPC);
}

void Scene_Eagle_Prev::OnEnter()
{
	//��׽ý� bgm
	SoundMgr::Play(L"HenesysBGM");
	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);
}

void Scene_Eagle_Prev::OnExit()
{
	SoundMgr::Stop(L"HenesysBGM");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
