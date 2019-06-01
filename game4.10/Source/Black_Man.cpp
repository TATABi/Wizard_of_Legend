#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Black_man.h"
#include "time.h"
#include "CharacterData.h"
#include "GameData.h"

namespace game_framework {
	Black_Man::Black_Man(int x, int y, int area, GameMap* map) : Enemy(x, y, area, map)
	{
		Init();
		Reset();
	}

	void Black_Man::Init()
	{
		_hitbox[0] = BLACKMAN_HITBOX[0];
		_hitbox[1] = BLACKMAN_HITBOX[1];
		_hitbox[2] = BLACKMAN_HITBOX[2];
		_hitbox[3] = BLACKMAN_HITBOX[3];
		_move_hitbox[0] = BLACKMAN_MOVE_HITBOX[0];
		_move_hitbox[1] = BLACKMAN_MOVE_HITBOX[1];
		_move_hitbox[2] = BLACKMAN_MOVE_HITBOX[2];
		_move_hitbox[3] = BLACKMAN_MOVE_HITBOX[3];
	}

	void Black_Man::Reset()
	{
		srand(time(NULL));
		rand() % 2 ? _direction = LEFT : _direction = RIGHT;
		_hp = BLACKMAN_HP;
		_step = BLACKMAN_STEP;
		_zone = BLACKMAN_ZONE;
		_damage = BLACKMAN_DAMAGE;
		_charge_zone = BLACKMAN_CHARGING_ZONE;
		_state = NOTHING;
		_attack_delay_counter = BLACKMAN_ATTACK_DELAY_TIME;
		_xy[0] = _ori_x;
		_xy[1] = _ori_y;
	}

	void Black_Man::LoadBitmap_2()
	{
		_bm_hp_bar.LoadBitmap(ENEMY_HP_BAR_M);

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
			ENEMY_BLACK_MAN_ATTACK_RIGHT_16, ENEMY_BLACK_MAN_ATTACK_RIGHT_17, ENEMY_BLACK_MAN_ATTACK_RIGHT_18 };
		for (int i = 0; i < 15; i++)
			_ani_attack_right.AddBitmap(ani_3[i], RGB(50, 255, 0));

		int ani_4[18] = { ENEMY_BLACK_MAN_ATTACK_LEFT_01, ENEMY_BLACK_MAN_ATTACK_LEFT_02, ENEMY_BLACK_MAN_ATTACK_LEFT_03, ENEMY_BLACK_MAN_ATTACK_LEFT_04, ENEMY_BLACK_MAN_ATTACK_LEFT_05,
			ENEMY_BLACK_MAN_ATTACK_LEFT_06, ENEMY_BLACK_MAN_ATTACK_LEFT_07, ENEMY_BLACK_MAN_ATTACK_LEFT_08, ENEMY_BLACK_MAN_ATTACK_LEFT_09, ENEMY_BLACK_MAN_ATTACK_LEFT_10,
			ENEMY_BLACK_MAN_ATTACK_LEFT_11, ENEMY_BLACK_MAN_ATTACK_LEFT_12, ENEMY_BLACK_MAN_ATTACK_LEFT_13, ENEMY_BLACK_MAN_ATTACK_LEFT_14, ENEMY_BLACK_MAN_ATTACK_LEFT_15,
			ENEMY_BLACK_MAN_ATTACK_LEFT_16, ENEMY_BLACK_MAN_ATTACK_LEFT_17, ENEMY_BLACK_MAN_ATTACK_LEFT_18 };
		for (int i = 0; i < 15; i++)
			_ani_attack_left.AddBitmap(ani_4[i], RGB(50, 255, 0));

