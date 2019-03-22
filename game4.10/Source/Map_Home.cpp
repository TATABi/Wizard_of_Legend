#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Home.h"

namespace game_framework {

	Map_Home::Map_Home(int x, int y) : GameMap(x, y){
	}

	Map_Home::~Map_Home() {

	}

	void Map_Home::LoadBitmap()
	{
		ParentLoadBitmap();
		_background.LoadBitmap(MAP_HOME);
		_wall.LoadBitmap(MAP_HOME_WALL, RGB(50, 255, 0));
	}

	void Map_Home::OnMove()
	{
		ParentOnMove();
		character_status = home_map[_cx + collision_move[0] + 10][_cy + collision_move[1] + 3];
		int temp_x = 0, temp_y = 0;
		if (character_status == 1 || character_status == 2 || character_status == 3)
		{
			switch (character_status)
			{
			case 1:						//傳送門
				temp_x = 770;
				temp_y = 360;
				ani_press_f.OnMove();
				break;
			case 2:						//道具箱
				temp_x = 865;
				temp_y = 1137;
				ani_press_f.OnMove();
				break;
			case 3:						// 書
				temp_x = 1235;
				temp_y = 840;
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

	
	void Map_Home::OnShow()
	{
		OnShowBackground();
		OnShowWall();
		OnShowPressF();
	}
	
	void Map_Home::SetCharacterXY(int dx, int dy)
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

}
