#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "Home_State_Controller.h"

namespace game_framework {

	Home_State_Controller::Home_State_Controller()
	:_map(740, 918, &Global_Class::g_character)
	{}

	Home_State_Controller::~Home_State_Controller()
	{}

	void Home_State_Controller::Begin()
	{
		_game_state_num = -1;
		_isSwitch = false;
		_delayCounter = 30 * 1; // 1 seconds
		_map.Initialize(740, 918);
		_character->Initialize(_map.GetCharacterPosition());

		//從其他場景回來不用再次出現加入選單
		if (_ani_light_beam.IsFinalBitmap())
		{
			_ani_light_beam.Reset();
			_flag = FLAG_HOME_NORMAL;
		}
		else
			_flag = FLAG_JOIN;

		CAudio::Instance()->Stop(AUDIO_TITLE);
		CAudio::Instance()->Play(AUDIO_HOME, true);
		CAudio::Instance()->Stop(AUDIO_TOWN);
	}

	void Home_State_Controller::LoadBitmap()
	{
		
	}

	void Home_State_Controller::Initialize()
	{
		_character =& Global_Class::g_character;
		_pauseMenu =& Global_Class::g_pauseMenu;
		_bag = &Global_Class::g_bag;
		_items = &Global_Class::g_items;
		_ui = &Global_Class::g_ui;
		

		CAudio::Instance()->Load(AUDIO_PULL, "sounds\\pull.mp3");
		CAudio::Instance()->Load(AUDIO_PUTTING, "sounds\\putting.mp3");
		CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");
		CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");
		CAudio::Instance()->Load(AUDIO_ARRIVAL, "sounds\\arrival.mp3");
		CAudio::Instance()->Load(AUDIO_PULL2, "sounds\\pull2.mp3");
		
		_bm_join.LoadBitmap(JOIN);
		_bm_loading.LoadBitmap(LOADING);

		_box.LoadBitmap();
		_book.LoadBitmap();
		_map.LoadBitmap();


		_ani_light_beam.SetDelayCount(1);
		_ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM02, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM03, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM04, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
		_ani_light_beam.SetTopLeft(0, 0);
	}

	void Home_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
	{
		if (nChar == KEY_DOWN || nChar == KEY_S)
			_character->SetMovingDown(false);
		if (nChar == KEY_UP || nChar == KEY_W)
			_character->SetMovingUp(false);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			_character->SetMovingLeft(false);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			_character->SetMovingRight(false);
	}

