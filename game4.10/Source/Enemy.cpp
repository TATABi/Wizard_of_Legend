#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include <cmath>
#include "Map_Home_Logic.h"
namespace game_framework {

	Enemy::Enemy(int x, int y)
	{
		Initialize(x, y);
	}

	void Enemy::Initialize(int x, int y)
	{
		xy[0] = x;
		xy[1] = y;
		hp = 1;
	}

	void Enemy::LoadBitmap()
	{
		bm_stand.LoadBitmap(ENEMY_BLOCKHEAD, RGB(50, 255, 0));
	}
	
	void Enemy::OnMove(int cx, int cy, vector<Skill*> skills)
	{
		bm_stand.SetTopLeft(CHARACTER_SCREEN_X + xy[0] - cx, CHARACTER_SCREEN_Y + xy[1] - cy);

		std:: vector<Skill*>::iterator iter;
		for (iter = skills.begin(); iter != skills.end(); iter++)
		{
			int *skill_hitbox = (*iter)->GetHitbox();
			int *skill_position = (*iter)->GetPosition();

			int x1 = xy[0] + collision_damage[0];
			int y1 = xy[1] + collision_damage[1];
			int l1 = collision_damage[2];
			int w1 = collision_damage[3];

			int x2 = skill_position[0] + skill_hitbox[0];
			int y2 = skill_position[1] + skill_hitbox[1];
			int l2 = skill_hitbox[2];
			int w2 = skill_hitbox[3];

			if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2)) //發生碰撞
			{
				hp -= (*iter)->GetDamage();
			}
		}			
			
	}

	void Enemy::OnShow()
	{
		bm_stand.ShowBitmap();
	}
	
	int Enemy::Collision(int *cxy, const int* collision, int dx, int dy)
	{
		int x1 = cxy[0] + collision[0] + dx;
		int y1 = cxy[1] + collision[1] + dy;
		int x2 = xy[0] + collision_move[0];
		int y2 = xy[1] + collision_move[1];
		int l1 = collision[2];
		int w1 = collision[3];
		int l2 = collision_move[2];
		int w2 = collision_move[3];
		int e_dx = 0, e_dy = 0;

		if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2))	//發生碰撞
		{
			e_dx = (int)(dx / 3);
			e_dy = (int)(dy / 3);

			if (home_map[xy[0] + collision_move[0] + e_dx][xy[1] + collision_move[1] + e_dy] != -1							//左上
				&& home_map[xy[0] + collision_move[0] + collision_move[2] + e_dx][xy[1] + collision_move[1] + e_dy] != -1				//右上
				&& home_map[xy[0] + collision_move[0] + e_dx][xy[1] + collision_move[1] + collision_move[3] + e_dy] != -1				//左下
				&& home_map[xy[0] + collision_move[0] + collision_move[2] + e_dx][xy[1] + collision_move[1] + collision_move[3] + e_dy] != -1)		//右下
			{
				xy[0] += e_dx;
				xy[1] += e_dy;
				return 1;			//被推到撞牆
			}
			
			return  2;				//被推
		}
		else return 3;				//沒撞到
	}


	bool Enemy::IsLive()
	{
		return hp > 0;
	}
}