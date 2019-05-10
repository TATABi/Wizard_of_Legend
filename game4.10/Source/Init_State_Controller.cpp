#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Init_State_Controller.h"

namespace game_framework {
	
	Init_State_Controller::Init_State_Controller() { }

	void Init_State_Controller::Begin()
	{
		_flag = FLAG_INIT_INIT;
		_instruction = SINGLE_PLAYER;
		_game_state_num = -1;
		_isSwitch = false;
	}

	void Init_State_Controller::Initialize()
	{	
		if (CAudio::Instance()->Load(AUDIO_TITLE, "sounds\\TitleBGM.wav"))
			CAudio::Instance()->Play(AUDIO_TITLE, true);

		CAudio::Instance()->Load(AUDIO_BE, "sounds\\be.mp3");

		
		int m1[23] = { MENU_INIT_02,MENU_INIT_04,MENU_INIT_06,MENU_INIT_08,MENU_INIT_10,MENU_INIT_12,MENU_INIT_16,MENU_INIT_18,MENU_INIT_20,MENU_INIT_22,MENU_INIT_24,
			MENU_INIT_26, MENU_INIT_28, MENU_INIT_30, MENU_INIT_32, MENU_INIT_34, MENU_INIT_36, MENU_INIT_38, MENU_INIT_40, MENU_INIT_42, MENU_INIT_44,
			MENU_INIT_46, MENU_INIT_48 };
		for (int i = 0; i < 23; i++)
			_ani_menu_1.AddBitmap(m1[i]);
		
		int m2[11] = { MENU_ENTERMENU_01, MENU_ENTERMENU_02, MENU_ENTERMENU_03, MENU_ENTERMENU_04, MENU_ENTERMENU_05, MENU_ENTERMENU_06, MENU_ENTERMENU_07,
			MENU_ENTERMENU_08, MENU_ENTERMENU_09, MENU_ENTERMENU_10, MENU_ENTERMENU_11 };
		for (int i = 0; i < 11; i++)
			_ani_menu_2.AddBitmap(m2[i]);

	
		_bm_option.LoadBitmap(MENU_ENTERMENU_OPTIONS);
		_bm_quit.LoadBitmap(MENU_ENTERMENU_QUIT);
		_bm_single_player.LoadBitmap(MENU_ENTERMENU_SINGLE_PLAYER);
		_bm_loading.LoadBitmap(LOADING);
		_bm_option_page.LoadBitmap(MENU_OPTIONS);

		_ani_menu_1.SetDelayCount(2);
		_ani_menu_2.SetDelayCount(1);

	}

	void Init_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){}

	void Init_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CAudio::Instance()->Stop(AUDIO_BE);
		CAudio::Instance()->Play(AUDIO_BE, false);

		switch (_flag)
		{
		case FLAG_INIT_INIT:
			_flag = FLAG_INIT_MENU;
			break;

		case FLAG_INIT_MENU:

			if (nChar == KEY_ESC)
			{
				if (_instruction == QUIT)
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
				else
					_instruction = QUIT;
			}
			else if (nChar == KEY_UP || nChar == KEY_W)
			{
				_instruction > 0 ? _instruction-- : NULL;
			}
			else if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				_instruction < 2 ? _instruction++ : NULL;
			}
			else if (nChar == KEY_SPACE || nChar == KEY_ENTER)
			{
				switch (_instruction)
				{
				case SINGLE_PLAYER:
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_HOME;
					break;
				case OPTION:
					_flag = FLAG_INIT_OPTION;
					break;
				case QUIT:
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
					break;
				}
			}
			break;

		case FLAG_INIT_OPTION:
			if (nChar == KEY_ESC)
				_flag = FLAG_INIT_MENU;
			break;	
		}
	}

	void Init_State_Controller::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (_flag == FLAG_INIT_INIT)
			_flag = FLAG_INIT_MENU;
	}

	void Init_State_Controller::OnRButtonDown(UINT nFlags, CPoint point)
	{
		if (_flag == FLAG_INIT_INIT)
			_flag = FLAG_INIT_MENU;
	}

	void Init_State_Controller::OnShow()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	
		switch (_flag) 
		{
		case FLAG_INIT_INIT:
			_ani_menu_1.OnMove();
			_ani_menu_1.SetTopLeft(0, 0);
			_ani_menu_1.OnShow();	
			break;

		case FLAG_INIT_MENU:
			if (!_ani_menu_2.IsFinalBitmap()) {
				_ani_menu_2.OnMove();
				_ani_menu_2.SetTopLeft(0, 0);
				_ani_menu_2.OnShow();
			}
			else {
				switch (_instruction)
				{
				case SINGLE_PLAYER:
					_bm_single_player.SetTopLeft(0, 0);
					_bm_single_player.ShowBitmap();
					break;
				case OPTION:
					_bm_option.SetTopLeft(0, 0);
					_bm_option.ShowBitmap();
					break;
				case QUIT:
					_bm_quit.SetTopLeft(0, 0);
					_bm_quit.ShowBitmap();
					break;
				}
				
			}
			break;
		case FLAG_INIT_OPTION:
			_bm_option_page.SetTopLeft(0, 0);
			_bm_option_page.ShowBitmap();
			break;
		}
		
	}

	bool Init_State_Controller::IsSwitchGameState()
	{
		return _isSwitch;
	}
	int Init_State_Controller::GotoGameState()
	{
		return _game_state_num;
	}
}