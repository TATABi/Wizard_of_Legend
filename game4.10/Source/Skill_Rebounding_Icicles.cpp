#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Rebounding_Icicles.h"
#include "CharacterData.h"
#include "GameData.h"

namespace game_framework
{
	Skill_Rebounding_Icicles::Skill_Rebounding_Icicles(int mousreX, int mouseY, float *cxy) 		//���ߩ��ƹ���m���V�q
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();
	}

	void Skill_Rebounding_Icicles::Initialize(int mouseX, int mouseY, float* cxy)
	{
		_damage = REBOUNDING_ICICKES_DAMAGE;
		_hitbox[0] = REBOUNDING_ICICKES_HITBOX[0];
		_hitbox[1] = REBOUNDING_ICICKES_HITBOX[1];
		_hitbox[2] = REBOUNDING_ICICKES_HITBOX[2];
		_hitbox[3] = REBOUNDING_ICICKES_HITBOX[3];
		_lifeTime = REBOUNDING_ICICKES_LIFETIME;
		_map_collision[0] = REBOUNDING_ICICKES_MAP_HITBOX[0];
		_map_collision[1] = REBOUNDING_ICICKES_MAP_HITBOX[1];
		_map_collision[2] = REBOUNDING_ICICKES_MAP_HITBOX[2];
		_map_collision[3] = REBOUNDING_ICICKES_MAP_HITBOX[3];
		_speed = REBOUNDING_ICICKES_SPEED;
		_cast_distance = REBOUNDING_ICICKES_CAST_DISTANCE;
		_isDelete = false;
		_isStock = false;
		_isInit[0] = _isInit[1] = _isInit[2] = _isInit[3] = true;

		//�ù����ߨ�ƹ��V�q
		int tempX = mouseX - CHARACTER_SCREEN_CENTER_X;					
		int tempY = mouseY - CHARACTER_SCREEN_CENTER_Y;
		float unitVec = (float)(sqrt(pow(tempX, 2) + pow(tempY, 2)));

		//�]�w���ʦV�q
		_dx = (mouseX - CHARACTER_SCREEN_CENTER_X) * _speed / unitVec;
		_dy = (mouseY - CHARACTER_SCREEN_CENTER_Y) * _speed / unitVec;
		_xy[0] = cxy[0] + (mouseX - CHARACTER_SCREEN_CENTER_X) * _cast_distance / unitVec;
		_xy[1] = cxy[1] + (mouseY - CHARACTER_SCREEN_CENTER_Y) * _cast_distance / unitVec;
		_rx = cxy[0] + (mouseX - CHARACTER_SCREEN_CENTER_X) * _cast_distance / unitVec;
		_ry = cxy[1] + (mouseY - CHARACTER_SCREEN_CENTER_Y) * _cast_distance / unitVec;

		_ani_skill[0].SetDelayCount(1);
		_ani_skill[1].SetDelayCount(1);
		_ani_skill[2].SetDelayCount(1);
		_ani_skill[3].SetDelayCount(1);
	}

	void Skill_Rebounding_Icicles::LoadBitmap()
	{
		int ani[10] = { SKILL_REBOUNDING_ICICLES_01,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_03,
					   SKILL_REBOUNDING_ICICLES_03,SKILL_REBOUNDING_ICICLES_03,SKILL_REBOUNDING_ICICLES_04, SKILL_REBOUNDING_ICICLES_04, SKILL_REBOUNDING_ICICLES_04 };
		
		for (int i = 0; i < 10; i++)
			_ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));
	
		for (int i = 0; i < 10; i++)
			_ani_skill[1].AddBitmap(ani[i], RGB(50, 255, 0));

		for (int i = 0; i < 10; i++)
			_ani_skill[2].AddBitmap(ani[i], RGB(50, 255, 0));

		for (int i = 0; i < 10; i++)
			_ani_skill[3].AddBitmap(ani[i], RGB(50, 255, 0));
	}

	int Skill_Rebounding_Icicles::GetDamage(Enemy *enemy)
	{
		int *enemy_hitbox = enemy->GetHitbox();
		float *enemy_position = enemy->GetPosition();
		float x1 = _xy[0] + _hitbox[0];
		float y1 = _xy[1] + _hitbox[1];
		float l1 = _hitbox[2];
		float w1 = _hitbox[3];
		float x2 = enemy_position[0] + enemy_hitbox[0];
		float y2 = enemy_position[1] + enemy_hitbox[1];
		float l2 = enemy_hitbox[2];
		float w2 = enemy_hitbox[3];

		//�����PEnemy�I��
		if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2)) 
		{
			if (AttackedThisEnemy(enemy))
			{
				CharacterData* data = CharacterData::Instance();
				int damage = _damage * data->ATTACK_COEFFICIENT();	
				data->AddMP((int)(damage * data->MP_CHARGE_COEFFICIENT()));
				return damage;
			}
		}
		return 0;
	}

	void Skill_Rebounding_Icicles::OnMove(int *cxy, GameMap *map)
	{
		//�����P�a�ϸI��
		if (map->GetMapStatus(_xy[0] + _map_collision[0], _xy[1] + _map_collision[1]) == -1 ||
			map->GetMapStatus(_xy[0] + _map_collision[0] + _map_collision[2], _xy[1] + _map_collision[1]) == -1 ||
			map->GetMapStatus(_xy[0] + _map_collision[0], _xy[1] + _map_collision[1] + _map_collision[3]) == -1 ||
			map->GetMapStatus(_xy[0] + _map_collision[0] + _map_collision[2], _xy[1] + _map_collision[1] + _map_collision[3]) == -1 )
		{
			_isStock = true;
		}

		//�ޯ��m�]�w
		if (_lifeTime == 0 )		//�ɶ��� or �I����
			_isDelete = true;
		else
		{
			_lifeTime--;

			if (_ani_skill[3].GetCurrentBitmapNumber() < 2 && !_isStock)
			{
				_rx += _dx;
				_ry += _dy;
				_xy[0] = (int)_rx;
				_xy[1] = (int)_ry;
			}

			//  1 Icicles
			if (_isInit[0])
			{
				_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[0].Width() / 2 + _xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[0].Height() / 2 + _xy[1] - cxy[1]);
				_isInit[0] = false;
				_ani_1[0] = _xy[0];
				_ani_1[1] = _xy[1];
			}
			else if (_isInit[0] == false && !_ani_skill[0].IsFinalBitmap())
			{
				_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[0].Width() / 2 + _ani_1[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[0].Height() / 2 + _ani_1[1] - cxy[1]);
				_ani_skill[0].OnMove();
			}

			//  2 Icicles
			if (_ani_skill[0].GetCurrentBitmapNumber() == 4)
			{
				_ani_skill[1].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[1].Width() / 2 + _xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[1].Height() / 2 + _xy[1] - cxy[1]);
				_isInit[1] = false;
				_ani_2[0] = _xy[0];
				_ani_2[1] = _xy[1];
			}
			else if (_isInit[1] == false && !_ani_skill[1].IsFinalBitmap())
			{
				_ani_skill[1].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[1].Width() / 2 + _ani_2[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[1].Height() / 2 + _ani_2[1] - cxy[1]);
				_ani_skill[1].OnMove();
			}
			
			//  3 Icicles
			if (_ani_skill[1].GetCurrentBitmapNumber() == 4)
			{
				_ani_skill[2].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[2].Width() / 2 + _xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[2].Height() / 2 + _xy[1] - cxy[1]);
				_isInit[2] = false;
				_ani_3[0] = _xy[0];
				_ani_3[1] = _xy[1];
			}
			else if (_isInit[2] == false && !_ani_skill[2].IsFinalBitmap())
			{
				_ani_skill[2].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[2].Width() / 2 + _ani_3[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[2].Height() / 2 + _ani_3[1] - cxy[1]);
				_ani_skill[2].OnMove();
			}

			//  4 Icicles
			if (_ani_skill[2].GetCurrentBitmapNumber() == 4)
			{
				_ani_skill[3].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[3].Width() / 2 + _xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[3].Height() / 2 + _xy[1] - cxy[1]);
				_isInit[3] = false;
				_ani_4[0] = _xy[0];
				_ani_4[1] = _xy[1];
			}
			else if (_isInit[3] == false && !_ani_skill[3].IsFinalBitmap())
			{
				_ani_skill[3].SetTopLeft(CHARACTER_SCREEN_CENTER_X - _ani_skill[3].Width() / 2 + _ani_4[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - _ani_skill[3].Height() / 2 + _ani_4[1] - cxy[1]);
				_ani_skill[3].OnMove();
			}
		}
	}

	void Skill_Rebounding_Icicles::OnShow()
	{
		if (!_isDelete)
		{
			if(!_ani_skill[0].IsFinalBitmap())
				_ani_skill[0].OnShow();
			
			if (!_ani_skill[1].IsFinalBitmap() && !_isInit[1])
				_ani_skill[1].OnShow();
			
			if (!_ani_skill[2].IsFinalBitmap() && !_isInit[2])
				_ani_skill[2].OnShow();

			if (!_ani_skill[3].IsFinalBitmap() && !_isInit[3])
				_ani_skill[3].OnShow();
			
			if (_ani_skill[3].IsFinalBitmap())
				_isDelete = true;
		}
	}

}