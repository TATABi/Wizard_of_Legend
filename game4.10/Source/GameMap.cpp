#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <algorithm>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Character.h"
#include "UI.h"
#include "CharacterData.h"
#include "Boss.h"

namespace game_framework {
	
	GameMap::GameMap(int x, int y){}
	
	GameMap::~GameMap() 
	{
		for each (Skill* skill in _skillList)
			delete skill;

		for each (Enemy* enemy in _enemies)
			delete enemy;

		for each (Reward* reward in _rewards)
			delete reward;
	}

	void GameMap::Initialize(int x, int y) 
	{
		_cxy[0] = x;
		_cxy[1] = y;	
		_ani_press_f.SetDelayCount(2);
		_isPressF = false;
		_character_status = 0;
		_isEnd = false;
		Init();
	}

	void GameMap::LoadBitmapPressF()
	{
		int m[6] = { PRESS_F_01, PRESS_F_02, PRESS_F_03 , PRESS_F_04, PRESS_F_05, PRESS_F_06 };
		for (int i = 0; i < 6;i++)
			_ani_press_f.AddBitmap(m[i], RGB(50, 255, 0));
	}
	
	void GameMap::OnMoveBackgroundAndWall()
	{
		_background.SetTopLeft(CHARACTER_SCREEN_X - _cxy[0], CHARACTER_SCREEN_Y - _cxy[1]);
		_wall.SetTopLeft(CHARACTER_SCREEN_X - _cxy[0], CHARACTER_SCREEN_Y - _cxy[1]);
	}
	
	void GameMap::OnShowBackground()
	{
		_background.ShowBitmap();
	}

	void GameMap::OnShowWall()
	{
		_wall.ShowBitmap();
	}

	void GameMap::OnShowPressF()
	{
		if (_isPressF)
			_ani_press_f.OnShow();
	}
	
	int GameMap::GetCharacterStatus() 
	{
		return _character_status;
	}

	float* GameMap::GetCharacterPosition()
	{
		return _cxy;
	}

	void GameMap::CharacterUseSkill(int skillNum, int x, int y)
	{
		if(!Character::Instance().IsUsingSkill() && !Character::Instance().IsHurt() && !Character::Instance().IsSkillCooldown(skillNum))
			_skillList.push_back(Character::Instance().GenerateSkill(skillNum, x, y));
	}
	
	void GameMap::SkillOnMove()
	{
		for each (Skill* skill in _skillList)
			skill->OnMove(GetCharacterPosition(), &(*this));	
	}
	
	void GameMap::EnemyOnMove()
	{
		for each (Enemy* enemy in _enemies)
			enemy->OnMove(_cxy[0], _cxy[1], _skillList);
	}
	
	void GameMap::RewardsOnMove()
	{
		for each (Reward* reward in _rewards)
			reward->OnMove();
	}
	void GameMap::OnShow()
	{
		Show();
		//圖層效果
		vector<Layer*> layer;
		layer.insert(layer.end(), _rewards.begin(), _rewards.end());
		layer.insert(layer.end(), _enemies.begin(), _enemies.end());
		layer.insert(layer.end(), _skillList.begin(), _skillList.end());
		layer.push_back(&Character::Instance());
		sort(layer.begin(), layer.end(), [](Layer* a, Layer* b) {return a->GetY() < b->GetY(); });

		vector<Layer*>::iterator l_it;
		for (l_it = layer.begin(); l_it != layer.end(); l_it++)
			(*l_it)->OnShow();

		CleanMemory();	
	}

	void GameMap::CleanMemory()
	{
		vector<Skill*>::iterator s_it;
		for (s_it = _skillList.begin(); s_it != _skillList.end(); s_it++)
		{
			if ((*s_it)->IsDelete() == true)
			{
				delete *s_it;
				s_it = _skillList.erase(s_it);
			}
			if (s_it == _skillList.end())
				break;
		}

		vector<Enemy*>::iterator e_it;
		for (e_it = _enemies.begin(); e_it != _enemies.end(); e_it++)
		{
			if (!(*e_it)->IsLive())
			{
				//刪除enemy前先產生reward
				if (!(*e_it)->IsReset())
				{
					vector<Reward*> temp = (*e_it)->CreateReward();
					(*e_it)->PlayDeadAudio();
					(*e_it)->Area() == 11 ? (UI::Instance().StageCleared(), _isEnd = true) : NULL;
					_rewards.insert(_rewards.end(), temp.begin(), temp.end());
				}
				delete *e_it;
				e_it = _enemies.erase(e_it);
			}
			if (e_it == _enemies.end())
				break;
		}
		
		vector<Reward*>::iterator r_it;
		for (r_it = _rewards.begin(); r_it != _rewards.end(); r_it++)
		{
			if ((*r_it)->IsDelete() == true)
			{
				delete *r_it;
				r_it = _rewards.erase(r_it);
			}
			if (r_it == _rewards.end())
				break;
		}
	}

