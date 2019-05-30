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

#define CHARGING_ZONE 300

namespace game_framework {
	Enemy::Enemy(int x, int y, int area, GameMap* map) : _ori_x(x), _ori_y(y), _area(area), _map(map)
	{
		Initialize(x, y);
	}

	Enemy::~Enemy(){}

	void Enemy::Initialize(int x, int y)
	{
		_xy[0] = x;
		_xy[1] = y;
		_is_detour = _is_left = _is_right = _is_up = _is_down = false;
		_detour_time = 0;
		_is_x_arrive = _is_y_arrive = false;
		_state = NOTHING;
		_hit_recover_counter = 0;
		_hit_recover_flag = false;
		_hp = 100;
		_step = 20;
		_zone = 30;
		_damage = 10;
		
		for (int i = 0; i < 4; i++)
			_neighbor[i] = true;
	}

	void Enemy::LoadBitmap()
	{
		LoadBitmap_2();

		int ani[7] = { GET_HURT_01, GET_HURT_02, GET_HURT_03, GET_HURT_04, GET_HURT_05, GET_HURT_06, GET_HURT_07 };
		for (int i = 0; i < 7; i++)
			_ani_hurt.AddBitmap(ani[i], RGB(50, 255, 0));
		_ani_hurt.SetDelayCount(1);
	}

	void Enemy::OnMove(int cx, int cy, vector<Skill*> &skills)
	{
		if (IsLive())
		{
			int currentX = _xy[0];
			int currentY = _xy[1];

			// 技能碰撞判定
			std::vector<Skill*>::iterator iter;
			for (iter = skills.begin(); iter != skills.end(); iter++)
			{
				int ori_hp = _hp;
				_hp -= (*iter)->GetDamage(this);
				if (_hp != ori_hp)
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
				if (pow(_xy[0] - _ori_x, 2) + pow(_xy[1] - _ori_y, 2) > pow(CHARGING_ZONE, 2) && _state != HIT_RECOVER) //離開攻擊範圍
					_state = RESET;
				break;

			case RESET:
				MoveToTarget(_ori_x, _ori_y);
				if (currentX == _xy[0] && currentY == _xy[1])
					_state = NOTHING;
				break;
			
			case ATTACKING:
				//攻擊動畫結束後回到 CHARGING 狀態
				if (cx >= _xy[0])
					_direction = RIGHT;
				else
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
			//Move(CHARACTER_SCREEN_X + _xy[0] - cx, CHARACTER_SCREEN_Y + _xy[1] - cy);	
			Move(cx, cy);
		}	
	}

	void Enemy::SetXY(int dx, int dy)
	{
		_xy[0] += dx;
		_xy[1] += dy;
	}

	int* Enemy::GetCollisionMove() 
	{
		return _collision_move;
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
		return _map->SetEnemyXY(_xy[0] + dx, _xy[1] + dy, _collision_move);
		/*
		int x1 = _xy[0] + _collision_move[0];
		int y1 = _xy[1] + _collision_move[1];
		int x2 = x1 + _collision_move[2];
		int y2 = y1 + _collision_move[3];
		if ((HOME_LOGIC[x1 + dx][y1 + dy] != -1) &&
			(HOME_LOGIC[x2 + dx][y1 + dy] != -1) &&
			(HOME_LOGIC[x1 + dx][y2 + dy] != -1) &&
			(HOME_LOGIC[x2 + dx][y2 + dy] != -1))
		{
			return true;
		}
		return false;
		*/
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

	vector<Reward*> Enemy::CreateReward()
	{
		int midX = _xy[0] + _hitbox[0] + _hitbox[2] / 2;	//敵人中心位置
		int midY = _xy[1] + _hitbox[1] + _hitbox[3] / 2;	
		vector<Reward*> rewards;
		/*srand(time(NULL));
		int prob = rand() % 100 + 1;						//取1~100
		if (prob <= 10)										//Default reward: Blood Ball 10%, Diamond 20%, Money 70%
			rewards.push_back(new Reward_Blood_Ball(midX, midY, _map));
		else if (prob <= 30)
			rewards.push_back(new Reward_Diamond(midX, midY, _map));
		else
			rewards.push_back(new Reward_Money(midX, midY, _map));*/

		//可重複產生
		for (int i = 0; i < 5; i++)
		{
			rewards.push_back(new Reward_Diamond(midX, midY, _map));
		}
		return rewards;
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

			//斜走放慢速度
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
			if (_neighbor[0] == false)	//上卡住
			{
				for (int i = 0; i < detourTime; i++)
				{
					//向右檢查
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_right = true;
							break;
						}
					}
					//向左檢查
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
			if (_neighbor[1] == false)	//下卡住
			{
				for (int i = 0; i < detourTime; i++)
				{
					//向右檢查
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), _step))
						{
							_is_right = true;
							_detour_time = i;
							break;
						}
					}
					//向左檢查
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
			if (_neighbor[2] == false)	//左卡住
			{
				for (int i = 0; i < detourTime; i++)
				{
					//向上檢查
					if (CanAchieved(0 , -_step * (i + 1)))
					{
						if (CanAchieved(-_step , -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//向下檢查
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
			if (_neighbor[3] == false)	//右卡住
			{		
				for (int i = 0; i < detourTime; i++)
				{
					//向上檢查
					if (CanAchieved(0, -_step * (i + 1)))
					{
						if (CanAchieved(_step, -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//向下檢查
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
		if (currentX == _xy[0] && currentY == _xy[1])
		{
			_state == RESET ? _xy[0] = _ori_x, _xy[1] = _ori_y : _state = ATTACKING;	//加上動畫
		}
	}
}