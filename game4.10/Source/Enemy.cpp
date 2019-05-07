#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include <cmath>
#include "Map_Home_Logic.h"

#define CHARGING_ZONE 300

namespace game_framework {
	Enemy::Enemy(int x, int y, int area, int zone) : _ori_x(x), _ori_y(y), _area(area), _zone(zone)
	{
		Initialize(x, y);
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::Initialize(int x, int y)
	{
		_xy[0] = x;
		_xy[1] = y;
		_hp = 5;
		_is_detour = _is_left = _is_right = _is_up = _is_down = false;
		_detour_time = 0;
		_is_x_arrive = _is_y_arrive = false;

		for (int i = 0; i < 4; i++)
		{
			_neighbor[i] = true;
		}
	}

	void Enemy::LoadBitmap()
	{
		_bm_stand.LoadBitmap(ENEMY_BLOCKHEAD, RGB(50, 255, 0));
	}

	void Enemy::OnMove(int cx, int cy, vector<Skill*> &skills)
	{
		if (_hp > 0)
		{
			if (pow(_xy[0] - _ori_x, 2) + pow(_xy[1] - _ori_y, 2) > pow(CHARGING_ZONE, 2))
			{
				_state = RESET;
			}
			// 技能碰撞判定

			_bm_stand.SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cx, CHARACTER_SCREEN_Y + _xy[1] - cy);

			std::vector<Skill*>::iterator iter;
			for (iter = skills.begin(); iter != skills.end(); iter++)
			{
				int *skill_hitbox = (*iter)->GetHitbox();
				int *skill_position = (*iter)->GetPosition();

				int x1 = _xy[0] + _collision_damage[0];
				int y1 = _xy[1] + _collision_damage[1];
				int l1 = _collision_damage[2];
				int w1 = _collision_damage[3];

				int x2 = skill_position[0] + skill_hitbox[0];
				int y2 = skill_position[1] + skill_hitbox[1];
				int l2 = skill_hitbox[2];
				int w2 = skill_hitbox[3];

				if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2)) //發生碰撞
				{
					_hp -= (*iter)->GetDamage(this);			//扣血 把自己傳進去判斷是否已經受到過此技能的傷害
				}
			}

