#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include <iostream>
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
		


	}

	void GameMap::LoadBitmap()
	{
		_background.LoadBitmap(INGAME_MAP_HOME);

	}

	void GameMap::OnMove()
	{

		_background.SetTopLeft(CHARACTER_SCREEN_X - _cx*10, CHARACTER_SCREEN_Y - _cy*10);

	}

	void GameMap::OnShow()
	{
		_background.ShowBitmap();
	}

	void GameMap::SetCharacterXY(int dx, int dy) 
	{	
		
		if (_map.map[_cx + collision_move[0] + dx][_cy + collision_move[1] + dy] != -1							//左上
			&& _map.map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + dy] != -1				//右上
			&& _map.map[_cx + collision_move[0] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1				//左下
			&& _map.map[_cx + collision_move[0] + collision_move[2] + dx][_cy + collision_move[1] + collision_move[3] + dy] != -1)		//右下
		{
				_cx += dx;
				_cy += dy;
		}
		
	}
}