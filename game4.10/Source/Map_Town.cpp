#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Town.h"

namespace game_framework {

	Map_Town::Map_Town(int x, int y) : GameMap(x, y) {
	}

	Map_Town::~Map_Town() {

	}

	void Map_Town::LoadBitmap()
	{
		ParentLoadBitmap();
		_background.LoadBitmap(MAP_TOWN);
		_wall.LoadBitmap(MAP_TOWN_WALL, RGB(50, 255, 0));
	}

	void Map_Town::OnMove()
	{
		ParentOnMove();
		character_status = town_map[_cx + collision_move[0] + 10][_cy + collision_move[1] + 3];
		int temp_x = 0, temp_y = 0;
		if (character_status == 1 || character_status == 2 || character_status == 3)
		{
			switch (character_status)
			{
			case 1:						//傳送門(往家)
				temp_x = 792;
				temp_y = 1052;
				ani_press_f.OnMove();
				break;
			case 2:						//傳送門(往關卡)
				temp_x = 791;
				temp_y = 561;
				ani_press_f.OnMove();
				break;
			case 3:						// 道具1
				temp_x = 530;
				temp_y = 969;
				ani_press_f.OnMove();
				break;
			case 4:						// 道具2
				temp_x = 575;
				temp_y = 971;
				ani_press_f.OnMove();
				break;
			case 5:						// 道具3
				temp_x = 620;
				temp_y = 973;
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


	void Map_Town::OnShow()
	{
		OnShowBackground();
		OnShowWall();
		OnShowPressF();
	}

	void Map_Town::SetCharacterXY(int dx, int dy)
	{


		if (town_map[_cx + collision_move[0] + dx][_cy + collision_move[1] + dy] != -1							//左上
			&& town_map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + dy] != -1				//右上
			&& town_map[_cx + collision_move[0] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1				//左下
			&& town_map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1)		//右下
		{
			_cx += dx;
			_cy += dy;
		}

	}

}