			//自動尋路
			switch (_state)
			{
			case CHARGING:
				MoveToTarget(cx, cy);
				_target_x = cx;
				_target_y = cy;
				break;
			case RESET:
				MoveToTarget(_ori_x, _ori_y);
				_target_x = _ori_x;
				_target_y = _ori_y;
				break;
			case ATTACKING:
				break;
			default:
				break;
			}
		}
	}

	void Enemy::OnShow()
	{
		_bm_stand.ShowBitmap();
	}

	bool Enemy::IsAttackZone(int cx, int cy)
	{
		return true;
	}

	int Enemy::Collision(int *cxy, const int* collision, int dx, int dy)
	{
		int x1 = cxy[0] + collision[0] + dx;
		int y1 = cxy[1] + collision[1] + dy;
		int x2 = _xy[0] + _collision_move[0];
		int y2 = _xy[1] + _collision_move[1];
		int l1 = collision[2];
		int w1 = collision[3];
		int l2 = _collision_move[2];
		int w2 = _collision_move[3];
		int e_dx = 0, e_dy = 0;

		if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2))	//發生碰撞
		{
			e_dx = (int)(dx / 3);
			e_dy = (int)(dy / 3);

			//home_map當作參數傳入，不同地圖的敵人才不用重寫
			if (home_map[_xy[0] + _collision_move[0] + e_dx][_xy[1] + _collision_move[1] + e_dy] != -1							//左上
				&& home_map[_xy[0] + _collision_move[0] + _collision_move[2] + e_dx][_xy[1] + _collision_move[1] + e_dy] != -1				//右上
				&& home_map[_xy[0] + _collision_move[0] + e_dx][_xy[1] + _collision_move[1] + _collision_move[3] + e_dy] != -1				//左下
				&& home_map[_xy[0] + _collision_move[0] + _collision_move[2] + e_dx][_xy[1] + _collision_move[1] + _collision_move[3] + e_dy] != -1)		//右下
			{
				_xy[0] += e_dx;
				_xy[1] += e_dy;
				return 1;			//被推到撞牆
			}
			return  2;				//被推
		}
		else return 3;				//沒撞到
	}

	bool Enemy::IsMove(int dx, int dy)
	{
		int x1 = _xy[0] + _collision_move[0];
		int y1 = _xy[1] + _collision_move[1];
		int x2 = x1 + _collision_move[2];
		int y2 = y1 + _collision_move[3];
		if ((home_map[x1 + dx][y1 + dy] != -1) &&
			(home_map[x2 + dx][y1 + dy] != -1) &&
			(home_map[x1 + dx][y2 + dy] != -1) &&
			(home_map[x2 + dx][y2 + dy] != -1))
		{
			return true;
		}
		return false;
	}

	bool Enemy::IsLive()
	{
		return _hp > 0;
	}

	void Enemy::NotifyCharge()
	{
		_state = CHARGING;
	}

	int Enemy::Area()
	{
		return _area;
	}

	void Enemy::MoveToTarget(int target_x, int target_y)
	{
		int currentX = _xy[0];
		int currentY = _xy[1];
		int midX = _xy[0] + (_collision_move[0] + _collision_move[2]) / 2;
		int midY = _xy[1] + 3 * (_collision_move[1] + _collision_move[3]) / 4;
		int cMidX = target_x + 35;
		int cMidY = target_y + 35;
		_step = 1;

		if (!_is_detour)
		{
		

			if ((abs(midX - cMidX) > _zone))
			{
				_is_x_arrive = false;
				if (midX > cMidX)
				{
					if (IsMove(-_step, 0))
					{
						_xy[0] -= _step;
					}
					else
					{
						_neighbor[2] = false;
					}
				}
				else if (midX < cMidX)
				{
					if (IsMove(_step, 0))
					{
						_xy[0] += _step;
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
					if (IsMove(0, -_step))
					{
						_xy[1] -= _step;
					}
					else
					{
						_neighbor[0] = false;
					}
				}
				else if (midY < cMidY)
				{
					if (IsMove(0, _step))
					{
						_xy[1] += _step;
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
				
				IsMove(0, -_step) ? _xy[1] -= _step : NULL;
				//_detour_time--;
			}
			else if (_is_down)
			{
				IsMove(0, _step) ? _xy[1] += _step : NULL;
				
				//_xy[1] += _step;
				//_detour_time--;
			}
			else if(_is_left)
			{
				IsMove(-_step, 0) ? _xy[0] -= _step : NULL;
				//_xy[0] -= _step;
				//_detour_time--;
			}
			else if (_is_right)
			{
				IsMove(_step, 0) ? _xy[0] += _step : NULL;
				//_xy[0] += _step;
				//_detour_time--;
			}

			_detour_time--;

			if (_detour_time <= 0)
			{
				_is_detour = false;

				for (int i; i < 4; i++)
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
				for (int i = 0; i < 60; i++)
				{
					//向右檢查
					if (IsMove(_step * (i + 1), 0))
					{
						if (IsMove(_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_right = true;
							break;
						}
					}
					//向左檢查
					if (IsMove(-_step * (i + 1), 0))
					{
						if (IsMove(-_step * (i + 1), -_step))
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
				
				for (int i = 0; i < 60; i++)
				{
					//向右檢查
					if (IsMove(_step * (i + 1), 0))
					{
						if (IsMove(_step * (i + 1), _step))
						{
							_is_right = true;
							_detour_time = i;
							break;
						}
					}
					//向左檢查
					if (IsMove(-_step * (i + 1), 0))
					{
						if (IsMove(-_step * (i + 1), _step))
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
				for (int i = 0; i < 60; i++)
				{
					//向上檢查
					if (IsMove(0 , -_step * (i + 1)))
					{
						if (IsMove(-_step , -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//向下檢查
					if (IsMove(0, _step * (i + 1)))
					{
						if (IsMove(-_step, _step * (i + 1)))
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
				for (int i = 0; i < 60; i++)
				{
					//向上檢查
					if (IsMove(0, -_step * (i + 1)))
					{
						if (IsMove(_step, -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//向下檢查
					if (IsMove(0, _step * (i + 1)))
					{
						if (IsMove(_step, _step * (i + 1)))
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