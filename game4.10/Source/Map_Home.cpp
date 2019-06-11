#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Home.h"
#include "Map_Home_Logic.h"
#include "algorithm"
#include "Black_Man.h"
#include "Blockhead.h"
#include "Slime.h"
#include "Boss.h"

namespace game_framework {

	Map_Home::Map_Home(int x, int y) : GameMap(x, y) {}

	Map_Home::~Map_Home(){}

	void Map_Home::AddEnemy() 
	{
		vector<Enemy*>::iterator e_it;
		for (e_it = _enemies.begin(); e_it != _enemies.end(); e_it++)
			(*e_it)->Dead();
		
		_enemies.push_back(new Blockhead(650, 918, AREA_1, this));
		_enemies.push_back(new Blockhead(850, 830, AREA_1, this));
		_enemies.push_back(new Blockhead(870, 910, AREA_1, this));
		_enemies.push_back(new Blockhead(850, 1000, AREA_1, this));
		_enemies.push_back(new Boss(800, 950, AREA_1, this));
		for each (Enemy* enemy in _enemies)
			enemy->LoadBitmap();
	}

	void Map_Home::LoadBitmap()
	{
		LoadBitmapPressF();
		_background.LoadBitmap(MAP_HOME);
		_wall.LoadBitmap(MAP_HOME_WALL, RGB(50, 255, 0));
	}

	void Map_Home::OnMove()
	{
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);

		//AREA_1
		if ((_cxy[0] >= 633) && (_cxy[1] >= 811) && (_cxy[0] <= 926) && (_cxy[1]) <= 1081)
		{
			for (int i = 0; i < _enemies.size(); i++)
			{
				if (_enemies[i]->Area() == AREA_1)
				{
					_enemies[i]->NotifyCharge();
				}
			}
		}	

		int temp_x = 0, temp_y = 0;

		if (_character_status == 1 || _character_status == 2 || _character_status == 3)
		{
			switch (_character_status)
			{
			case 1:						//傳送門
				temp_x = 768;
				temp_y = 360;
				_ani_press_f.OnMove();
				break;
			case 2:						//道具箱
				temp_x = 865;
				temp_y = 1137;
				_ani_press_f.OnMove();
				break;
			case 3:						// 書
				temp_x = 1235;
				temp_y = 840;
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

		OnMoveBackgroundAndWall();
		SkillOnMove();
		EnemyOnMove();
		RewardsOnMove();
	}
		
	int Map_Home::GetMapStatus(float x, float y)
	{
		return HOME_LOGIC[int(x/10)][int(y/10)];
	}
}