		_ani_left.SetDelayCount(2);
		_ani_right.SetDelayCount(2);
		_ani_attack_right.SetDelayCount(2);
		_ani_attack_left.SetDelayCount(2);
	}

	void Black_Man::Move(int cx, int cy)
	{
		_sx = CHARACTER_SCREEN_X + _xy[0] - cx;
		_sy = CHARACTER_SCREEN_Y + _xy[1] - cy;

		switch (_state)
		{
		case NOTHING:				//站立
			_bm_stand_left.SetTopLeft(_sx, _sy);
			_bm_stand_right.SetTopLeft(_sx, _sy);
			break;

		case ATTACKING:				//攻擊
			_attack_delay_counter > 0 ? _attack_delay_counter-- : NULL;
			_ani_attack_right.SetTopLeft(_sx, _sy);
			_ani_attack_left.SetTopLeft(_sx, _sy);
			_isAttack ? NULL : Attack(cx, cy);
			break;

		case CHARGING:				//移動
		case RESET:
			_ani_left.SetTopLeft(_sx, _sy);
			_ani_right.SetTopLeft(_sx, _sy);
			if (_direction == LEFT)
				_ani_left.OnMove();
			else if (_direction == RIGHT)
				_ani_right.OnMove();
			break;

		case HIT_RECOVER:
			_ani_hurt.SetTopLeft(_sx + (_bm_stand_left.Width() - _ani_hurt.Width()) / 2, _sy + (_bm_stand_left.Height() - _ani_hurt.Height()) / 2);
			_bm_hurt_left.SetTopLeft(_sx, _sy);
			_bm_hurt_right.SetTopLeft(_sx, _sy);
			break;
		}
	}

	void Black_Man::OnShow()
	{
		switch (_state)
		{
		case NOTHING:				//站立
			if (_direction == LEFT)
				_bm_stand_left.ShowBitmap();
			else
				_bm_stand_right.ShowBitmap();
			break;

		case ATTACKING:				//攻擊

			if (_direction == LEFT)
			{
				_ani_attack_left.OnShow();

				_attack_delay_counter == 0 ?_ani_attack_left.OnMove() : NULL;

				if (_ani_attack_left.IsFinalBitmap())
				{
					_attack_delay_counter = 10;
					_isAttack = false;
					_ani_attack_left.Reset();
					_state = CHARGING;
				}
			}
			else
			{
				_ani_attack_right.OnShow();	//暫時使用

				_attack_delay_counter == 0 ? _ani_attack_right.OnMove() : NULL;

				if (_ani_attack_right.IsFinalBitmap())
				{
					_attack_delay_counter = 10;
					_isAttack = false;
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
				ResetAnimation();
				_hit_recover_flag = true;
			}
			break;
		}
		CalculateHP();
	}

	void Black_Man::Attack(float cx, float cy)
	{
		float x1 = _xy[0] + 35;
		float y1 = _xy[1] + 35;
		float r = 50;
		float x2 = cx + CHARACTER_HITBOX[0];
		float y2 = cy + CHARACTER_HITBOX[1];
		float l2 = CHARACTER_HITBOX[2];
		float w2 = CHARACTER_HITBOX[3];
		
		if (_attack_delay_counter == 0)
		{
			for (int i = 0; i < l2; i++)
			{
				int step = 0;

				if (i == 0 || i == l2 - 1)
					step = 1;
				else
					step = w2 - 1;

				for (int j = 0; j < w2; j = j + step)
				{
					if (!_isAttack)
						if (pow(x1 - (x2 + i), 2) + pow(y1 - (y2 + j), 2) <= pow(r, 2))
						{
							CharacterData::Instance()->ISVINCIBLE() == false ? CharacterData::Instance()->AddHP(-BLACKMAN_DAMAGE) : NULL;
							_isAttack = true;
							break;
						}
				}

				if (_isAttack)
					break;
			}
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

	void Black_Man::CalculateHP()
	{
		int sx = _sx + (_bm_stand_left.Width() - _bm_hp_bar.Width()) / 2;
		int sy = _sy;
		int Max_HP_X2 = sx + 53;
		int MAX_HP_Y1 = sy + 1;
		int MAX_HP_Y2 = sy + 5;
		int X1;
		float temp_hp;
		
		_bm_hp_bar.SetTopLeft(sx, sy);
		_bm_hp_bar.ShowBitmap();
		temp_hp = (float)(BLACKMAN_HP - _hp) / BLACKMAN_HP;			//計算HP差值
		X1 = (int)(temp_hp * 52);
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// 畫灰色 (扣MP)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(Max_HP_X2 - X1, MAX_HP_Y1, Max_HP_X2, MAX_HP_Y2);
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		
	}
}