#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Shock_Nova.h"


namespace game_framework
{
	Skill_Shock_Nova::Skill_Shock_Nova(int mousreX, int mouseY, int *cxy) 		//中心往滑鼠位置的向量
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();	
	}

	Skill_Shock_Nova::~Skill_Shock_Nova()
	{

	}

	void Skill_Shock_Nova::Initialize(int mouseX, int mouseY, int* cxy)
	{
		_damage = 0;
		_backDistance = 10;
		_hitbox[0] = 13;
		_hitbox[1] = 13;
		_hitbox[2] = 187;
		_hitbox[3] = 187;
		_lifeTimer = 300;
		_map_collision[0] = 0;
		_map_collision[1] = 0;
		_map_collision[2] = 0;
		_map_collision[3] = 0;
		_isDelete = false;
		_isStock = false;
		_speed = 20;
		_cast_distance = 30;
		_isInit = true;
		_counter = 5;
		_time = 6;
		_ani_skill[0].SetDelayCount(1);

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
		_counter == 0 ? NULL : _counter--;
		
		_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cxy[0], CHARACTER_SCREEN_X + _xy[1] - cxy[1]);

		if (_counter == 0)
		{
			_damage = 20;

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
				_xy[1] = cxy[1] - (_ani_skill[0].Height() - 70) / 2 - 52;
				_isInit = false;
			}
		}

	}

	void Skill_Shock_Nova::OnShow()
	{
		if (!_isDelete && _counter==0)
		{
			_ani_skill[0].OnShow();
			if (_ani_skill[0].IsFinalBitmap())
			{
				_time == 0 ? _isDelete = true : _ani_skill[0].Reset(), _time--;
			}
		}
		
	}


}