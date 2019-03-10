#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

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
	}

	void GameMap::LoadBitmap()
	{
		_background.LoadBitmap(INGAME_MAP_HOME);
			//_wall.LoadBitmap();
			//_terrain.LoadBitmap();
	}

	void GameMap::OnMove()
	{
		
		_background.SetTopLeft(295-_cx, 215-_cy);

	}

	void GameMap::OnShow()
	{
		_background.ShowBitmap();
	}

	void GameMap::SetCharacterXY(int cx, int cy) 
	{	
		_cx += cx;
		_cy += cy;
		
	}
}