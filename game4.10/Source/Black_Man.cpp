#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Black_man.h"
#include "time.h"
#include "CharacterData.h"

namespace game_framework {
	Black_Man::Black_Man(int x, int y, int area) : Enemy(x, y, area)
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

		isAttack = false;
		
	}

	void Black_Man::LoadBitmap_2()
	{
		
		_bm_stand_left.LoadBitmap(ENEMY_BLACK_MAN_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(ENEMY_BLACK_MAN_STAND_RIGHT, RGB(50, 255, 0));
		_bm_hurt_left.LoadBitmap(ENEMY_BLACK_MAN_HURT_LEFT, RGB(50, 255, 0));
		_bm_hurt_right.LoadBitmap(ENEMY_BLACK_MAN_HURT_RIGHT, RGB(50, 255, 0));

		int ani_1[4] = { ENEMY_BLACK_MAN_MOVE_LEFT_01, ENEMY_BLACK_MAN_MOVE_LEFT_02, ENEMY_BLACK_MAN_MOVE_LEFT_03, ENEMY_BLACK_MAN_MOVE_LEFT_04 };
		for (int i = 0; i < 4; i++)
			_ani_left.AddBitmap(ani_1[i], RGB(50, 255, 0));

		int ani_2[4] = { ENEMY_BLACK_MAN_MOVE_RIGHT_01, ENEMY_BLACK_MAN_MOVE_RIGHT_02, ENEMY_BLACK_MAN_MOVE_RIGHT_03, ENEMY_BLACK_MAN_MOVE_RIGHT_04 };
		for (int i = 0; i < 4; i++)
			_ani_right.AddBitmap(ani_2[i], RGB(50, 255, 0));

		int ani_3[18] = { ENEMY_BLACK_MAN_ATTACK_RIGHT_01, ENEMY_BLACK_MAN_ATTACK_RIGHT_02, ENEMY_BLACK_MAN_ATTACK_RIGHT_03, ENEMY_BLACK_MAN_ATTACK_RIGHT_04, ENEMY_BLACK_MAN_ATTACK_RIGHT_05,
			ENEMY_BLACK_MAN_ATTACK_RIGHT_06, ENEMY_BLACK_MAN_ATTACK_RIGHT_07, ENEMY_BLACK_MAN_ATTACK_RIGHT_08, ENEMY_BLACK_MAN_ATTACK_RIGHT_09, ENEMY_BLACK_MAN_ATTACK_RIGHT_10,
			ENEMY_BLACK_MAN_ATTACK_RIGHT_11, ENEMY_BLACK_MAN_ATTACK_RIGHT_12, ENEMY_BLACK_MAN_ATTACK_RIGHT_13, ENEMY_BLACK_MAN_ATTACK_RIGHT_14, ENEMY_BLACK_MAN_ATTACK_RIGHT_15,
			ENEMY_BLACK_MAN_ATTACK_RIGHT_16, ENEMY_BLACK_MAN_ATTACK_RIGHT_17, ENEMY_BLACK_MAN_ATTACK_RIGHT_18};
		for (int i = 0; i < 13; i++)
			_ani_attack_right.AddBitmap(ani_3[i], RGB(50, 255, 0));

		int ani_4[18] = { ENEMY_BLACK_MAN_ATTACK_LEFT_01, ENEMY_BLACK_MAN_ATTACK_LEFT_02, ENEMY_BLACK_MAN_ATTACK_LEFT_03, ENEMY_BLACK_MAN_ATTACK_LEFT_04, ENEMY_BLACK_MAN_ATTACK_LEFT_05,
			ENEMY_BLACK_MAN_ATTACK_LEFT_06, ENEMY_BLACK_MAN_ATTACK_LEFT_07, ENEMY_BLACK_MAN_ATTACK_LEFT_08, ENEMY_BLACK_MAN_ATTACK_LEFT_09, ENEMY_BLACK_MAN_ATTACK_LEFT_10,
			ENEMY_BLACK_MAN_ATTACK_LEFT_11, ENEMY_BLACK_MAN_ATTACK_LEFT_12, ENEMY_BLACK_MAN_ATTACK_LEFT_13, ENEMY_BLACK_MAN_ATTACK_LEFT_14, ENEMY_BLACK_MAN_ATTACK_LEFT_15,
			ENEMY_BLACK_MAN_ATTACK_LEFT_16, ENEMY_BLACK_MAN_ATTACK_LEFT_17, ENEMY_BLACK_MAN_ATTACK_LEFT_18};
		for (int i = 0; i < 13; i++)
			_ani_attack_left.AddBitmap(ani_4[i], RGB(50, 255, 0));

		_ani_left.SetDelayCount(2);
		_ani_right.SetDelayCount(2);
		_ani_attack_right.SetDelayCount(2);
		_ani_attack_left.SetDelayCount(2);
	}

	void Black_Man::Move(int cx, int cy)
	{
		int x = CHARACTER_SCREEN_X + _xy[0] - cx; 
		int y = CHARACTER_SCREEN_Y + _xy[1] - cy;
		c_x = cx;
		c_y = cy;

		switch (_state)
		{
		case NOTHING:				//站立
			_bm_stand_left.SetTopLeft(x, y);
			_bm_stand_right.SetTopLeft(x, y);
			break;
		case ATTACKING:				//攻擊
			_ani_attack_right.SetTopLeft(x, y);
			_ani_attack_left.SetTopLeft(x, y);
			if (_ani_attack_left.GetCurrentBitmapNumber() == 2 || _ani_attack_right.GetCurrentBitmapNumber() == 2)
				Attack(c_x, c_y);
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
			_bm_hurt_left.SetTopLeft(x, y);
			_bm_hurt_right.SetTopLeft(x, y);
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
				_ani_attack_left.OnMove();
				if (_ani_attack_left.IsFinalBitmap())
				{
					_ani_attack_left.Reset();
					_state = CHARGING;
				}
			}
			else
			{
				_ani_attack_right.OnShow();	//暫時使用
				_ani_attack_right.OnMove();
				if (_ani_attack_right.IsFinalBitmap())
				{
					_ani_attack_right.Reset();
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
		case HIT_RECOVER:
			if (_direction == LEFT)
				_bm_hurt_left.ShowBitmap();
			else
				_bm_hurt_right.ShowBitmap();

			if (!_ani_hurt.IsFinalBitmap() && _hit_recover_flag == false)
			{
				_ani_hurt.OnMove();
				_ani_hurt.OnShow();
			}
			else
			{
				//_ani_hurt.Reset();
				ResetAnimation();
				_hit_recover_flag = true;
			}
			break;

		}
		
	}
	
	void Black_Man::Attack(int cx, int cy)
	{
		int c_hitbox[4] = { 23, 10, 24, 49 };
		int damage_range[4];

		switch (_direction)
		{
		case LEFT:
			damage_range[0] = 6;
			damage_range[1] = 12;
			damage_range[2] = 26;
			damage_range[2] = 51;
			break;
		case RIGHT:
			damage_range[0] = 40;
			damage_range[1] = 12;
			damage_range[2] = 26;
			damage_range[2] = 51;
			break;
		}

		float x1 = _xy[0] + damage_range[0];
		float y1 = _xy[1] + damage_range[1];
		float l1 = damage_range[2];
		float w1 = damage_range[3];

		float x2 = cx + c_hitbox[0];
		float y2 = cy + c_hitbox[1];
		float l2 = c_hitbox[2];
		float w2 = c_hitbox[3];

		//CharacterData::HP -= DAMAGE;
		
		if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2)) //發生碰撞
		{
			CharacterData::HP -= DAMAGE;
		}
		

	}
	

	void Black_Man::ResetAnimation()
	{
		_ani_hurt.Reset();
		_ani_left.Reset();
		_ani_right.Reset();
		_ani_attack_left.Reset();
		_ani_attack_right.Reset();
	}


}