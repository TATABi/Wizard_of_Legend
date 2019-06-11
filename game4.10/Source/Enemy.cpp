#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "GameMap.h"
#include "Reward.h"
#include "Reward_Blood_Ball.h"
#include "Reward_Money.h"
#include "Reward_Diamond.h"
#include <random>
#include "CharacterData.h"

#define DEFEATED_COUNT 1

namespace game_framework {
	Enemy::Enemy(int x, int y, int area, GameMap* map) : _ori_x(x), _ori_y(y), _area(area), _map(map)
	{
		Initialize(x, y);
	}

	void Enemy::Initialize(int x, int y)
	{
		_xy[0] = x;
		_xy[1] = y;
		_is_detour = _is_left = _is_right = _is_up = _is_down = false;
		_detour_time = 0;
		_is_x_arrive = _is_y_arrive = false;
		_state = NOTHING;
		_hit_recover_flag = false;
		_is_transfer = false;
		_ani_hurt.SetDelayCount(1);
		_invincible_counter = 0;
		for (int i = 0; i < 4; i++)
			_neighbor[i] = true;
	}

	void Enemy::LoadBitmap()
	{
		LoadEnemyBitmap();
		int ani_hurt[7] = { GET_HURT_01, GET_HURT_02, GET_HURT_03, GET_HURT_04, GET_HURT_05, GET_HURT_06, GET_HURT_07 };
		for (int i = 0; i < 7; i++)
			_ani_hurt.AddBitmap(ani_hurt[i], RGB(50, 255, 0));
	}

	void Enemy::OnMove(int cx, int cy, vector<Skill*> &skills)
	{
		if (IsLive())
		{
			int currentX = _xy[0];
			int currentY = _xy[1];
			_invincible_counter > 0 ? _invincible_counter-- : NULL;
			// �ޯ�I���P�w
			std::vector<Skill*>::iterator iter;
			for (iter = skills.begin(); iter != skills.end(); iter++)
			{
				int ori_hp = _hp;
				_hp -= (*iter)->GetDamage(this);
				if (_hp != ori_hp && _invincible_counter == 0)
				{
					_state = HIT_RECOVER;
					_hit_recover_counter = 30 * 0.5;
					_hit_recover_flag = false;
				}
			}

			switch (_state)
			{
			case CHARGING:
				MoveToTarget(cx, cy);
				if (IsInAttackZone(cx, cy))
					_state = ATTACKING;
				if (pow(_xy[0] - _ori_x, 2) + pow(_xy[1] - _ori_y, 2) > pow(_charge_zone, 2) && _state != HIT_RECOVER) //���}�����d��
					_state = RESET;
				break;

			case RESET:
				MoveToTarget(_ori_x, _ori_y);
				if (currentX == _xy[0] && currentY == _xy[1])
					_state = NOTHING;
				break;
			
			case ATTACKING:
				//�����ʵe������^�� CHARGING ���A
				if (cx >= _xy[0] && !_isAttack)
					_direction = RIGHT;
				else if(cx < _xy[0] && !_isAttack)
					_direction = LEFT;
				break;

			case NOTHING:
				if (IsInAttackZone(cx, cy))
					_state = CHARGING;
				break;

			case HIT_RECOVER:	
				_hit_recover_counter > 0 ? _hit_recover_counter-- : NULL;
				_hit_recover_counter == 0 ? _state = CHARGING : NULL;
				break;
			}
			Move(cx, cy);
		}	
	}

	void Enemy::Dead()
	{
		_hp = 0;
		_isReset = true;
	}

	bool Enemy::IsReset()
	{
		return _isReset;
	}

	void Enemy::ResetAnimation()
	{
		_ani_hurt.Reset();
		_ani_left.Reset();
		_ani_right.Reset();
		_ani_attack_left.Reset();
		_ani_attack_right.Reset();
	}

	void Enemy::SetXY(int dx, int dy)
	{
		_xy[0] += dx;
		_xy[1] += dy;
	}

	int* Enemy::GetCollisionMove() 
	{
		return _move_hitbox;
	}

	int *Enemy::GetHitbox()
	{
		return _hitbox;
	}

	bool Enemy::IsInAttackZone(int target_x, int target_y)
	{
		int cMidX = target_x + 35;
		int cMidY = target_y + 35;
		int midX = _xy[0] + _hitbox[0] + _hitbox[2] / 2;
		int midY = _xy[1] + _hitbox[1] + _hitbox[3] / 2;
		if ((abs(midX - cMidX) < _zone) && (abs(midY - cMidY) < _zone))
			return true;
		else
			return false;		
	}
	
	bool Enemy::CanAchieved(int dx, int dy)
	{
		return _map->CheckEnemyPosition(_xy[0] + dx, _xy[1] + dy, _move_hitbox);
	}

	bool Enemy::IsLive()
	{
		return _hp > 0;
	}

	void Enemy::NotifyCharge()
	{
		if(_state != HIT_RECOVER && _state != ATTACKING)
			_state = CHARGING;
	}

	int Enemy::Area()
	{
		return _area;
	}

