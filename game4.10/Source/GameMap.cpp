#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"


namespace game_framework {
	
	GameMap::GameMap(int x, int y)
	{
		Initialize(x, y);
	}
	
	GameMap::~GameMap() {
	
	}

	void GameMap::Initialize(int x, int y) 
	{
		_cx = x;
		_cy = y;	
		ani_press_f.SetDelayCount(2);
		can_press_f = false;
		character_status = 0;
	}

	void GameMap::ParentLoadBitmap()
	{
		ani_press_f.AddBitmap(PRESS_F_01, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_02, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_03, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_04, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_05, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_06, RGB(50, 255, 0));

	}
	
	void GameMap::ParentOnMove()
	{
		_background.SetTopLeft(CHARACTER_SCREEN_X - _cx  , CHARACTER_SCREEN_Y - _cy);
		_wall.SetTopLeft(CHARACTER_SCREEN_X - _cx	, CHARACTER_SCREEN_Y - _cy );
	}
	
	void GameMap::OnShowBackground()
	{
		_background.ShowBitmap();
	}

	void GameMap::OnShowWall()
	{
		_wall.ShowBitmap();
	}

	void GameMap::OnShowPressF()
	{
		if (can_press_f)
			ani_press_f.OnShow();
	}
	/*
	void GameMap::Paused(bool paused)
	{
		isPaused = paused;
		paused_flag = 0;
	}

	void GameMap::OnShowPaused()
	{
		if (isPaused)
		{
			switch (paused_flag)
			{
			case 0:
				paused_resume.ShowBitmap();
				break;
			case 1:
				paused_title.ShowBitmap();
				break;
			case 2:
				paused_options.ShowBitmap();
				break;
			case 3:
				paused_quit.ShowBitmap();
				break;
			}
		}
	}
	*/

	int GameMap::GetCharacterStatus() 
	{
		return character_status;
	}

}


