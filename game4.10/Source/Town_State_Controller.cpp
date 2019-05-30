#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Town_State_Controller.h"
#include "GameData.h"

namespace game_framework {

	Town_State_Controller::Town_State_Controller() :Controller(), _map(TOWN_CHARACTER_XY[0], TOWN_CHARACTER_XY[1], &Global_Class::g_character), _item_store(TOWN_STORE_XY[0], TOWN_STORE_XY[1]){}

	void Town_State_Controller::Begin()
	{
		_game_state_num = -1;
		_isSwitch = false;
		_delayCounter = 30 * 1; // 1 seconds
		_map.Initialize(TOWN_CHARACTER_XY[0], TOWN_CHARACTER_XY[1]);
		_character->Initialize(_map.GetCharacterPosition());
		_flag = FLAG_TOWN_NORMAL;
		Global_Class::g_character.Initialize(_map.GetCharacterPosition());

		CAudio::Instance()->Stop(AUDIO_HOME);
		CAudio::Instance()->Play(AUDIO_TOWN, true);

		//////產生隨機道具/////
		_item_store.Shelf(&Items::Instance());
	}

	void Town_State_Controller::Initialize()
	{
		_character = &Global_Class::g_character;
		_pauseMenu = &Global_Class::g_pauseMenu;
		_bag = &Global_Class::g_bag;

		CAudio::Instance()->Load(AUDIO_TOWN, "sounds\\TownBGM.wav");
		CAudio::Instance()->Load(AUDIO_BUY, "sounds\\buy.mp3");
		CAudio::Instance()->Load(AUDIO_NOMONEY, "sounds\\nomoney.mp3");

		_bm_loading.LoadBitmap(LOADING);
		_map.LoadBitmap();
		_item_store.LoadBitmap();
	}

	void Town_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_DOWN || nChar == KEY_S)
			Global_Class::g_character.SetMovingDown(false);
		if (nChar == KEY_UP || nChar == KEY_W)
			Global_Class::g_character.SetMovingUp(false);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			Global_Class::g_character.SetMovingLeft(false);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			Global_Class::g_character.SetMovingRight(false);
	}

	void Town_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_delayCounter < 0)
		{
			Cheater(nChar);
			switch (_flag)
			{
			case FLAG_TOWN_NORMAL:			//一般狀態，沒有開啟任何選單，可以購買東西，走路，進傳送門

				if (nChar == KEY_DOWN || nChar == KEY_S)
					Global_Class::g_character.SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					Global_Class::g_character.SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					Global_Class::g_character.SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					Global_Class::g_character.SetMovingRight(true);
				if (nChar == KEY_SPACE)
					Global_Class::g_character.Dash();
	
				if (nChar == KEY_F && _map.GetCharacterStatus() == 1)
				{
					_game_state_num = GAME_STATE_RUN_HOME;		//切換場景到Home
					_isSwitch = true;
				}

				if (nChar == KEY_F && _map.GetCharacterStatus() == 2)
				{
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_LEVEL_1;
				}

				if (nChar == KEY_F && _map.GetCharacterStatus() == 3)	//買道具1
				{

					if (_item_store.Buy(0, &Items::Instance()))
						CAudio::Instance()->Play(AUDIO_BUY, false);
					else
						CAudio::Instance()->Play(AUDIO_NOMONEY, false);

				}

				if (nChar == KEY_F && _map.GetCharacterStatus() == 4)	//買道具2
				{

					if (_item_store.Buy(1, &Items::Instance()))
						CAudio::Instance()->Play(AUDIO_BUY, false);
					else
						CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				}


				if (nChar == KEY_F && _map.GetCharacterStatus() == 5)	//買道具3
				{
					if (_item_store.Buy(2, &Items::Instance()))
						CAudio::Instance()->Play(AUDIO_BUY, false);
					else
						CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				}

				if (nChar == KEY_ESC)	//PAUSED選單
				{
					Global_Class::g_pauseMenu.Paused(true);
					_flag = FLAG_TOWN_PAUSED;
				}

				if (nChar == KEY_TAB)
				{
					Global_Class::g_bag.Open(true);
					_flag = FLAG_TOWN_BAG;
				}
				break;

			case FLAG_TOWN_PAUSED:									//暫停選單
				if (nChar == KEY_DOWN || nChar == KEY_S)
					Global_Class::g_pauseMenu.NextPausedMenu();
				if (nChar == KEY_UP || nChar == KEY_W)
					Global_Class::g_pauseMenu.PrePausedMenu();
				if (nChar == KEY_ESC)
				{
					_flag = FLAG_TOWN_NORMAL;
					Global_Class::g_pauseMenu.Paused(false);
				}
				if (nChar == KEY_SPACE)
				{
					int temp;
					temp = Global_Class::g_pauseMenu.EnterPauseMenu();

					switch (temp)
					{
					case 0:
						_flag = FLAG_TOWN_NORMAL;
						break;
					case 1:
						CAudio::Instance()->Play(AUDIO_TITLE, true);
						CAudio::Instance()->Stop(AUDIO_TOWN);
						_game_state_num = GAME_STATE_INIT;		//切換場景到Home
						_isSwitch = true;
						break;
					case 2:
						_flag = FLAG_TOWN_OPTIONS;
						break;
					case 3:
						PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
						break;
					}
				}
				break;

			case FLAG_TOWN_OPTIONS:		//點進options
				if (nChar == KEY_ESC || nChar == KEY_SPACE)
				{
					Global_Class::g_pauseMenu.PrePausedMenu();
					Global_Class::g_pauseMenu.PrePausedMenu();
					_flag = FLAG_TOWN_PAUSED;
				}
				break;

			case FLAG_TOWN_BAG:
				if (nChar == KEY_TAB || nChar == KEY_ESC)
				{
					Global_Class::g_bag.Open(false);
					_flag = FLAG_TOWN_NORMAL;
				}
				break;
			}
		}
	}

	void Town_State_Controller::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(2, point.x, point.y);
	}

	void Town_State_Controller::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(3, point.x, point.y);
	}

	void Town_State_Controller::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

		if (_delayCounter > -1)
			_delayCounter--;

		_bm_loading.SetTopLeft(0, 0);
		Global_Class::g_character.OnMove(&_map);
		_map.OnMove();
		Global_Class::g_bag.OnMove(Items::Instance().GetItemInBag());
		UI::Instance().OnMove();
		Items::Instance().Effect();
		_item_store.SetXY(_map.GetCharacterPosition());
	}

	void Town_State_Controller::OnShow()
	{
		if (_delayCounter < 0)
		{
			_map.OnShowBackground();
			_item_store.OnShow();
			_map.OnShow();
			_map.OnShowWall();
			_map.OnShowPressF();
			UI::Instance().OnShow();
			Global_Class::g_bag.OnShow();
			Global_Class::g_pauseMenu.OnShow();
		}
		else
			_bm_loading.ShowBitmap();
	}
}