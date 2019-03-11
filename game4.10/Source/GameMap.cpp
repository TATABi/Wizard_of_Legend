#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include <iostream>
namespace game_framework {
	
	GameMap::GameMap(int x, int y) {
		Initialize(x, y);
	}
	
	GameMap::~GameMap() {
	
	}

	void GameMap::Initialize(int x, int y) 
	{
		_cx = x;
		_cy = y;

		//設定地圖碰撞邊界
		for (int i = 40; i < 60; i++) {
			for (int j = 0; j < 160; j++)
				_map[i][j] = -1;
		}

		cm[0] = 1;
		cm[1] = 3;
		cm[2] = 2;
		cm[3] = 1;

	}

	void GameMap::LoadBitmap()
	{
		_background.LoadBitmap(INGAME_MAP_HOME);

	}

	void GameMap::OnMove()
	{

		_background.SetTopLeft(295 - _cx*10, 215 - _cy*10);

	}

	void GameMap::OnShow()
	{
		_background.ShowBitmap();
	}

	void GameMap::SetCharacterXY(int dx, int dy) 
	{	
		if (_map[_cx + cm[0] + dx][_cy + cm[1] + dy] != -1							//左上
			&& _map[_cx + cm[0] + cm[2] + dx][_cy + cm[1] + dy] != -1				//右上
			&& _map[_cx + cm[0] + dx][_cy + cm[1] + cm[3] + dy] != -1				//左下
			&& _map[_cx + cm[0] + cm[2] + dx][_cy + cm[1] + cm[3] + dy] != -1)		//右下
		{
				_cx += dx;
				_cy += dy;
		}

	}
}