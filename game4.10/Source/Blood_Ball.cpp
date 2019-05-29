#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blood_Ball.h"
#include "GameMap.h"
#include "GameData.h"
#include <cmath>

#define RANGE_EAT 100
#define RANGE_POSITION 50
#define SPEED  10
#define VALUE 50

namespace game_framework {
	BloodBall::BloodBall(float ex, float ey, GameMap* map) : _map(map), Reward(ex, ey, map)
	{
		LoadBitmap();
		Initialize(ex, ey);
		SetRandomPosition();
	}

	void BloodBall::Initialize(float ex, float ey)
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
		_speed = SPEED;
		_isShow = true;
		_state = BORN;
		_isUp = true;
		SetRandomPosition();
	}
	void BloodBall::LoadBitmap()
	{
		_bm_reward.LoadBitmap(BLOODBALL, RGB(0,0,0));
	}

	void BloodBall::MoveTarget(float targetX, float targetY)
	{
		float dx = (targetX - _xy[0]) / _speed;
		float dy = (targetY - _xy[1]) / _speed;
		_xy[0] += dx;
		_xy[1] += dy;
	}

	void BloodBall::Effect() 
	{

	}

	void BloodBall::SetRandomPosition()
	{
		_targetX = rand() % _range_position + _xy[0];
		_targetY = rand() % _range_position + _xy[1];
		while (!_map->SetEnemyXY(_targetX, _targetY, _hitbox))
		{
			_targetX = rand() % _range_position + _xy[0];
			_targetY = rand() % _range_position + _xy[1];
		}
	}
}