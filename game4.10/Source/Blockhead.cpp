#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blockhead.h"
#include "time.h"
#include "GameData.h"

namespace game_framework 
{
	Blockhead::Blockhead(int x, int y, int area, GameMap* map) : Enemy(x, y, area, map)
	{
		Init();
		Reset();
	}

	void Blockhead::Init()
	{
		_hitbox[0] = BLOCKHEAD_HITBOX[0];
		_hitbox[1] = BLOCKHEAD_HITBOX[1];
		_hitbox[2] = BLOCKHEAD_HITBOX[2];
		_hitbox[3] = BLOCKHEAD_HITBOX[3];
		_move_hitbox[0] = BLOCKHEAD_MOVE_HITBOX[0];
		_move_hitbox[1] = BLOCKHEAD_MOVE_HITBOX[1];
		_move_hitbox[2] = BLOCKHEAD_MOVE_HITBOX[2];
		_move_hitbox[3] = BLOCKHEAD_MOVE_HITBOX[3];
	}

	void Blockhead::Reset()
	{
		_hp = BLOCKHEAD_HP;
		_step = BLOCKHEAD_STEP;
		_zone = BLOCKHEAD_ZONE;
		_damage = BLOCKHEAD_DAMAGE;
		_charge_zone = BLOCKHEAD_CHARGING_ZONE;
		_state = NOTHING;
		_xy[0] = _ori_x;
		_xy[1] = _ori_y;
	}

	void Blockhead::LoadEnemyBitmap()
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
		case NOTHING:
			_bm_stand.SetTopLeft(x, y);
			break;
		case HIT_RECOVER:
			_bm_stand.SetTopLeft(x, y);
			_ani_hurt.SetTopLeft(x + (_bm_stand.Width() - _ani_hurt.Width()) / 2, y + (_bm_stand.Height() - _ani_hurt.Height()) / 2);
			break;
		}

		//不死
		_hp <= 0 ? _hp = BLOCKHEAD_HP : NULL;
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
}