	void Home_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_delayCounter < 0)
		{
			switch (_flag)
			{
			case FLAG_HOME_NORMAL:
				//進入遊戲，沒有開啟任何選單
				if (nChar == KEY_DOWN || nChar == KEY_S)
					_character->SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					_character->SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					_character->SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					_character->SetMovingRight(true);
				if (nChar == KEY_SPACE)
				{
					if (_character->CanDash())
					{
						_character->Dash();
						CAudio::Instance()->Play(AUDIO_DASH, false);
					}
				}
				if (nChar == KEY_F && _map.GetCharacterStatus() == 1)
				{
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_TOWN;			//切換到town
				}

				if (nChar == KEY_F && _map.GetCharacterStatus() == 2)
				{
					_box.Open(true);
					_flag = FLAG_BOX;		//開啟道具箱
				}

				if (nChar == KEY_F && _map.GetCharacterStatus() == 3)
				{
					_book.Open(true);		//開啟書
					_flag = FLAG_BOOK;
				}

				if (nChar == KEY_ESC)	//PAUSED選單
				{
					_pauseMenu->Paused(true);
					_flag = FLAG_HOME_PAUSED;
				}

				if (nChar == KEY_TAB)
				{
					_bag->Open(true);
					_flag = FLAG_HOME_BAG;
				}
				break;

			case FLAG_JOIN:

				if (nChar == KEY_SPACE)		// 加入遊戲提示選單
				{
					_flag = FLAG_HOME_NORMAL;				// 角色進入遊戲
				}
				break;

			case FLAG_BOX:							//道具箱選單
				if (nChar == KEY_ESC)
				{
					_box.Open(false);
					_flag = FLAG_HOME_NORMAL;
				}
				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					CAudio::Instance()->Play(AUDIO_PULL2, false);
					_box.Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					CAudio::Instance()->Play(AUDIO_PULL2, false);
					_box.Up();
				}
				if (nChar == KEY_SPACE)
				{
					CAudio::Instance()->Play(AUDIO_PULL, false);
					_box.OpenOpen(true);
					_flag = FLAG_BOX_ITEM;
				}
				break;

			case FLAG_BOX_ITEM:

				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					_box.Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					_box.Up();
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					_box.Left();
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					_box.Right();
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
				}
				if (nChar == KEY_SPACE)
				{
					if (_box.Equip(_items)) {
						_box.OpenOpen(false);
						_flag = FLAG_BOX;
					}
					else {
						CAudio::Instance()->Play(AUDIO_NOMONEY, false);
					}
				}
				if (nChar == KEY_ESC)
				{
					_box.OpenOpen(false);
					_flag = FLAG_BOX;
				}
				break;

			case FLAG_HOME_PAUSED:									//暫停選單
				if (nChar == KEY_DOWN || nChar == KEY_S)
					_pauseMenu->NextPausedMenu();
				if (nChar == KEY_UP || nChar == KEY_W)
					_pauseMenu->PrePausedMenu();
				if (nChar == KEY_ESC)
				{
					_flag = FLAG_HOME_NORMAL;
					_pauseMenu->Paused(false);
				}
				if (nChar == KEY_SPACE)
				{
					int temp;
					temp = _pauseMenu->EnterPauseMenu();

					switch (temp)
					{
					case 0:
						_flag = FLAG_HOME_NORMAL;
						break;
					case 1:
						_flag = FLAG_JOIN;
						_ani_light_beam.Reset();
						_map.Initialize(740, 918);
						CAudio::Instance()->Play(AUDIO_TITLE, true);
						CAudio::Instance()->Stop(AUDIO_HOME);
						_isSwitch = true;
						_game_state_num = GAME_STATE_INIT;
						break;
					case 2:
						_flag = FLAG_HOME_OPTIONS;
						break;
					case 3:
						PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
						break;
					}
				}
				break;

			case FLAG_HOME_OPTIONS:		//點進options
				if (nChar == KEY_ESC || nChar == KEY_SPACE)
				{
					_pauseMenu->PrePausedMenu();
					_pauseMenu->PrePausedMenu();
					_flag = FLAG_HOME_PAUSED;
				}
				break;
			case FLAG_HOME_BAG:
				if (nChar == KEY_TAB || nChar == KEY_ESC)
				{
					_bag->Open(false);
					_flag = FLAG_HOME_NORMAL;
				}
				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					_bag->Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					_bag->Up();
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					_bag->Left();
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					_bag->Right();
				}

				break;

			case FLAG_BOOK:

				if (nChar == KEY_ESC)
				{
					_book.Open(false);
					_flag = FLAG_HOME_NORMAL;
				}

				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					_book.Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					_book.Up();
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					_book.Left();
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					_book.Right();
				}
				break;

			}
		}
	}

	void Home_State_Controller::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(2, point.x, point.y);
	}

	void Home_State_Controller::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(3, point.x, point.y);
	}

	void Home_State_Controller::OnMove() 
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

		if (_delayCounter > -1)
			_delayCounter--;

		_bm_join.SetTopLeft(100, 100);
		_bm_loading.SetTopLeft(0, 0);
		_character->OnMove(&_map);
		_map.OnMove();
		_box.OnMove();
		_book.OnMove();
		_bag->OnMove(_items->GetItemInBag());
		_ui->OnMove();
		_items->Effect();
	}

	void Home_State_Controller::OnShow()
	{
		if (_delayCounter < 0)
		{
			_map.OnShowBackground();
			if (_flag == 1)
				_bm_join.ShowBitmap();
			else
			{
				if (!_ani_light_beam.IsFinalBitmap())
				{
					CAudio::Instance()->Play(AUDIO_ARRIVAL, false);
					_ani_light_beam.OnMove();
					_ani_light_beam.OnShow();
				}
				else
				{
					_map.OnShow();

					_map.OnShowWall();

					_map.OnShowPressF();


					_box.OnShow(_items);
					_book.OnShow();
					_ui->OnShow();
					_bag->OnShow();
					_pauseMenu->OnShow();
				}


			}
		}
		else
			_bm_loading.ShowBitmap();
	}

	bool Home_State_Controller::IsSwitchGameState()
	{
		return _isSwitch;
	}

	int Home_State_Controller::GameState()
	{
		return _game_state_num;
	}
}
