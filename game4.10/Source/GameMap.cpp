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

	void GameMap::LoadBitmap()
	{
		_background.LoadBitmap(INGAME_MAP_HOME);
		_wall.LoadBitmap(INGAME_MAP_HOME_WALL, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_01, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_02, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_03, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_04, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_05, RGB(50, 255, 0));
		ani_press_f.AddBitmap(PRESS_F_06, RGB(50, 255, 0));

	}

	void GameMap::OnMove()
	{
		_background.SetTopLeft(CHARACTER_SCREEN_X - _cx  , CHARACTER_SCREEN_Y - _cy);
		_wall.SetTopLeft(CHARACTER_SCREEN_X - _cx	, CHARACTER_SCREEN_Y - _cy );

		// press f
		character_status = home_map[_cx + collision_move[0] + 10][_cy + collision_move[1] + 3];
		int temp_x=0, temp_y=0;
		if (character_status == 1 || character_status == 2 || character_status == 3)
		{
			switch (character_status)
			{
			case 1:						//傳送門
				temp_x = 770;
				temp_y = 380;
				ani_press_f.OnMove();
				break;
			case 2:						//道具箱
				temp_x = 865;
				temp_y = 1147;
				ani_press_f.OnMove();
				break;
			case 3:						// 書
				temp_x = 1235;
				temp_y = 860;
				ani_press_f.OnMove();
				break;
			}
			can_press_f = true;
			ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - _cx, CHARACTER_SCREEN_Y + temp_y - _cy);
		}
		else
		{
			ani_press_f.Reset();
			can_press_f = false;
		}
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

	void GameMap::SetCharacterXY(int dx, int dy) 
	{	


		if (home_map[_cx + collision_move[0] + dx][_cy + collision_move[1] + dy] != -1							//左上
			&& home_map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + dy] != -1				//右上
			&& home_map[_cx + collision_move[0] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1				//左下
			&& home_map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1)		//右下
		{
			_cx += dx;
			_cy += dy;
		}
		
	}

	int GameMap::CharacterStatus() 
	{
		return character_status;
	}
}

