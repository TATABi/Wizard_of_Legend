#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Shock_Nova.h"
#include "CharacterData.h"


namespace game_framework
{
	Skill_Shock_Nova::Skill_Shock_Nova(int mousreX, int mouseY, float *cxy) 		//中心往滑鼠位置的向量
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();	
	}

	Skill_Shock_Nova::~Skill_Shock_Nova()
	{

	}

	void Skill_Shock_Nova::Initialize(int mouseX, int mouseY, float* cxy)
	{
		_damage = 2;
		_backDistance = 10;
		_hitbox[0] = 103;
		_hitbox[1] = 105;
		_hitbox[2] = 95;
		_hitbox[3] = 95;
		_lifeTimer = 300;
		_map_collision[0] = 0;			//圓心
		_map_collision[1] = 0;
		_map_collision[2] = 0;				//半徑
		_map_collision[3] = 0;
		_isDelete = false;
		_isStock = false;
		_speed = 20;
		_cast_distance = 30;
		_isInit = true;
		_delay_counter = 5;
		_time = 6;
		_ani_skill[0].SetDelayCount(1);
		_re_attack_counter = RE;

	}

	void Skill_Shock_Nova::LoadBitmap()
	{
		_bm_skill_icon.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));


		int ani[3] = { SKILL_SHOCK_NOVA_01,SKILL_SHOCK_NOVA_02,SKILL_SHOCK_NOVA_03 };

		for (int i = 0; i < 3; i++)
			_ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));

	}

	void Skill_Shock_Nova::OnMove(int *cxy, GameMap *map)
	{


		_delay_counter > 0 ? _delay_counter-- : NULL;
		_re_attack_counter > 0 ? _re_attack_counter-- : NULL;

		if (_delay_counter == 0)
		{

			if (_lifeTimer == 0) //時間到
			{
				_isDelete = true;
			}

			_lifeTimer--;
			if (!_isInit)
			{
				_ani_skill[0].OnMove();
			}
			else
			{
				_xy[0] = cxy[0] - (_ani_skill[0].Width() - 70) / 2 + 2;
				_xy[1] = cxy[1] - (_ani_skill[0].Height() - 70) / 2 + 25;

				_isInit = false;
			}
		}

		_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cxy[0], CHARACTER_SCREEN_Y + _xy[1] - cxy[1]);

		if (_re_attack_counter == 0)
		{
			RefreshEnemyList();
			_re_attack_counter = RE;
		}


	}

	int Skill_Shock_Nova::GetDamage(Enemy *enemy)
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
						auto* data = CharacterData::Instance();
						
						int damage = _damage * data->ATTACK_COEFFICIENT();

						data->AddMP((int)((damage) * data->MP_CHARGE_COEFFICIENT()));
						
						return damage;
						
						//return 0;
					}
				}
			}
		}
		return 0;
	}

	void Skill_Shock_Nova::OnShow()
	{
		if (!_isDelete && _delay_counter ==0)
		{
			_ani_skill[0].OnShow();
			if (_ani_skill[0].IsFinalBitmap())
			{
				_time == 0 ? _isDelete = true : _ani_skill[0].Reset(), _time--;
			}
		}
	}

	int* Skill_Shock_Nova::GetHitbox()
	{
		return _hitbox;
	}


}