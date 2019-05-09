#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Black_man.h"
#include "time.h"

namespace game_framework {
	Black_Man::Black_Man(int x, int y, int area, int zone) : Enemy(x, y, area, zone)
	{
		Init();
	}

	Black_Man::~Black_Man() {}

	void Black_Man::Init()
	{
		_hitbox[0] = 22;
		_hitbox[1] = 15;
		_hitbox[2] = 24;
		_hitbox[3] = 44;

		_collision_move[0] = 29;
		_collision_move[1] = 47;
		_collision_move[2] = 17;
		_collision_move[3] = 12;	
	}

	void Black_Man::Reset()
	{
		srand(time(NULL));
		rand() % 2 ? _direction = LEFT : _direction = RIGHT;
		
		_hp = HP;
		_step = STEP;
		_zone = ZONE;
		_damage = DAMAGE;
		_state = NOTHING;

		_xy[0] = _ori_x;
		_xy[1] = _ori_y; 
		
	}

	void Black_Man::LoadBitmap_2()
	{
		
		_bm_stand_left.LoadBitmap(ENEMY_BLACK_MAN_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(ENEMY_BLACK_MAN_STAND_RIGHT, RGB(50, 255, 0));

		int ani_1[4] = { ENEMY_BLACK_MAN_MOVE_LEFT_01, ENEMY_BLACK_MAN_MOVE_LEFT_02, ENEMY_BLACK_MAN_MOVE_LEFT_03, ENEMY_BLACK_MAN_MOVE_LEFT_04 };
		for (int i = 0; i < 4; i++)
			_ani_left.AddBitmap(ani_1[i], RGB(50, 255, 0));

		int ani_2[4] = { ENEMY_BLACK_MAN_MOVE_RIGHT_01, ENEMY_BLACK_MAN_MOVE_RIGHT_02, ENEMY_BLACK_MAN_MOVE_RIGHT_03, ENEMY_BLACK_MAN_MOVE_RIGHT_04 };
		for (int i = 0; i < 4; i++)
			_ani_right.AddBitmap(ani_2[i], RGB(50, 255, 0));

		int ani_3[5] = { ENEMY_BLACK_MAN_ATTACK_RIGHT_01, ENEMY_BLACK_MAN_ATTACK_RIGHT_02, ENEMY_BLACK_MAN_ATTACK_RIGHT_03, ENEMY_BLACK_MAN_ATTACK_RIGHT_04, ENEMY_BLACK_MAN_ATTACK_RIGHT_05 };
		for (int i = 0; i < 5; i++)
			_ani_attack_right.AddBitmap(ani_3[i], RGB(50, 255, 0));

		int ani_4[5] = { ENEMY_BLACK_MAN_ATTACK_LEFT_01, ENEMY_BLACK_MAN_ATTACK_LEFT_02, ENEMY_BLACK_MAN_ATTACK_LEFT_03, ENEMY_BLACK_MAN_ATTACK_LEFT_04, ENEMY_BLACK_MAN_ATTACK_LEFT_05 };
		for (int i = 0; i < 5; i++)
			_ani_attack_left.AddBitmap(ani_4[i], RGB(50, 255, 0));

		_ani_left.SetDelayCount(2);
		_ani_right.SetDelayCount(2);
		_ani_attack_right.SetDelayCount(2);
		_ani_attack_left.SetDelayCount(2);
	}

	void Black_Man::Move(int x, int y)
	{
		
		switch (_state)
		{
		case NOTHING:				//站立
			_bm_stand_left.SetTopLeft(x, y);
			_bm_stand_right.SetTopLeft(x, y);
			break;
		case ATTACKING:				//攻擊
			_ani_attack_right.SetTopLeft(x, y);
			_ani_attack_left.SetTopLeft(x, y);
			if (_direction == LEFT)
				_ani_attack_left.OnMove();
			else if (_direction == RIGHT)
				_ani_attack_right.OnMove();
			break;
		case CHARGING:				//移動
		case RESET:
			_ani_left.SetTopLeft(x, y);
			_ani_right.SetTopLeft(x, y);
			if (_direction == LEFT)
				_ani_left.OnMove();
			else if (_direction == RIGHT)
				_ani_right.OnMove();
			break;

		case HIT_RECOVER:
			_ani_hurt.SetTopLeft(x + (_bm_stand_left.Width() - _ani_hurt.Width()) / 2, y + (_bm_stand_left.Height() - _ani_hurt.Height()) / 2);
			_bm_stand_left.SetTopLeft(x, y);
			_bm_stand_right.SetTopLeft(x, y);
			break;
		}
	}

	void Black_Man::OnShow()
	{
		
		switch (_state)
		{
		case NOTHING:				//站立
			if(_direction == LEFT)
				_bm_stand_left.ShowBitmap();
			else
				_bm_stand_right.ShowBitmap();
			break;

		case ATTACKING:				//攻擊
			if (_direction == LEFT)
			{
				_ani_attack_left.OnShow();
				if (_ani_attack_right.IsFinalBitmap())
				{
					_attack_counter = 60;
					_ani_attack_right.Reset();
					_state = CHARGING;
				}
			}
			else
			{
				_ani_attack_right.OnShow();	//暫時使用
				if (_ani_attack_left.IsFinalBitmap())
				{
					_attack_counter = 60;
					_ani_attack_left.Reset();
					_state = CHARGING;
				}
			}
				
			break;

		case CHARGING:				//移動
		case RESET:
			if (_direction == LEFT)
				_ani_left.OnShow();
			else if (_direction == RIGHT)
				_ani_right.OnShow();
			break;
			/////////////////////////////
		case HIT_RECOVER:
			if (_direction == LEFT)
				_bm_stand_left.ShowBitmap();
			else
				_bm_stand_right.ShowBitmap();

			_ani_hurt.OnMove();
			_ani_hurt.OnShow();
			if (_ani_hurt.IsFinalBitmap())
			{
				_ani_hurt.Reset();
				_state = CHARGING;
			}
			break;
			////////////////////////////

		}

		/*
		if (_get_hurt == true)
		{
			_ani_hurt.OnShow();
			if (_ani_hurt.IsFinalBitmap())
			{
				_ani_hurt.Reset();
				_get_hurt = false;
			}
			else
				_ani_hurt.OnMove();
		}
		*/
		
	}

}