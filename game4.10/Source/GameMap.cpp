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
		cxy[0] = x;
		cxy[1] = y;	
		ani_press_f.SetDelayCount(2);
		isPressF = false;
		character_status = 0;
		
	}

	void GameMap::ParentLoadBitmap()
	{
		int m[6] = { PRESS_F_01, PRESS_F_02, PRESS_F_03 , PRESS_F_04, PRESS_F_05, PRESS_F_06 };
		for (int i = 0; i < 6;i++)
			ani_press_f.AddBitmap(m[i], RGB(50, 255, 0));

	}
	
	void GameMap::ParentOnMove()
	{
		_background.SetTopLeft(CHARACTER_SCREEN_X - cxy[0], CHARACTER_SCREEN_Y - cxy[1]);
		_wall.SetTopLeft(CHARACTER_SCREEN_X - cxy[0], CHARACTER_SCREEN_Y - cxy[1]);
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
		if (isPressF)
			ani_press_f.OnShow();
	}
	
	int GameMap::GetCharacterStatus() 
	{
		return character_status;
	}

	int* GameMap::GetCharacterPosition()
	{
		return cxy;
	}



}


