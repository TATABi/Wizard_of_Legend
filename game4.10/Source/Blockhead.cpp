#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blockhead.h"
#include "time.h"
#include "GameData.h"

namespace game_framework {
	Blockhead::Blockhead(int x, int y, int area, GameMap* map) : Enemy(x, y, area, map)
	{
		Init();
	}

	Blockhead::~Blockhead() {}

	void Blockhead::Init()
	{
		_hitbox[0] = 0;
		_hitbox[1] = 0;
		_hitbox[2] = 34;
		_hitbox[3] = 57;

		_collision_move[0] = 8;
		_collision_move[1] = 41;
		_collision_move[2] = 16;
		_collision_move[3] = 16;
	}

	void Blockhead::Reset()
	{
		_hp = HP;
		_step = STEP;
		_zone = ZONE;
		_damage = DAMAGE;
		_state = NOTHING;

		_xy[0] = _ori_x;
		_xy[1] = _ori_y;

	}

	void Blockhead::LoadBitmap_2()
	{
		_bm_stand.LoadBitmap(ENEMY_BLOCKHEAD, RGB(50, 255, 0));
	}

	void Blockhead::Move(int cx, int cy)
	{
		int x = CHARACTER_SCREEN_X + _xy[0] - cx;
		int y = CHARACTER_SCREEN_Y + _xy[1] - cy;

		switch (_state)
		{
		case ATTACKING:
		case RESET:
		case CHARGING:
		case NOTHING:				//站立
			_bm_stand.SetTopLeft(x, y);
			break;
		case HIT_RECOVER:
			_bm_stand.SetTopLeft(x, y);
			_ani_hurt.SetTopLeft(x + (_bm_stand.Width() - _ani_hurt.Width()) / 2, y + (_bm_stand.Height() - _ani_hurt.Height()) / 2);
			break;
		}
	}

	void Blockhead::OnShow()
	{
		switch (_state)
		{
		case ATTACKING:
		case RESET:
		case CHARGING:
		case NOTHING:				//站立
			_bm_stand.ShowBitmap();
			break;
		case HIT_RECOVER:
			_bm_stand.ShowBitmap();
			if (!_ani_hurt.IsFinalBitmap() && _hit_recover_flag == false)
			{
				_ani_hurt.OnMove();
				_ani_hurt.OnShow();
			}
			else
			{
				_ani_hurt.Reset();
				_hit_recover_flag = true;
			}
			break;
		}
	}

	/*
	int Blockhead::Attack(int x, int y)
	{
		return 0;
	}
	*/
}