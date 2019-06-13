#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Init_State_Controller.h"
#include "GameData.h"

namespace game_framework {
	Init_State_Controller::Init_State_Controller() : Controller(){} 

	void Init_State_Controller::Begin()
	{
		_audio_delay_counter = 1;
		_game_state_num = -1;
		_flag = FLAG_INIT_INIT;
		_instruction_1 = SINGLE_PLAYER;
		_instruction_2 = KEY_CONFIG;
		_isSwitch = false;
		CAudio::Instance()->StopAll();
	}

	void Init_State_Controller::Initialize()
	{	
		LoadData();
		int m1[23] = { MENU_INIT_02,MENU_INIT_04,MENU_INIT_06,MENU_INIT_08,MENU_INIT_10,MENU_INIT_12,MENU_INIT_16,MENU_INIT_18,MENU_INIT_20,MENU_INIT_22,MENU_INIT_24,
			MENU_INIT_26, MENU_INIT_28, MENU_INIT_30, MENU_INIT_32, MENU_INIT_34, MENU_INIT_36, MENU_INIT_38, MENU_INIT_40, MENU_INIT_42, MENU_INIT_44,
			MENU_INIT_46, MENU_INIT_48 };
		for (int i = 0; i < 23; i++)
			_ani_menu_1.AddBitmap(m1[i]);
		
		int m2[11] = { MENU_ENTERMENU_01, MENU_ENTERMENU_02, MENU_ENTERMENU_03, MENU_ENTERMENU_04, MENU_ENTERMENU_05, MENU_ENTERMENU_06, MENU_ENTERMENU_07,
			MENU_ENTERMENU_08, MENU_ENTERMENU_09, MENU_ENTERMENU_10, MENU_ENTERMENU_11 };
		for (int i = 0; i < 11; i++)
			_ani_menu_2.AddBitmap(m2[i]);

		int m3[10] = { MENU_EAT_PIZZA_01, MENU_EAT_PIZZA_02, MENU_EAT_PIZZA_03, MENU_EAT_PIZZA_04, MENU_EAT_PIZZA_05, MENU_EAT_PIZZA_06, MENU_EAT_PIZZA_07, MENU_EAT_PIZZA_08, MENU_EAT_PIZZA_09, MENU_EAT_PIZZA_10 };
		for (int i = 0; i < 10; i++)
			_ani_reset_data.AddBitmap(m3[i]);

		_bm_option.LoadBitmap(MENU_ENTERMENU_OPTIONS);
		_bm_quit.LoadBitmap(MENU_ENTERMENU_QUIT);
		_bm_single_player.LoadBitmap(MENU_ENTERMENU_SINGLE_PLAYER);
		_bm_loading.LoadBitmap(LOADING);
		_bm_options_page_1.LoadBitmap(MENU_OPTION_1);
		_bm_options_page_2.LoadBitmap(MENU_OPTION_2);
		_bm_options_page_3.LoadBitmap(MENU_OPTION_3);
		_bm_key_config.LoadBitmap(MENU_KEY_CONFIG);
		_bm_about.LoadBitmap(MENU_ABOUT);
		_bm_single_player.SetTopLeft(0, 0);
		_bm_quit.SetTopLeft(0, 0);
		_bm_option.SetTopLeft(0, 0);
		_ani_menu_1.SetTopLeft(0, 0);
		_ani_menu_2.SetTopLeft(0, 0);
		_bm_options_page_1.SetTopLeft(0, 0);
		_bm_options_page_2.SetTopLeft(0, 0);
		_bm_options_page_3.SetTopLeft(0, 0);
		_bm_key_config.SetTopLeft(0, 0);
		_bm_about.SetTopLeft(0, 0);
		_ani_reset_data.SetTopLeft(0, 0);
		_ani_menu_1.SetDelayCount(2);
		_ani_menu_2.SetDelayCount(1);
		_ani_reset_data.SetDelayCount(10);

	}

