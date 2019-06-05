#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Reward_Money.h"
#include "GameMap.h"
#include "GameData.h"
#include <cmath>
#include "CharacterData.h"
#define RANGE_EAT 100
#define RANGE_POSITION 100
#define TIME  3
#define VALUE 1

namespace game_framework {

	Reward_Money::Reward_Money(float ex, float ey, GameMap *map) : _map(map), Reward(ex, ey, map)
	{
		LoadBitmap();
		Initialize(ex, ey);
		SetRandomPosition();
	}

	void Reward_Money::Initialize(float ex, float ey)
	{
		_hitbox[0] = 5;
		_hitbox[1] = 5;
		_hitbox[2] = 9;
		_hitbox[3] = 9;
		_xy[0] = ex;
		_xy[1] = ey;
		_value = VALUE;
		_range_eat = RANGE_EAT;
		_range_position = RANGE_POSITION;
		_time = TIME;
		_isShow = true;
		_state = BORN;
		_isUp = true;
		SetRandomPosition();
	}

	void Reward_Money::LoadBitmap()
	{
		_bm_reward.LoadBitmap(UI_MONEY, RGB(50, 255, 0));
	}

	void Reward_Money::Effect()
	{
		CharacterData::Instance()->AddMoney(VALUE);
		CharacterData::Instance()->AddMoneyCollected(VALUE);
	}

}