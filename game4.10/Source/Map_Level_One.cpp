#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Level_One.h"
#include "Map_Level_One_Logic.h"
#include "algorithm"

namespace game_framework {

	Map_Level_One::Map_Level_One(int x, int y) : GameMap(x, y){ }

	Map_Level_One::~Map_Level_One() {
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
			delete *iter;
	}

	void Map_Level_One::AddEnemy()
	{
	}

	void Map_Level_One::LoadBitmap()
	{
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
			(*iter)->LoadBitmap();

		LoadBitmapPressF();
		_background.LoadBitmap(MAP_LEVEL_01);
		_wall.LoadBitmap(MAP_LEVEL_01_WALL, RGB(50, 255, 0));
	}

	void Map_Level_One::OnMove()
	{
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);

		int temp_x = 0, temp_y = 0;

		/*
		if (_character_status == 1 || _character_status == 2 || _character_status == 3 || _character_status == 4 || _character_status == 5)
		{
			switch (_character_status)
			{
			case 1:						//傳送門(往家)
				temp_x = 797;
				temp_y = 1052;
				_ani_press_f.OnMove();
				break;
			case 2:						//傳送門(往關卡)
				temp_x = 797;
				temp_y = 561;
				_ani_press_f.OnMove();
				break;
			case 3:						// 道具1
				temp_x = 530;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			case 4:						// 道具2
				temp_x = 580;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			case 5:						// 道具3
				temp_x = 626;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			}
			_isPressF = true;
			_ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - _cxy[0], CHARACTER_SCREEN_Y + temp_y - _cxy[1]);
		}
		else
		{
			_ani_press_f.Reset();
			_isPressF = false;
		}
		*/

		OnMoveBackgroundAndWall();
		SkillOnMove();
		EnemyOnMove();
	}

	int Map_Level_One::GetMapStatus(float x, float y)
	{
		return LEVEL_ONE_LOGIC[int(x/10)][int(y/10)];
	}
}
