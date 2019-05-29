#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Reward.h"
#include "GameMap.h"
#include "GameData.h"

namespace game_framework {
	Reward::Reward(float ex, float ey, GameMap* map) : _map(map) { }

	void Reward::OnMove()
	{
		float cx = _map->GetCharacterPosition()[0];
		float cy = _map->GetCharacterPosition()[1];
		float midCX = cx + CHARACTER_HITBOX[2] / 2;
		float midCY = cy + CHARACTER_HITBOX[3] / 2;
		_bm_reward.SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cx, CHARACTER_SCREEN_Y + _xy[1] - cy);
		if (_isShow) 
		{
			switch (_state)
			{
			case BORN:
				_state = MOVE;
				break;

			case EATEN:
				MoveTarget(midCX, midCY);
				IsTargetPosition(midCX, midCY) ? Effect(), _isShow =false: NULL;
				break;

			case MOVE:
				IsEaten() ? _state = EATEN : MoveTarget(_targetX, _targetY), _state = IDLE;
				break;

			case IDLE:
				IsEaten() ? _state = EATEN : NULL;
				break;
			}
		}
	}

	void Reward::OnShow()
	{
		if (_isShow)
			_bm_reward.ShowBitmap();
	}

	bool Reward::IsTargetPosition(float targetX, float targetY)
	{
		float d = 10;
		if (((abs(_xy[0] - targetX)) < d) && (abs(_xy[1] - targetY) < d))
			return true;
		return false;
	}

	bool Reward::IsEaten()
	{
		//角色中心位置
		float midCX = _map->GetCharacterPosition()[0] + CHARACTER_HITBOX[0] + CHARACTER_HITBOX[2] / 2;
		float midCY = _map->GetCharacterPosition()[1] + CHARACTER_HITBOX[1] + CHARACTER_HITBOX[3] / 2;
		for (int i = _hitbox[0]; i < _hitbox[2]; i++)
		{
			for (int j = _hitbox[1]; j < _hitbox[3]; j++)
			{
				if (pow(_xy[0] + i - midCX, 2) + pow(_xy[1] + j - midCY, 2) < pow(_range_eat, 2))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	/*
	void Reward::SetRandomPosition() 
	{
		_targetX = rand() % _range_position + _xy[0];
		_targetY = rand() % _range_position + _xy[1];
		while (!_map->SetEnemyXY(_targetX, _targetY, _hitbox))
		{
			_targetX = rand() % _range_position + _xy[0];
			_targetY = rand() % _range_position + _xy[1];
		}
	}*/
}