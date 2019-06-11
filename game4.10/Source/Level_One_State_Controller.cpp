#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Level_One_State_Controller.h"
#include "GameData.h"

#define LEVEL_ONE 1
namespace game_framework {
	Level_One_State_Controller::Level_One_State_Controller() :Controller(), _map(LEVEL_ONE_CHARACTER_XY[0], LEVEL_ONE_CHARACTER_XY[1]) {}
	
	void Level_One_State_Controller::Begin()
	{
		_map.AddEnemy();
		LoadMemento(Town_Or_Home);
		_game_state_num = -1;
		_isSwitch = false;
		_delayCounter = 30 * 4;			// 4 seconds
		_map.Initialize(LEVEL_ONE_CHARACTER_XY[0], LEVEL_ONE_CHARACTER_XY[1]);
		_flag = FLAG_NORMAL;
		Character::Instance().Initialize(_map.GetCharacterPosition());
		CAudio::Instance()->StopAll();
		CAudio::Instance()->Play(AUDIO_LEVEL_FIRE, true);
		UI::Instance().ResetMapMask();
		_bm_loading_chess.SetTopLeft(-100, -100);
		_chess_xy[0] = 62;
		_chess_xy[1] = 135;
		_isUpDown = true;
	}

	void Level_One_State_Controller::Initialize()
	{
		_bm_loading_level.LoadBitmap(LOADING_LEVEL);
		_bm_loading_chess.LoadBitmap(LOADING_CHESS, RGB(50, 255, 0));
		_map.LoadBitmap();
	}

	void Level_One_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (nChar == KEY_DOWN || nChar == KEY_S)
			Character::Instance().SetMovingDown(false);
		if (nChar == KEY_UP || nChar == KEY_W)
			Character::Instance().SetMovingUp(false);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			Character::Instance().SetMovingLeft(false);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			Character::Instance().SetMovingRight(false);
	}

	void Level_One_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_delayCounter < 0)
		{
			Cheater(nChar);

			if (nChar == KEY_F6)	//重生Enemy
			{
				_map.AddEnemy();
			}

			switch (_flag)
			{
			case FLAG_NORMAL:			//一般狀態，沒有開啟任何選單，可以購買東西，走路，進傳送門
				if (nChar == KEY_DOWN || nChar == KEY_S)
					Character::Instance().SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					Character::Instance().SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					Character::Instance().SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					Character::Instance().SetMovingRight(true);
				if (nChar == KEY_SPACE)
					Character::Instance().Dash();
				if (nChar == KEY_ESC)	//PAUSED選單
				{
					CAudio::Instance()->Play(AUDIO_BE, false);
					PausedMenu::Instance().Paused(true);
					_flag = FLAG_PAUSED;
				}
				if (nChar == KEY_TAB)
				{
					Bag::Instance().Open(true);
					_flag = FLAG_BAG;
				}
				if (nChar == KEY_M)
				{
					UI::Instance().OpenMap(true, 1);
					_flag = FLAG_MAP;
				}
				break;

			case FLAG_PAUSED:									//暫停選單
				CAudio::Instance()->Play(AUDIO_BE, false);
				if (nChar == KEY_DOWN || nChar == KEY_S)
					PausedMenu::Instance().NextPausedMenu();
				if (nChar == KEY_UP || nChar == KEY_W)
					PausedMenu::Instance().PrePausedMenu();
				if (nChar == KEY_ESC)
				{
					_flag = FLAG_NORMAL;
					PausedMenu::Instance().Paused(false);
				}
				if (nChar == KEY_SPACE)
				{
					int temp;
					temp = PausedMenu::Instance().EnterPauseMenu();

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
				CAudio::Instance()->Play(AUDIO_BE, false);
				if (nChar == KEY_ESC)
				{
					PausedMenu::Instance().PrePausedMenu();
					PausedMenu::Instance().PrePausedMenu();
					_flag = FLAG_PAUSED;
				}
				if (nChar == KEY_SPACE)
				{
					//音效
				}
				break;

			case FLAG_BAG:
				if (nChar == KEY_TAB || nChar == KEY_ESC)
				{
					Bag::Instance().Open(false);
					_flag = FLAG_NORMAL;
				}
				break;

			case FLAG_MAP:
				if (nChar == KEY_DOWN || nChar == KEY_S)
					Character::Instance().SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					Character::Instance().SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					Character::Instance().SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					Character::Instance().SetMovingRight(true);
				if (nChar == KEY_SPACE)
					Character::Instance().Dash();
				if (nChar == KEY_ESC || nChar == KEY_M)	//PAUSED選單
				{
					UI::Instance().OpenMap(false, 1);
					_flag = FLAG_NORMAL;
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
		CharacterData::Instance().SetStage(LEVEL_ONE);
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
		CharacterDead();		//判斷腳色死亡、執行相關動作

		if (_delayCounter > -1)
			_delayCounter--;

		_bm_loading_level.SetTopLeft(0, 0);
		_bm_loading_chess.SetTopLeft(_chess_xy[0], _chess_xy[1]);

		if (_delayCounter < 110)
		{
			_chess_xy[0] < 212 ? _chess_xy[0] += 2 : NULL;
			if (_isUpDown)
			{
				_chess_xy[1] >= 137 ? _isUpDown = false : _chess_xy[1] += 2;
			}
			else
			{
				_chess_xy[1] <= 133 ? _isUpDown = true : _chess_xy[1] -= 2;
			}
		}

		_map.OnMove();
		Character::Instance().OnMove(&_map);
		Bag::Instance().OnMove();
		UI::Instance().OnMove();
		Items::Instance().Effect();
	}

	void Level_One_State_Controller::OnShow()
	{
		if (_delayCounter < 0)
		{
			_map.OnShowBackground();
			_map.OnShow();
			_map.OnShowWall();
			UI::Instance().OnShow();
			Bag::Instance().OnShow();
			PausedMenu::Instance().OnShow();
		}
		else
		{
			_bm_loading_level.ShowBitmap();
			_bm_loading_chess.ShowBitmap();
		}
	}
}