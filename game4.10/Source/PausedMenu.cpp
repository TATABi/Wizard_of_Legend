#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "PausedMenu.h"

namespace game_framework {

	PausedMenu::PausedMenu()
	{
		Initialize();
	}

	void PausedMenu::Initialize()
	{
		paused_flag = 0;
		isPaused = false;
	}

	void PausedMenu::LoadBitmap()
	{
		bm_paused_resume.LoadBitmap(PAUSED_01, RGB(50, 255, 0));
		bm_paused_title.LoadBitmap(PAUSED_02, RGB(50, 255, 0));
		bm_paused_options.LoadBitmap(PAUSED_03, RGB(50, 255, 0));
		bm_paused_quit.LoadBitmap(PAUSED_04, RGB(50, 255, 0));
		bm_pause_optionss.LoadBitmap(MENU_OPTIONSS, RGB(50, 255, 0));

		bm_paused_resume.SetTopLeft(260, 170);
		bm_paused_title.SetTopLeft(260, 170);
		bm_paused_options.SetTopLeft(260, 170);
		bm_paused_quit.SetTopLeft(260, 170);
		bm_pause_optionss.SetTopLeft(216, 80);
		

	}

	void PausedMenu::OnShow()
	{
		if (isPaused)
		{
			switch (paused_flag)
			{
			case 0:
				bm_paused_resume.ShowBitmap();
				break;
			case 1:
				bm_paused_title.ShowBitmap();
				break;
			case 2:
				bm_paused_options.ShowBitmap();
				break;
			case 3:
				bm_paused_quit.ShowBitmap();
				break;
			case 4:
				bm_pause_optionss.ShowBitmap();
			}
		}

	}

	void PausedMenu::Paused(bool flag)
	{
		isPaused = flag;

		if (isPaused)
			paused_flag = 0;
	}

	void PausedMenu::NextPausedMenu()
	{
		if (paused_flag < 3)
			paused_flag++;
	}

	void PausedMenu::PrePausedMenu()
	{
		if (paused_flag > 0)
			paused_flag--;
	}

	int PausedMenu::EnterPauseMenu()
	{
		switch (paused_flag)
		{
		case 0:		//回遊戲
			isPaused = false;
			return 0;
			break;
		case 1:		//主選單
			isPaused = false;
			return 1;
			break;
		case 2:		//options
			paused_flag = 4;
			return 2;
			break;
		case 3:		//結束遊戲
			return 3;
			break;
		default:
			return 3;
		}
	}
}
