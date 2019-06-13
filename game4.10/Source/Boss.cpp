#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Boss.h"
#include "time.h"
#include "CharacterData.h"
#include "GameData.h"

namespace game_framework {

	Boss::Boss(int x, int y, int area, GameMap* map) : Enemy(x, y, area, map)
	{
		Init();
	}

	void Boss::Init()
	{
		_hitbox[0] = BOSS_HITBOX[0];
		_hitbox[1] = BOSS_HITBOX[1];
		_hitbox[2] = BOSS_HITBOX[2];
		_hitbox[3] = BOSS_HITBOX[3];
		_move_hitbox[0] = BOSS_MOVE_HITBOX[0];
		_move_hitbox[1] = BOSS_MOVE_HITBOX[1];
		_move_hitbox[2] = BOSS_MOVE_HITBOX[2];
		_move_hitbox[3] = BOSS_MOVE_HITBOX[3];
		_ani_left.SetDelayCount(3);
		_ani_right.SetDelayCount(3);
		_ani_attack_right.SetDelayCount(2);
		_ani_attack_left.SetDelayCount(2);
		_ani_skill.SetDelayCount(3);
		srand(time(NULL));
		rand() % 2 ? _direction = LEFT : _direction = RIGHT;
		_hp = BOSS_HP;
		_step = BOSS_STEP;
		_zone = BOSS_ZONE;
		_damage = BOSS_DAMAGE;
		_attack_delay_counter = BOSS_ATTACK_DELAY_TIME;
		_charge_zone = BOSS_CHARGE_ZONE;
		_state = NOTHING;
		_skill_counter = 100;
		_isInvisible = false;
		_xy[0] = _ori_x;
		_xy[1] = _ori_y;
		//出場笑聲
		CAudio::Instance()->Play(AUDIO_BOSS_LAUGH);
	}

	void Boss::LoadEnemyBitmap()
	{
		_bm_hp_bar.LoadBitmap(ENEMY_HP_BAR_M);
		_bm_stand_left.LoadBitmap(ENEMY_BOSS_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(ENEMY_BOSS_STAND_RIGHT, RGB(50, 255, 0));
		_bm_hurt_left.LoadBitmap(ENEMY_BOSS_HURT_LEFT, RGB(50, 255, 0));
		_bm_hurt_right.LoadBitmap(ENEMY_BOSS_HURT_RIGHT, RGB(50, 255, 0));
		_bm_shadow.LoadBitmap(ENEMY_BOSS_SHADOW, RGB(50, 255, 0));

		int source1[5] = { ENEMY_BOSS_MOVE_LEFT_01, ENEMY_BOSS_MOVE_LEFT_02, ENEMY_BOSS_MOVE_LEFT_03, ENEMY_BOSS_MOVE_LEFT_04, ENEMY_BOSS_MOVE_LEFT_05 };
		for (int i = 0; i < 5; i++)
			_ani_left.AddBitmap(source1[i], RGB(50, 255, 0));

		int source2[5] = { ENEMY_BOSS_MOVE_RIGHT_01, ENEMY_BOSS_MOVE_RIGHT_02, ENEMY_BOSS_MOVE_RIGHT_03, ENEMY_BOSS_MOVE_RIGHT_04, ENEMY_BOSS_MOVE_RIGHT_05 };
		for (int i = 0; i < 5; i++)
			_ani_right.AddBitmap(source2[i], RGB(50, 255, 0));

		int source3[6] = { ENEMY_BOSS_ATTACK_RIGHT_01, ENEMY_BOSS_ATTACK_RIGHT_02, ENEMY_BOSS_ATTACK_RIGHT_03, ENEMY_BOSS_ATTACK_RIGHT_04, ENEMY_BOSS_ATTACK_RIGHT_05,
			ENEMY_BOSS_ATTACK_RIGHT_06 };
		for (int i = 0; i < 6; i++)
			_ani_attack_right.AddBitmap(source3[i], RGB(50, 255, 0));

		int source4[6] = { ENEMY_BOSS_ATTACK_LEFT_01, ENEMY_BOSS_ATTACK_LEFT_02, ENEMY_BOSS_ATTACK_LEFT_03, ENEMY_BOSS_ATTACK_LEFT_04, ENEMY_BOSS_ATTACK_LEFT_01,
			ENEMY_BOSS_ATTACK_LEFT_06 };
		for (int i = 0; i < 6; i++)
			_ani_attack_left.AddBitmap(source4[i], RGB(50, 255, 0));

		int source5[4] = { ENEMY_BOSS_SKILL_LEFT_01, ENEMY_BOSS_SKILL_LEFT_02, ENEMY_BOSS_SKILL_LEFT_03, ENEMY_BOSS_SKILL_LEFT_04 };
		for (int i = 0; i < 4; i++)
			_ani_skill.AddBitmap(source5[i], RGB(50, 255, 0));
	}

	void Boss::Move(int cx, int cy)
	{
		_sx = CHARACTER_SCREEN_X + _xy[0] - cx;
		_sy = CHARACTER_SCREEN_Y + _xy[1] - cy;

		_bm_shadow.SetTopLeft(_sx, _sy);
		!_hit_recover_flag ? _isInvisible = false, _skill_counter = 100 : NULL;

		if (_skill_counter > 0)
			_skill_counter--;
		else
		{
			if (!_isInvisible)
			{
				_state = SKILL;
				CAudio::Instance()->Play(AUDIO_BOSS_INVISIBLE);
				_invincible_counter = 150;
			}
		}

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
		case HIT_RECOVER:			//硬直
			_ani_hurt.SetTopLeft(_sx + (_bm_stand_left.Width() - _ani_hurt.Width()) / 2, _sy + (_bm_stand_left.Height() - _ani_hurt.Height()) / 2);
			_bm_hurt_left.SetTopLeft(_sx, _sy);
			_bm_hurt_right.SetTopLeft(_sx, _sy);
			break;
		case SKILL:					//使用技能(隱身)
			_ani_skill.SetTopLeft(_sx, _sy);
			break;
		}
	}

