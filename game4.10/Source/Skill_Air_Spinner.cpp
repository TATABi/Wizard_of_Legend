#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Air_Spinner.h"
#include "CharacterData.h"
#include "GameData.h"

namespace game_framework
{
	Skill_Air_Spinner::Skill_Air_Spinner(int mousreX, int mouseY, float *cxy) 		//中心往滑鼠位置的向量
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();
	}

	void Skill_Air_Spinner::Initialize(int mouseX, int mouseY, float* cxy)
	{
		_damage = AIR_SPINNER_DAMAGE;
		_hitbox[0] = AIR_SPINNER_HITBOX[0];
		_hitbox[1] = AIR_SPINNER_HITBOX[1];
		_hitbox[2] = AIR_SPINNER_HITBOX[2];
		_hitbox[3] = AIR_SPINNER_HITBOX[2];
		_lifeTime = AIR_SPINNER_LIFETIME;
		_map_collision[0] = AIR_SPINNER_MAP_HITBOX[0];
		_map_collision[1] = AIR_SPINNER_MAP_HITBOX[1];
		_map_collision[2] = AIR_SPINNER_MAP_HITBOX[2];
		_map_collision[3] = AIR_SPINNER_MAP_HITBOX[3];
		_speed = AIR_SPINNER_SPEED;
		_cast_distance = AIR_SPINNER_CAST_DISTANCE;
		_isDelete = false;
		_isStock = false;

		//螢幕中心到滑鼠向量
		int tempX = mouseX - CHARACTER_SCREEN_CENTER_X;
		int tempY = mouseY - CHARACTER_SCREEN_CENTER_Y;
		float unitVec = (float)(sqrt(pow(tempX, 2) + pow(tempY, 2)));

		//設定移動向量
		_dx = (mouseX - CHARACTER_SCREEN_CENTER_X) * _speed / unitVec;
		_dy = (mouseY - CHARACTER_SCREEN_CENTER_Y) * _speed / unitVec;
		_xy[0] = cxy[0] + (mouseX - CHARACTER_SCREEN_CENTER_X) * _cast_distance / unitVec;
		_xy[1] = cxy[1] + (mouseY - CHARACTER_SCREEN_CENTER_Y) * _cast_distance / unitVec;

		_ani_skill[0].SetDelayCount(1);
	}

	void Skill_Air_Spinner::LoadBitmap()
	{
		int ani[5] = { SKILL_AIR_SPINNER_01, SKILL_AIR_SPINNER_02, SKILL_AIR_SPINNER_03, SKILL_AIR_SPINNER_04, SKILL_AIR_SPINNER_05 };
		for (int i = 0; i < 5; i++)
			_ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));
	}

	int Skill_Air_Spinner::GetDamage(Enemy *enemy)
	{
		int *enemy_hitbox = enemy->GetHitbox();
		float *enemy_position = enemy->GetPosition();
		float x1 = _xy[0] + _hitbox[0];
		float y1 = _xy[1] + _hitbox[1];
		float r = _hitbox[2];
		float x2 = enemy_position[0] + enemy_hitbox[0];
		float y2 = enemy_position[1] + enemy_hitbox[1];
		float l2 = enemy_hitbox[2];
		float w2 = enemy_hitbox[3];

		//檢查碰撞"外框"是否有接觸
		for (int i = 0; i < l2; i++)
		{
			int step = 0;

			if (i == 0 || i == l2 - 1)
				step = 1;
			else
				step = w2 - 1;

			for (int j = 0; j < w2; j = j + step)
			{
				if (pow(x1 - (x2 + i), 2) + pow(y1 - (y2 + j), 2) <= pow(r, 2))
				{
					if (AttackedThisEnemy(enemy))
					{
						CharacterData* data = &CharacterData::Instance();
						int damage = _damage * data->ATTACK_COEFFICIENT();
						data->AddMP((int)((damage)* data->MP_CHARGE_COEFFICIENT()));
						return damage;
					}
				}
			}
		}
		return 0;
	}

	void Skill_Air_Spinner::OnMove(float *cxy, GameMap *map)
	{
		int x = int(cxy[0]);
		int y = int(cxy[1]);

		//技能位置設定
		if (_lifeTime == 0)		//時間到
			_isDelete = true;
		else
		{
			_lifeTime--;
			_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[0].Width() / 2 + _xy[0] - x, CHARACTER_SCREEN_CENTER_Y - _ani_skill[0].Height() / 2 + _xy[1] - y);

		}
	}

	void Skill_Air_Spinner::OnShow()
	{
		if (!_isDelete)
		{
			_ani_skill[0].OnShow();
			_ani_skill[0].IsFinalBitmap() ? _isDelete = true : _ani_skill[0].OnMove();
		}
	}

}