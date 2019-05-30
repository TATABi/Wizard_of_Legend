#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include "audio.h"
#include "gamelib.h"
#include "Reward_Blood_Ball.h"
#include "GameMap.h"
#include "GameData.h"
#include "CharacterData.h"

#define RANGE_EAT 100
#define RANGE_POSITION 60
#define TIME  3
#define VALUE 50

namespace game_framework {
	Reward_Blood_Ball::Reward_Blood_Ball(float ex, float ey, GameMap* map) : _map(map), Reward(ex, ey, map)
	{
		LoadBitmap();
		Initialize(ex, ey);
		SetRandomPosition();
	}

	void Reward_Blood_Ball::Initialize(float ex, float ey)
	{
		_hitbox[0] = 3;
		_hitbox[1] = 3;
		_hitbox[2] = 13;
		_hitbox[3] = 13;
		_xy[0] = ex;
		_xy[1] = ey;
		srand(time(NULL));
		_value = VALUE;
		_range_eat = RANGE_EAT;
		_range_position = RANGE_POSITION;
		_time = TIME;
		_isShow = true;
		_state = BORN;
		_isUp = true;
		SetRandomPosition();
	}
	void Reward_Blood_Ball::LoadBitmap()
	{
		_bm_reward.LoadBitmap(BLOODBALL, RGB(0,0,0));
	}

	void Reward_Blood_Ball::Effect() 
	{
		CharacterData::Instance()->AddHP(VALUE);
	}
}