	vector<Reward*> Enemy::CreateReward()	//�w�]
	{
		int midX = _xy[0] + _hitbox[0] + _hitbox[2] / 2;	//�ĤH���ߦ�m
		int midY = _xy[1] + _hitbox[1] + _hitbox[3] / 2;
		vector<Reward*> rewards;
		//Default reward: Blood Ball 10%, Diamond 20%, Money 70%
		std::random_device rd;

		//���ͦ�y
		for (int i = 0; i < 5; i++)
		{
			int prob = rd() % 100 + 1;		//��1~100		
			if (prob <= 10)
				rewards.push_back(new Reward_Blood_Ball(midX, midY, _map));
		}

		//�����p��
		for (int i = 0; i < 5; i++)
		{
			int prob = rd() % 100 + 1;
			if (prob <= 30)
				rewards.push_back(new Reward_Diamond(midX, midY, _map));
		}

		//���ͪ���
		for (int i = 0; i < 5; i++)
		{
			int prob = rd() % 100 + 1;				
			if (prob <= 70)
				rewards.push_back(new Reward_Money(midX, midY, _map));
		}

		//�W�[���ļ�
		CharacterData::Instance().AddEnemiesDefeated(DEFEATED_COUNT);
		return rewards;
	}

	void Enemy::PlayDeadAudio()
	{
	}

	void Enemy::MoveToTarget(int target_x, int target_y)
	{
		int currentX = _xy[0];
		int currentY = _xy[1];
		int midX = _xy[0] + _hitbox[0] + _hitbox[2] / 2;
		int midY = _xy[1] + _hitbox[1] + _hitbox[3] / 2;
		int cMidX = target_x + 35;
		int cMidY = target_y + 35;
		int detourTime = 60;

		if (!_is_detour)
		{
			int temp_step = _step;

			//�ר���C�t��
			if ((abs(midX - cMidX) > _zone) && (abs(midY - cMidY) > _zone))
				temp_step = (float)(_step) * 0.6 + 0.5;

			if ((abs(midX - cMidX) > _zone))
			{
				_is_x_arrive = false;
				if (midX > cMidX)
				{
					if (CanAchieved(-temp_step, 0))
					{
						_direction = LEFT;
						_xy[0] -= temp_step;
					}
					else
					{
						_neighbor[2] = false;
					}
				}
				else if (midX < cMidX)
				{
					if (CanAchieved(temp_step, 0))
					{
						_direction = RIGHT;
						_xy[0] += temp_step;
					}
					else
					{
						_neighbor[3] = false;
					}
				}
			}
			else
			{
				_is_x_arrive = true;
			}
			if ((abs(midY - cMidY) > _zone))
			{
				_is_y_arrive = false;
				if (midY > cMidY)
				{
					if (CanAchieved(0, -temp_step))
					{
						_xy[1] -= temp_step;
					}
					else
					{
						_neighbor[0] = false;
					}
				}
				else if (midY < cMidY)
				{
					if (CanAchieved(0, temp_step))
					{
						_xy[1] += temp_step;
					}
					else
					{
						_neighbor[1] = false;
					}
				}
			}
			else
			{
				_is_y_arrive = true;
			}
		}
		else
		{
			if (_is_up)
			{
				CanAchieved(0, -_step) ? _xy[1] -= _step : NULL;
			}
			else if (_is_down)
			{
				CanAchieved(0, _step) ? _xy[1] += _step : NULL;
			}
			else if(_is_left)
			{
				_direction = LEFT;
				CanAchieved(-_step, 0) ? _xy[0] -= _step : NULL;
			}
			else if (_is_right)
			{
				_direction = RIGHT;
				CanAchieved(_step, 0) ? _xy[0] += _step : NULL;
			}
			_detour_time--;
			if (_detour_time < 0)
			{
				_is_detour = false;
				for (int i = 0; i < 4; i++)
				{
					_neighbor[i] = true;
				}
				_is_left = false;
				_is_right = false;
				_is_up = false;
				_is_down = false;
			}
		}

		if ((currentX == _xy[0]) && (currentY == _xy[1]) && ((!_is_x_arrive) || (!_is_y_arrive)))
		{
			_is_detour = true;
			if (_neighbor[0] == false)	//�W�d��
			{
				for (int i = 0; i < detourTime; i++)
				{
					//�V�k�ˬd
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_right = true;
							break;
						}
					}
					//�V���ˬd
					if (CanAchieved(-_step * (i + 1), 0))
					{
						if (CanAchieved(-_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_left = true;
							break;
						}
					}
				}
			}
			if (_neighbor[1] == false)	//�U�d��
			{
				for (int i = 0; i < detourTime; i++)
				{
					//�V�k�ˬd
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), _step))
						{
							_is_right = true;
							_detour_time = i;
							break;
						}
					}
					//�V���ˬd
					if (CanAchieved(-_step * (i + 1), 0))
					{
						if (CanAchieved(-_step * (i + 1), _step))
						{
							_detour_time = i;
							_is_left = true;
							break;
						}
					}
				}
			}
			if (_neighbor[2] == false)	//���d��
			{
				for (int i = 0; i < detourTime; i++)
				{
					//�V�W�ˬd
					if (CanAchieved(0 , -_step * (i + 1)))
					{
						if (CanAchieved(-_step , -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//�V�U�ˬd
					if (CanAchieved(0, _step * (i + 1)))
					{
						if (CanAchieved(-_step, _step * (i + 1)))
						{
							_detour_time = i;
							_is_down = true;
							break;
						}
					}
				}
			}
			if (_neighbor[3] == false)	//�k�d��
			{		
				for (int i = 0; i < detourTime; i++)
				{
					//�V�W�ˬd
					if (CanAchieved(0, -_step * (i + 1)))
					{
						if (CanAchieved(_step, -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//�V�U�ˬd
					if (CanAchieved(0, _step * (i + 1)))
					{
						if (CanAchieved(_step, _step * (i + 1)))
						{
							_detour_time = i;
							_is_down = true;
							break;
						}
					}
				}
			}		
		}
	}
}