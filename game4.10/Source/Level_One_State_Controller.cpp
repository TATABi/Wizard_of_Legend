#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Level_One_State_Controller.h"

namespace game_framework {

	Level_One_State_Controller::Level_One_State_Controller() : _map(3000, 2830, &Global_Class::g_character) {}

	Level_One_State_Controller::~Level_One_State_Controller() {}

	void Level_One_State_Controller::Begin()
	{
		_game_state_num = -1;
		_isSwitch = false;
		_delayCounter = 30 * 1; // 1 seconds
		_map.Initialize(3000, 2830);
		_character->Initialize(_map.GetCharacterPosition());
		_flag = FLAG_NORMAL;
		Global_Class::g_character.Initialize(_map.GetCharacterPosition());

		CAudio::Instance()->Stop(AUDIO_TOWN);

	}

	void Level_One_State_Controller::Initialize()
	{
		_character = &Global_Class::g_character;
		_pauseMenu = &Global_Class::g_pauseMenu;
		_bag = &Global_Class::g_bag;
		_items = &Global_Class::g_items;
		_ui = &Global_Class::g_ui;

		_bm_loading.LoadBitmap(LOADING);
		_map.LoadBitmap();
	}

	void Level_One_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
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

	void Level_One_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_delayCounter < 0)
		{
			switch (_flag)
			{
			case FLAG_NORMAL:			//一般狀態，沒有開啟任何選單，可以購買東西，走路，進傳送門

				if (nChar == KEY_DOWN || nChar == KEY_S)
					Global_Class::g_character.SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					Global_Class::g_character.SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					Global_Class::g_character.SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					Global_Class::g_character.SetMovingRight(true);
				if (nChar == KEY_SPACE)
				{
					if (Global_Class::g_character.CanDash())
					{
						Global_Class::g_character.Dash();
						CAudio::Instance()->Play(AUDIO_DASH, false);
					}
				}
				if (nChar == KEY_ESC)	//PAUSED選單
				{
					Global_Class::g_pauseMenu.Paused(true);
					_flag = FLAG_PAUSED;
				}

				if (nChar == KEY_TAB)
				{
					Global_Class::g_bag.Open(true);
					_flag = FLAG_BAG;
				}
				break;

			case FLAG_PAUSED:									//暫停選單
				if (nChar == KEY_DOWN || nChar == KEY_S)
					Global_Class::g_pauseMenu.NextPausedMenu();
				if (nChar == KEY_UP || nChar == KEY_W)
					Global_Class::g_pauseMenu.PrePausedMenu();
				if (nChar == KEY_ESC)
				{
					_flag = FLAG_NORMAL;
					Global_Class::g_pauseMenu.Paused(false);
				}
				if (nChar == KEY_SPACE)
				{
					int temp;
					temp = Global_Class::g_pauseMenu.EnterPauseMenu();

					switch (temp)
					{
					case 0:
						_flag = FLAG_NORMAL;
						break;
					case 1:
						CAudio::Instance()->Play(AUDIO_TITLE, true);
						CAudio::Instance()->Stop(AUDIO_TOWN);
						_game_state_num = GAME_STATE_INIT;		//切換場景到Home
						_isSwitch = true;
						break;
					case 2:
						_flag = FLAG_OPTIONS;
						break;
					case 3:
						PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
						break;
					}
				}
				break;

			case FLAG_OPTIONS:		//點進options
				if (nChar == KEY_ESC || nChar == KEY_SPACE)
				{
					Global_Class::g_pauseMenu.PrePausedMenu();
					Global_Class::g_pauseMenu.PrePausedMenu();
					_flag = FLAG_PAUSED;
				}
				break;

			case FLAG_BAG:
				if (nChar == KEY_TAB || nChar == KEY_ESC)
				{
					Global_Class::g_bag.Open(false);
					_flag = FLAG_BAG;
				}
				break;
			}
		}

	}

	void Level_One_State_Controller::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(2, point.x, point.y);
	}

	void Level_One_State_Controller::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(3, point.x, point.y);
	}

	void Level_One_State_Controller::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

		if (_delayCounter > -1)
			_delayCounter--;

		_bm_loading.SetTopLeft(0, 0);
		Global_Class::g_character.OnMove(&_map);
		_map.OnMove();
		Global_Class::g_bag.OnMove(Global_Class::g_items.GetItemInBag());
		Global_Class::g_ui.OnMove();
		Global_Class::g_items.Effect();
	}

	void Level_One_State_Controller::OnShow()
	{
		if (_delayCounter < 0)
		{
			_map.OnShowBackground();
			_map.OnShow();
			Global_Class::g_ui.OnShow();
			Global_Class::g_bag.OnShow();
			Global_Class::g_pauseMenu.OnShow();
		}
		else
			_bm_loading.ShowBitmap();
	}

	bool Level_One_State_Controller::IsSwitchGameState()
	{
		return _isSwitch;
	}

	int Level_One_State_Controller::GameState()
	{
		return _game_state_num;
	}
}