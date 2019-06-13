#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "PausedMenu.h"
#include "Memento.h"
#include "Items.h"
#include "CharacterData.h"

namespace game_framework {

	PausedMenu& PausedMenu::Instance()
	{
		static PausedMenu instance;
		return instance;
	}

	PausedMenu::PausedMenu()
	{
		Initialize();
	}

	void PausedMenu::Initialize()
	{
		_paused_flag = 0;
		_isPaused = false;
	}

	void PausedMenu::LoadBitmap()
	{
		_bm_paused_resume.LoadBitmap(PAUSED_01, RGB(50, 255, 0));
		_bm_paused_title.LoadBitmap(PAUSED_02, RGB(50, 255, 0));
		_bm_paused_options.LoadBitmap(PAUSED_03, RGB(50, 255, 0));
		_bm_paused_quit.LoadBitmap(PAUSED_04, RGB(50, 255, 0));
		_bm_pause_optionss.LoadBitmap(MENU_OPTIONSS, RGB(50, 255, 0));
		_bm_paused_resume.SetTopLeft(260, 170);
		_bm_paused_title.SetTopLeft(260, 170);
		_bm_paused_options.SetTopLeft(260, 170);
		_bm_paused_quit.SetTopLeft(260, 170);
		_bm_pause_optionss.SetTopLeft(216, 80);
	}

	void PausedMenu::OnShow()				//判斷該Show哪一張圖片
	{
		if (_isPaused)
		{
			switch (_paused_flag)
			{
			case 0:
				_bm_paused_resume.ShowBitmap();
				break;
			case 1:
				_bm_paused_title.ShowBitmap();
				break;
			case 2:
				_bm_paused_options.ShowBitmap();
				break;
			case 3:
				_bm_paused_quit.ShowBitmap();
				break;
			case 4:
				_bm_pause_optionss.ShowBitmap();
			}
		}
	}

	void PausedMenu::Paused(bool flag)
	{
		_isPaused = flag;

		if (_isPaused)
			_paused_flag = 0;
	}

	void PausedMenu::NextPausedMenu()
	{
		if (_paused_flag < 3)
			_paused_flag++;
	}

	void PausedMenu::PrePausedMenu()
	{
		if (_paused_flag > 0)
			_paused_flag--;
	}

	int PausedMenu::EnterPauseMenu()
	{
		switch (_paused_flag)
		{
		case 0:							//回遊戲
			_isPaused = false;
			return 0;
			break;
		case 1:							//主選單
			_isPaused = false;
			return 1;
			break;
		case 2:							//options
			_paused_flag = 4;
			return 2;
			break;
		case 3:							//結束遊戲
			return 3;
			break;
		default:
			return 3;
		}
	}
}
