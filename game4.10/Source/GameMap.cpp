#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

namespace game_framework {
	GameMap::GameMap()
	{
	
	}

	GameMap::~GameMap() {

	}

	void GameMap::LoadBitmap()
	{
		_background.LoadBitmap(INGAME_MAP_HOME);
		_wall.LoadBitmap(INGAME_MAP_HOME_WALL, RGB(50, 255, 0));
	}

	bool GameMap::IsEmpty(int x, int y)
	{
<<<<<<< HEAD
		int gx = x / 10;
		int gy = y / 10;
		return _map.map[gx][gy] == 0;
	}

	void GameMap::SetScreenPosition(int x, int y)
	{
		_sx = x;
		_sy = y;
		_background.SetTopLeft(-_sx, -_sy);
		_wall.SetTopLeft(-_sx, -_sy);
	}

	void GameMap::OnShowBackground()
	{
		_background.ShowBitmap();
	}

	void GameMap::OnShowWall()
	{
		_wall.ShowBitmap();
	}

	int GameMap::GetScreenX() 
	{
		return _sx;
	}

	int GameMap::GetScreenY()
	{
		return _sy;
	}
}

