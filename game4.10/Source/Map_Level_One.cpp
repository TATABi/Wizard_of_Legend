#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Level_One.h"
#include "Map_Level_One_Logic.h"
#include "algorithm"
#include "Black_Man.h"
#include "Slime.h"
#include "Boss.h"

namespace game_framework {

	Map_Level_One::Map_Level_One(int x, int y) : GameMap(x, y){ }

	void Map_Level_One::AddEnemy()
	{
		vector<Enemy*>::iterator e_it;
		for (e_it = _enemies.begin(); e_it != _enemies.end(); e_it++)
			(*e_it)->Dead();

		//Area 1
		_enemies.push_back(new Black_Man(2963, 3202, AREA_1, this));
		_enemies.push_back(new Black_Man(2947, 3210, AREA_1, this));
		//Area 2
		_enemies.push_back(new Black_Man(3545, 2761, AREA_2, this));
		_enemies.push_back(new Slime(3751, 2770, AREA_2, this));
		_enemies.push_back(new Slime(3703, 2804, AREA_2, this));
		_enemies.push_back(new Slime(3770, 2830, AREA_2, this));
		//Area 3
		_enemies.push_back(new Black_Man(2017, 2510, AREA_3, this));
		_enemies.push_back(new Black_Man(2123, 2509, AREA_3, this));
		_enemies.push_back(new Black_Man(2124, 2650, AREA_3, this));
		_enemies.push_back(new Slime(1856, 2591, AREA_3, this));
		//Area 4
		_enemies.push_back(new Slime(1367, 2515, AREA_4, this));
		_enemies.push_back(new Slime(1380, 2635, AREA_4, this));
		_enemies.push_back(new Slime(1400, 2539, AREA_4, this));
		_enemies.push_back(new Slime(1430, 2506, AREA_4, this));
		//Area 5
		_enemies.push_back(new Black_Man(840, 2720, AREA_5, this));
		_enemies.push_back(new Black_Man(840, 2824, AREA_5, this));
		_enemies.push_back(new Black_Man(840, 2960, AREA_5, this));
		//Area 6
		_enemies.push_back(new Slime(154, 2529, AREA_6, this));
		_enemies.push_back(new Slime(146, 2586, AREA_6, this));
		_enemies.push_back(new Slime(202, 2555, AREA_6, this));
		_enemies.push_back(new Slime(223, 2603, AREA_6, this));
		_enemies.push_back(new Slime(261, 2531, AREA_2, this));
		//Area 7
		_enemies.push_back(new Black_Man(767, 2148, AREA_7, this));
		//Area 8
		_enemies.push_back(new Slime(1459, 1740, AREA_8, this));
		_enemies.push_back(new Slime(1484, 1795, AREA_8, this));
		_enemies.push_back(new Slime(1667, 1929, AREA_8, this));
		//Area 9
		_enemies.push_back(new Black_Man(1958, 1736, AREA_9, this));
		_enemies.push_back(new Black_Man(2152, 1806, AREA_9, this));
		_enemies.push_back(new Black_Man(2304, 1733, AREA_9, this));
		//Area 10
		_enemies.push_back(new Slime(2059, 1239, AREA_10, this));
		_enemies.push_back(new Slime(2069, 1687, AREA_10, this));
		//Area 11
		_enemies.push_back(new Slime(2734, 1427, AREA_11, this));
		_enemies.push_back(new Slime(2890, 1568, AREA_11, this));

		for each (Enemy* enemy in _enemies)
			enemy->LoadBitmap();
	}

	void Map_Level_One::LoadBitmap()
	{
		LoadBitmapPressF();
		_background.LoadBitmap(MAP_LEVEL_01);
		_wall.LoadBitmap(MAP_LEVEL_01_WALL, RGB(50, 255, 0));
	}

	void Map_Level_One::OnMove()
	{
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);

		int temp_x = 0, temp_y = 0;

		NotifyAnemy(AREA_1, LEVEL_AREA_1);
		NotifyAnemy(AREA_2, LEVEL_AREA_2);
		NotifyAnemy(AREA_3, LEVEL_AREA_3);
		NotifyAnemy(AREA_4, LEVEL_AREA_4);
		NotifyAnemy(AREA_5, LEVEL_AREA_5);
		NotifyAnemy(AREA_6, LEVEL_AREA_6);
		NotifyAnemy(AREA_7, LEVEL_AREA_7);
		NotifyAnemy(AREA_8, LEVEL_AREA_8);
		NotifyAnemy(AREA_9, LEVEL_AREA_9);
		NotifyAnemy(AREA_10, LEVEL_AREA_10);
		NotifyAnemy(AREA_11, LEVEL_AREA_11);
		//NotifyAnemy(AREA_BOSS, LEVEL_AREA_BOSS);

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
		RewardsOnMove();
	}

	int Map_Level_One::GetMapStatus(float x, float y)
	{
		return LEVEL_ONE_LOGIC[int(x/10)][int(y/10)];
	}

	void Map_Level_One::NotifyAnemy(AREA name, const int* area)
	{
		if ((_cxy[0] >= area[0]) && (_cxy[1] >= area[1]) && (_cxy[0] <= area[2]) && (_cxy[1]) <= area[3])
		{
			for (int i = 0; i < _enemies.size(); i++)
				if (_enemies[i]->Area() == name)
					_enemies[i]->NotifyCharge();
		}

	}
}