	void Init_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){}

	void Init_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		Cheater(nChar);
		CAudio::Instance()->Play(AUDIO_BE, false);
		switch (_flag)
		{
		case FLAG_INIT_INIT:	//初始選單
			_flag = FLAG_INIT_MENU;
			break;
		case FLAG_INIT_MENU:	//開始選單
			if (nChar == KEY_ESC)
			{
				if (_instruction_1 == QUIT)
				{
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
				}
				else
					_instruction_1 = QUIT;
			}
			else if (nChar == KEY_UP || nChar == KEY_W)
			{
				_instruction_1 > 0 ? _instruction_1-- : NULL;
			}
			else if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				_instruction_1 < 2 ? _instruction_1++ : NULL;
			}
			else if (nChar == KEY_SPACE || nChar == KEY_ENTER)
			{
				switch (_instruction_1)
				{
				case SINGLE_PLAYER:
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_HOME;
					break;
				case OPTIONS:
					_flag = FLAG_INIT_OPTION;
					break;
				case QUIT:
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
					break;
				}
			}
			break;
		case FLAG_INIT_OPTION:	//Option
			if (nChar == KEY_ESC)
			{
				_flag = FLAG_INIT_MENU;
				_instruction_2 = KEY_CONFIG;
			}
			else if (nChar == KEY_SPACE)
			{
				switch (_instruction_2)
				{
				case KEY_CONFIG:
					_flag = FLAG_INIT_KEY_CONFIG;
					break;
				case RESET_DATA:
					remove(SAVE_DATA_PATH.c_str());
					ResetData();
					_flag = FLAG_INIT_RESET_DATA;
					break;
				case ABOUT:
					_flag = FLAG_INIT_ABOUT;
					break;
				}
			}
			else if (nChar == KEY_UP || nChar == KEY_W)
			{
				_instruction_2 > 0 ? _instruction_2-- : NULL;
			}
			else if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				_instruction_2 < 2 ? _instruction_2++ : NULL;
			}
			break;	
		case FLAG_INIT_KEY_CONFIG:	//查看按鍵功能
		case FLAG_INIT_ABOUT:		//About資訊
			if (nChar == KEY_ESC)
				_flag = FLAG_INIT_OPTION;
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
		_audio_delay_counter >= 0 ? _audio_delay_counter-- : NULL;
		_audio_delay_counter == 0 ? CAudio::Instance()->Play(AUDIO_TITLE) : NULL;
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
		switch (_flag) 
		{
		case FLAG_INIT_INIT:
			_ani_menu_1.OnMove();
			_ani_menu_1.OnShow();	
			break;
		case FLAG_INIT_MENU:
			if (!_ani_menu_2.IsFinalBitmap()) {
				_ani_menu_2.OnMove();
				_ani_menu_2.OnShow();
			}
			else {
				switch (_instruction_1)
				{
				case SINGLE_PLAYER:
					_bm_single_player.ShowBitmap();
					break;
				case OPTIONS:
					
					_bm_option.ShowBitmap();
					break;
				case QUIT:	
					_bm_quit.ShowBitmap();
					break;
				}
			}
			break;
		case FLAG_INIT_OPTION:
			switch (_instruction_2)
			{
			case KEY_CONFIG:
				_bm_options_page_1.ShowBitmap();
				break;
			case RESET_DATA:
				_bm_options_page_2.ShowBitmap();
				break;
			case ABOUT:
				_bm_options_page_3.ShowBitmap();
				break;
			}
			break;
		case FLAG_INIT_KEY_CONFIG:
			_bm_key_config.ShowBitmap();
			break;
		case FLAG_INIT_RESET_DATA:
			_ani_reset_data.OnMove();
			_ani_reset_data.OnShow();
			//動畫播完移置Option選單
			if (_ani_reset_data.IsFinalBitmap())
			{
				_ani_reset_data.Reset();
				_flag = FLAG_INIT_OPTION;
			}
			break;
		case FLAG_INIT_ABOUT:
			_bm_about.ShowBitmap();
			break;
		}
	}
}