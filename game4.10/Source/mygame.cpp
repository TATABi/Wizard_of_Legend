#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "UI.h"
#include "Items.h"
#include "PausedMenu.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g) : CGameState(g) {}

	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);	// 一開始的loading進度為0%

		//載入音效
		CAudio::Instance()->Load(AUDIO_TITLE, "sounds\\TitleBGM.wav");
		CAudio::Instance()->Load(AUDIO_BE, "sounds\\be.mp3");
		CAudio::Instance()->Load(AUDIO_PULL, "sounds\\pull.mp3");
		CAudio::Instance()->Load(AUDIO_PUTTING, "sounds\\putting.mp3");
		CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");
		CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");
		CAudio::Instance()->Load(AUDIO_ARRIVAL, "sounds\\arrival.mp3");
		CAudio::Instance()->Load(AUDIO_PULL2, "sounds\\pull2.mp3");
		CAudio::Instance()->Load(AUDIO_LEVEL_FIRE, "sounds\\FireBGM.wav");
		CAudio::Instance()->Load(AUDIO_TOWN, "sounds\\TownBGM.wav");
		CAudio::Instance()->Load(AUDIO_BUY, "sounds\\buy.mp3");
		CAudio::Instance()->Load(AUDIO_NOMONEY, "sounds\\nomoney.mp3");
		CAudio::Instance()->Load(AUDIO_GET_MONEY, "sounds\\getMoney.mp3");
		CAudio::Instance()->Load(AUDIO_GET_BLOOD_BALL, "sounds\\getBloodBall.mp3");
		CAudio::Instance()->Load(AUDIO_SKILL_WIND, "sounds\\skillWind.mp3");
		CAudio::Instance()->Load(AUDIO_SKILL_ICE, "sounds\\skillIce.mp3");
		CAudio::Instance()->Load(AUDIO_SKILL_NOVA, "sounds\\skillNova.mp3");
		CAudio::Instance()->Load(AUDIO_HIT_ENEMY, "sounds\\hitEnemy.mp3");
		CAudio::Instance()->Load(AUDIO_BUFF, "sounds\\buff.mp3");
		CAudio::Instance()->Load(AUDIO_SLIME_DEAD, "sounds\\slimeDead.mp3");
		CAudio::Instance()->Load(AUDIO_SLIME_ATTACK, "sounds\\slimeAttack.mp3");
		CAudio::Instance()->Load(AUDIO_BLACK_MAN_ATTACK, "sounds\\blackManAttack.mp3");
		CAudio::Instance()->Load(AUDIO_BLACK_MAN_DEAD, "sounds\\blackManDead.mp3");
		CAudio::Instance()->Load(AUDIO_BOSS_DEAD, "sounds\\bossDead.mp3");
		CAudio::Instance()->Load(AUDIO_BOSS_ATTACK, "sounds\\bossAttack.mp3");
		CAudio::Instance()->Load(AUDIO_BOSS_INVISIBLE, "sounds\\bossDead.mp3");
		ShowInitProgress(30);
		
		//controller初始化
		_controller.Initialize();
		Items::Instance().LoadBitmap();
		Character::Instance().LoadBitmap();
		PausedMenu::Instance().LoadBitmap();
		Bag::Instance().LoadBitmap();
		UI::Instance().LoadBitmap();

		ShowInitProgress(80);
	}

	void CGameStateInit::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateInit::OnShow()
	{
		_controller.OnShow();

		//切換State
		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g) : CGameState(g) {}

	CGameStateOver::~CGameStateOver() {}

	void CGameStateOver::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateOver::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateOver::OnInit() 
	{
		_controller.Initialize();
	}

	void CGameStateOver::OnShow()
	{
		_controller.OnShow();
		
		//切換State
		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}

	void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Home
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Home::CGameStateRun_Home(CGame *g) : CGameState(g) {}

	CGameStateRun_Home::~CGameStateRun_Home() {}

	void CGameStateRun_Home::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Home::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Home::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Home::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Home::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Home::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Home::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Home::OnShow()
	{
		_controller.OnShow();

		//切換State
		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}

	/////////////////////////////////////////////////////////////////////////////
	////Town
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Town::CGameStateRun_Town(CGame *g) : CGameState(g) {}

	CGameStateRun_Town::~CGameStateRun_Town() {}

	void CGameStateRun_Town::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Town::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Town::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Town::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Town::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Town::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Town::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Town::OnShow()
	{
		_controller.OnShow();

		//切換State
		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}

	/////////////////////////////////////////////////////////////////////////////
	////Level 1
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Level_1::CGameStateRun_Level_1(CGame *g) : CGameState(g) {}

	CGameStateRun_Level_1::~CGameStateRun_Level_1() {}

	void CGameStateRun_Level_1::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Level_1::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Level_1::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Level_1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Level_1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Level_1::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Level_1::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Level_1::OnShow()
	{
		_controller.OnShow();

		//切換State
		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}
}
