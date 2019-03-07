#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

namespace game_framework
{
	GameMap::GameMap()
	{
		Initialize();
	}
	void GameMap::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 0;
		_x = X_POS;
		_y = Y_POS;
	}
	int GameMap::GetX1()
	{
		return _x;
	}
	int GameMap::GetY1()
	{
		return _y;
	}
	void GameMap::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void GameMap::OnShow()
	{
		_pic.SetTopLeft(_x, _y);
		_pic.ShowBitmap();
	}
	
	void GameMap::RandomMap()
	{
		_pic.LoadBitmap(IDB_Map);
	}
}