	void Boss::OnShow()
	{
		if (IsLive())
		{
			switch (_state)
			{
			case NOTHING:				//站立
				if (_isInvisible)
					_bm_shadow.ShowBitmap();
				else if (_direction == LEFT)
					_bm_stand_left.ShowBitmap();
				else
					_bm_stand_right.ShowBitmap();
				break;
			case ATTACKING:				//攻擊
				if (_direction == LEFT)
				{
					_isInvisible ? _bm_shadow.ShowBitmap() : _ani_attack_left.OnShow();

					_attack_delay_counter == 0 ? _ani_attack_left.OnMove() : NULL;

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
					_isInvisible ? _bm_shadow.ShowBitmap() : _ani_attack_right.OnShow();
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
				if (_isInvisible)
					_bm_shadow.ShowBitmap();
				else if (_direction == LEFT)
					_ani_left.OnShow();
				else if (_direction == RIGHT)
					_ani_right.OnShow();
				break;
			case HIT_RECOVER:			//硬直
				if (_isInvisible)
					_bm_shadow.ShowBitmap();
				else if (_direction == LEFT)
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
					_invincible_counter = 90;
				}
				break;

			case SKILL:					//隱身
				if (!_ani_skill.IsFinalBitmap())
				{
					_ani_skill.OnShow();
					_ani_skill.OnMove();
				}
				else
				{
					_isInvisible = true;
					_ani_skill.Reset();
					_state = CHARGING;
				}
				break;
			}
			//顯示&計算HP
			CalculateHP();
		}
	}

	void Boss::Attack(float cx, float cy)
	{
		float x1 = _xy[0] + 65;
		float y1 = _xy[1] + 65;
		float r = 65;
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
					{
						if (pow(x1 - (x2 + i), 2) + pow(y1 - (y2 + j), 2) <= pow(r, 2))
						{
							if (CharacterData::Instance().ISVINCIBLE()) //如果Character在Dash狀態，則Enemy打不到
							{
								CharacterData::Instance().AddHP(-BOSS_DAMAGE);
								CAudio::Instance()->Play(AUDIO_BOSS_ATTACK);
							}
							_isAttack = true;
							break;
						}
					}
				}

				if (_isAttack)
					break;
			}
		}
	}

	void Boss::CalculateHP()
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
		temp_hp = (float)(BOSS_HP - _hp) / BOSS_HP;			//計算HP差值
		X1 = (int)(temp_hp * 52);
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// 畫灰色 (扣MP)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(Max_HP_X2 - X1, MAX_HP_Y1, Max_HP_X2, MAX_HP_Y2);
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	void Boss::PlayDeadAudio()
	{
		CAudio::Instance()->Play(AUDIO_BOSS_DEAD, false);
	}
}