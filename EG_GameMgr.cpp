#include "EG_GameMgr.h"
#include "TimeMgr.h"
#include "Counting.h"
#include "joObject.h"
#include "Success.h"
#include "Fail.h"
#include "TimerUI.h"
#include "SoundMgr.h"
#include "QuestMgr.h"

EG_GameMgr::EG_GameMgr()
	: m_pTimerUI(nullptr)
{
}

EG_GameMgr::~EG_GameMgr()
{
}

void EG_GameMgr::Initialize()
{
	m_iMaxBaldCnt = 10;
	m_iBaldCnt = m_iMaxBaldCnt;
	m_iMaxEagleCnt = 10;
	m_iEagleCnt = m_iMaxEagleCnt;
	m_eGameState = GameState::Start;
	m_bSuccess = false;
	m_bFail = false;

	Instantiate<Counting>(eLayerType::LT_UI)->SetPos({ 500.f, 400.f } );
}

void EG_GameMgr::Update()
{
	switch (m_eGameState)
	{
	case GameState::Start:
		StartGame();
		break;
	case GameState::Loop:
		LoopGame();
		break;
	case GameState::End:
		EndGame();
		break;
	}
}

void EG_GameMgr::StartGame()
{
	static float fNowTime = 0.f;

	fNowTime += TimeMgr::DeltaTime_NoScale();

	if (fNowTime >= 3.f)
	{
		fNowTime = 0.f;
		TimeMgr::SetTimeScale(1.f);
		SoundMgr::Play(L"Nautilus");
		m_eGameState = GameState::Loop;
	}
}

void EG_GameMgr::LoopGame()
{
	if (m_iBaldCnt == m_iMaxBaldCnt - 3)
	{
		m_bFail = true;
		Instantiate<Fail>(eLayerType::LT_UI)->SetPos({ 500.f, 350.f });
		m_eGameState = GameState::End;
		return;
	}

	if (m_iEagleCnt == 0)
	{
		m_bSuccess = true;
		Instantiate<Success>(eLayerType::LT_UI)->SetPos({ 500.f, 350.f } );
		m_eGameState = GameState::End;
		QuestMgr::Get_NowQuest()->Set_Satisfied(true);
		return;
	}

	if (m_pTimerUI->GetTime() <= 0.f)
	{
		m_bFail = true;
		Instantiate<Fail>(eLayerType::LT_UI)->SetPos({ 500.f, 350.f });
		m_eGameState = GameState::End;
		return;
	}
}


void EG_GameMgr::EndGame()
{
	static float fNowTime = 0.f;

	fNowTime += TimeMgr::DeltaTime_NoScale();

	if (fNowTime >= 3.f)
	{
		fNowTime = 0.f;
		SceneMgr::Reservation_ChangeScene(L"Scene_Eagle_Prev", Vec2(137.f, 117.f));
	}

	// Scene out
}
