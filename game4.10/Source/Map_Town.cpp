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
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			delete *iter;
	}

	void Map_Town::LoadBitmap()
	{
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			(*iter)->LoadBitmap();

		ParentLoadBitmap();
		_background.LoadBitmap(MAP_TOWN);
		_wall.LoadBitmap(MAP_TOWN_WALL, RGB(50, 255, 0));
	}

	void Map_Town::OnMove(std::vector<Skill*> skills)
	{
		ParentOnMove();
		character_status = town_map[cxy[0] + collision_move[0] + 10][cxy[1] + collision_move[1] + 3];
		int temp_x = 0, temp_y = 0;
		if (character_status == 1 || character_status == 2 || character_status == 3 || character_status == 4 || character_status == 5)
		{
			switch (character_status)
			{
			case 1:						//傳送門(往家)
				temp_x = 797;
				temp_y = 1052;
				ani_press_f.OnMove();
				break;
			case 2:						//傳送門(往關卡)
				temp_x = 797;
				temp_y = 561;
				ani_press_f.OnMove();
				break;
			case 3:						// 道具1
				temp_x = 530;
				temp_y = 970;
				ani_press_f.OnMove();
				break;
			case 4:						// 道具2
				temp_x = 580;
				temp_y = 970;
				ani_press_f.OnMove();
				break;
			case 5:						// 道具3
				temp_x = 626;
				temp_y = 970;
				ani_press_f.OnMove();
				break;
			}
			isPressF = true;
			ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - cxy[0], CHARACTER_SCREEN_Y + temp_y - cxy[1]);
		}
		else
		{
			ani_press_f.Reset();
			isPressF = false;
		}


		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			(*iter)->OnMove(cxy[0], cxy[1], skills);


	}


	void Map_Town::OnShow(std::vector<Skill*> *skills)
	{
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			(*iter)->OnShow();
	}

	int* Map_Town::SetCharacterXY(int dx, int dy)
	{


		if (town_map[cxy[0] + collision_move[0] + dx][cxy[1] + collision_move[1] + dy] != -1							//左上
			&& town_map[cxy[0] + collision_move[0] + collision_move[2] + dx][cxy[1] + collision_move[1] + dy] != -1				//右上
			&& town_map[cxy[0] + collision_move[0] + dx][cxy[1] + collision_move[1] + collision_move[3] + dy] != -1				//左下
			&& town_map[cxy[0] + collision_move[0] + collision_move[2] + dx][cxy[1] + collision_move[1] + collision_move[3] + dy] != -1)		//右下
		{
			cxy[0] += dx;
			cxy[1] += dy;
		}

		return cxy;

	}

	int Map_Town::GetMapStatus(int x, int y)
	{
		return town_map[x][y];
	}


}
