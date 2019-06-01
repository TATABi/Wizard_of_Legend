#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Reward.h"
#include "GameMap.h"
#include "GameData.h"
#include <random>

namespace game_framework {
	Reward::Reward(float ex, float ey, GameMap* map) : _map(map) { }

	void Reward::OnMove()
	{
		float cx = _map->GetCharacterPosition()[0];
		float cy = _map->GetCharacterPosition()[1];
		float midCX = cx + CHARACTER_HITBOX[2] / 2;
		float midCY = cy + CHARACTER_HITBOX[3] / 2;
		_bm_reward.SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cx, CHARACTER_SCREEN_Y + _xy[1] - cy);
		delay_counter > 0 ? delay_counter-- : NULL;
		if (_isShow) 
		{
			switch (_state)
			{
			case BORN:
				_state = MOVE;
				break;

			case EATEN:
				if (delay_counter == 0)
				{
					MoveTarget(midCX, midCY);
					if (IsTargetPosition(midCX, midCY))
					{
						Effect();
						_isShow = false;
					}
				}
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

	void Reward::MoveTarget(float targetX, float targetY)
	{
		int temp = _time;
		if (_move_counter != 0)
		{
			_move_counter--;
		}
		else
		{
			_time = 1;
		}
		float dx = (targetX - _xy[0]) / _time;	//單位時間移動距離
		float dy = (targetY - _xy[1]) / _time;
		_xy[0] += dx;
		_xy[1] += dy;
		_move_counter--;
	}

	bool Reward::IsTargetPosition(float targetX, float targetY)
	{
		float d = 20;
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
	
	bool Reward::IsDelete()
	{
		float cx = _map->GetCharacterPosition()[0];
		float cy = _map->GetCharacterPosition()[1];
		float midCX = cx + CHARACTER_HITBOX[2] / 2;
		float midCY = cy + CHARACTER_HITBOX[3] / 2;
		if ((_isShow) && (IsTargetPosition(midCX, midCY)) && delay_counter == 0)
			return true;
		else
			return false;
	}

	void Reward::SetRandomPosition()
	{
		std::random_device rd;
		_targetX = rd() % _range_position + _xy[0];
		_targetY = rd() % _range_position + _xy[1];
		while (!_map->SetEnemyXY(_targetX, _targetY, _hitbox))
		{
			_targetX = rd() % _range_position + _xy[0];
			_targetY = rd() % _range_position + _xy[1];
		}
	}
}