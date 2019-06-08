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
		_wall.LoadBitmap(MAP_LEVEL_01, RGB(50, 255, 0));
	}

	void Map_Level_One::OnMove()
	{
		
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);

		int temp_x = 0, temp_y = 0;

		OnMoveBackgroundAndWall();

		SkillOnMove();

		EnemyOnMove();
	}

	int Map_Level_One::GetMapStatus(float x, float y)
	{
		return LEVEL_ONE_LOGIC[int(x/10)][int(y/10)];
	}
}
