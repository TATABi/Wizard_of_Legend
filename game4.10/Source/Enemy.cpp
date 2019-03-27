#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"


namespace game_framework {

	Enemy::Enemy(int x, int y)
	{
		Initialize(x, y);
	}

	void Enemy::Initialize(int x, int y)
	{
		map_x = x;
		map_y = y;
	}

	void Enemy::LoadBitmap()
	{
		bm_stand.LoadBitmap(ENEMY_BLOCKHEAD, RGB(50, 255, 0));
	}
	
	void Enemy::OnMove(int cx, int cy)
	{
		bm_stand.SetTopLeft(CHARACTER_SCREEN_X + map_x - cx, CHARACTER_SCREEN_Y + map_y - cy);
		
	}

	void Enemy::OnShow()
	{
		bm_stand.ShowBitmap();

	}

	

}