	void GameMap::SetCharacterXY(int dx, int dy)
	{
		int slow_x = (int)dx / 3;
		int slow_y = (int)dy / 3;

		////////角色移動與怪物碰撞//////
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
		{
			float *e_xy = (*iter)->GetPosition();
			int *e_collision_move = (*iter)->GetMoveHitbox();

			int x1 = _cxy[0] + CHARACTER_MOVE_HITBOX[0] + dx;
			int y1 = _cxy[1] + CHARACTER_MOVE_HITBOX[1] + dy;
			int x2 = e_xy[0] + e_collision_move[0];
			int y2 = e_xy[1] + e_collision_move[1];
			int l1 = CHARACTER_MOVE_HITBOX[2];
			int w1 = CHARACTER_MOVE_HITBOX[3];
			int l2 = e_collision_move[2];
			int w2 = e_collision_move[3];

			int e_dx = 0, e_dy = 0;

			if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2))	//發生碰撞
			{
				e_dx = (int)(dx / 3);
				e_dy = (int)(dy / 3);

				if (CheckMapStatus(e_xy[0] + e_dx, e_xy[1] + e_dy, e_collision_move, -1, '>'))
				{
					e_xy[0] += e_dx;
					e_xy[1] += e_dy;
					//角色放慢速度	
					dx = slow_x;
					dy = slow_y;
					break;
				}
				//被推
				dx = dy = 0;
			}
			//沒撞到
		}

		//////////角色與地圖碰撞////////////
		int cx = _cxy[0] + CHARACTER_MOVE_HITBOX[0];
		int cy = _cxy[1] + CHARACTER_MOVE_HITBOX[1];
		int l = CHARACTER_MOVE_HITBOX[2];
		int w = CHARACTER_MOVE_HITBOX[3];
		bool canMove = CheckMapStatus(_cxy[0] + dx, _cxy[1] + dy, CHARACTER_MOVE_HITBOX, -1, '!');
		bool nextIsDrop = (GetMapStatus(cx + dx + l / 2, cy + dy + w / 2) == -2);
		bool isDrop = GetMapStatus(cx + l / 2, cy + w / 2) == -2;
		
		//不是-1
		if (canMove)
		{
			//移動處是否為drop
			if (!nextIsDrop)
			{
				//判斷是否是陷阱
				if (GetMapStatus(int(cx + dx + l / 2), int(cy + dy + w / 3)) == -3)
					Character::Instance().SetInTrap(true);
				else
					Character::Instance().SetInTrap(false);

				_cxy[0] += dx;
				_cxy[1] += dy;
			}
			else
			{
				if (Character::Instance().IsDash())
					_cxy[0] += dx, _cxy[1] += dy;
			}		
			if (isDrop && !Character::Instance().IsDash())
				Character::Instance().SetDrop();
		}
	}

	bool GameMap::CheckEnemyPosition(int x, int y, const int* hitbox)
	{
		int ex = x + hitbox[0];
		int ey = y + hitbox[1];
		int l = hitbox[2];
		int w = hitbox[3];

		//////////與地圖碰撞////////////
		return CheckMapStatus(x, y, hitbox) && CheckMapStatus(x, y, hitbox, -2, '!');
	}

	bool GameMap::CheckMapStatus(int px, int py, const int* move_hitbox, int num, char op)
	{
		int x = px + move_hitbox[0];
		int y = py + move_hitbox[1];
		int l = move_hitbox[2];
		int w = move_hitbox[3];

		//判斷碰撞框四角在地圖的Logic值
		switch (op)
		{
		case '!':
			if (GetMapStatus(x, y) != num
				&& GetMapStatus(x + l, y) != num
				&& GetMapStatus(x + l, y + w) != num
				&& GetMapStatus(x, y + w) != num)
			{
				return true;
			}
			return false;
			break;

		case '>':
			if (GetMapStatus(x, y) > num
				&& GetMapStatus(x + l, y) > num
				&& GetMapStatus(x + l, y + w) > num
				&& GetMapStatus(x, y + w) > num)
			{
				return true;
			}
			return false;
			break;
		}
	}

	bool GameMap::IsEnd()
	{
		return _isEnd;
	}

	void GameMap::Show() {}

	void GameMap::Init() {}
}