#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include "audio.h"
#include "gamelib.h"
#include "Reward_Diamond.h"
#include "GameMap.h"
#include "GameData.h"
#include "CharacterData.h"

#define RANGE_EAT 100
#define RANGE_POSITION 100
#define TIME  3
#define VALUE 1

namespace game_framework {

	Reward_Diamond::Reward_Diamond(float ex, float ey, GameMap *map) : _map(map), Reward(ex, ey, map)
	{
		LoadBitmap();
		Initialize(ex, ey);
	}

	void Reward_Diamond::Initialize(float ex, float ey)
	{
		_hitbox[0] = 6;
		_hitbox[1] = 4;
		_hitbox[2] = 7;
		_hitbox[3] = 12;
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

	void Reward_Diamond::LoadBitmap()
	{
		_bm_reward.LoadBitmap(UI_DIAMOND, RGB(50, 255, 0));
	}

	void Reward_Diamond::Effect()
	{
		CharacterData::Instance()->AddDiamond(VALUE);
		CharacterData::Instance()->AddDiamondCollected(VALUE);
	}
}