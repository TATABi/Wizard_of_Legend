#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Skill_Air_Spinner.h"
#include "Skill_Rebounding_Icicles.h"
#include "Skill_Shock_Nova.h"
#include "math.h"
#include "GameData.h"

#define M_PI atan(1.0) * 4;
#define SLASH_COEFFICIENT 1 / sqrt(2) 

namespace game_framework {

	Character& Character::Instance()
	{
		static Character instance;
		return instance;
	}

	Character::Character()
	{
		float xy[2] = { 0, 0 };
		Initialize(xy);
	}

	void Character::Initialize(float* xy)
	{
		_xy[0] = xy[0];
		_xy[1] = xy[1];
		_ani_down.SetDelayCount(2);
		_ani_up.SetDelayCount(2);
		_ani_left.SetDelayCount(2);
		_ani_right.SetDelayCount(2);
		_ani_dash_right.SetDelayCount(1);
		_ani_dash_left.SetDelayCount(1);
		_ani_dash_down.SetDelayCount(1);
		_ani_dash_up.SetDelayCount(1);
		_ani_run_down.SetDelayCount(2);
		_ani_run_up.SetDelayCount(2);
		_ani_run_right.SetDelayCount(2);
		_ani_run_left.SetDelayCount(2);
		_ani_useSkill_1_up.SetDelayCount(2);
		_ani_useSkill_1_down.SetDelayCount(2);
		_ani_useSkill_1_left.SetDelayCount(2);
		_ani_useSkill_1_right.SetDelayCount(2);
		_ani_useSkill_2_down.SetDelayCount(1);
		_ani_useSkill_2_up.SetDelayCount(1);
		_ani_useSkill_2_left.SetDelayCount(1);
		_ani_useSkill_2_right.SetDelayCount(1);
		_ani_useSkill_3_down.SetDelayCount(1);
		_ani_useSkill_3_up.SetDelayCount(1);
		_ani_magic_buff.SetDelayCount(3);
		_ani_die.SetDelayCount(2);
		_ani_transfer.SetDelayCount(1);

		_hp = CharacterData::Instance().HP();
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = _isDash = _isRunning = false;
		_dx = 0;
		_dy = 0;
		_direction = DOWN; //面向下
		_run_counter = 45;
		_isDashLock = false;
		_dash_delay_counter = DASH_COOLDOWN_TIME;
		_dash_counter = 9;
		_isUsingSkill = false;
		_isHurt = false;
		_dash_resistance = 1;
		_hit_recover_counter = 0;
		_magic_buff_counter = 0;
		_is_magic_buff_init = true;
		_isDead = false;
		_mp_decrease_counter = MP_DECREASE_TIME;;
		_skill_cooldown_counter[0] = _skill_cooldown_counter[1] = _skill_cooldown_counter[2] = 0;
		_isDrop = false;
		_drop_counter = DROP_COUNTER_TIME;
		_trap_counter = TRAP_COUNTER_TIME;
		_isTransfer = false;
	}

	void Character::LoadBitmap()
	{
		int source1[10] = { CHARACTER_DOWN_01,CHARACTER_DOWN_02,CHARACTER_DOWN_03,CHARACTER_DOWN_04,CHARACTER_DOWN_05,
			CHARACTER_DOWN_06,CHARACTER_DOWN_07,CHARACTER_DOWN_08,CHARACTER_DOWN_09,CHARACTER_DOWN_10 };
		for (int i = 0; i < 10; i++)
			_ani_down.AddBitmap(source1[i], RGB(50, 255, 0));

		int source2[10] = { CHARACTER_UP_01,CHARACTER_UP_02,CHARACTER_UP_03,CHARACTER_UP_04,CHARACTER_UP_05,
			CHARACTER_UP_06,CHARACTER_UP_07,CHARACTER_UP_08,CHARACTER_UP_09,CHARACTER_UP_10 };
		for (int i = 0; i < 10; i++)
			_ani_up.AddBitmap(source2[i], RGB(50, 255, 0));

		int source3[9] = { CHARACTER_LEFT_01,CHARACTER_LEFT_02,CHARACTER_LEFT_03,CHARACTER_LEFT_04,CHARACTER_LEFT_05,
			CHARACTER_LEFT_06,CHARACTER_LEFT_07,CHARACTER_LEFT_08,CHARACTER_LEFT_09 };
		for (int i = 0; i < 9; i++)
			_ani_left.AddBitmap(source3[i], RGB(50, 255, 0));

		int source4[9] = { CHARACTER_RIGHT_01,CHARACTER_RIGHT_02,CHARACTER_RIGHT_03,CHARACTER_RIGHT_04,CHARACTER_RIGHT_05,
			CHARACTER_RIGHT_06,CHARACTER_RIGHT_07,CHARACTER_RIGHT_08,CHARACTER_RIGHT_09 };
		for (int i = 0; i < 9; i++)
			_ani_right.AddBitmap(source4[i], RGB(50, 255, 0));

		int source5[4] = { CHARACTER_RUN_DOWN_01,CHARACTER_RUN_DOWN_02,CHARACTER_RUN_DOWN_03,CHARACTER_RUN_DOWN_04 };
		for (int i = 0; i < 4; i++)
			_ani_run_down.AddBitmap(source5[i], RGB(50, 255, 0));

		int source6[5] = { CHARACTER_RUN_UP_01,CHARACTER_RUN_UP_02,CHARACTER_RUN_UP_03,CHARACTER_RUN_UP_04, CHARACTER_RUN_UP_05 };
		for (int i = 0; i < 5; i++)
			_ani_run_up.AddBitmap(source6[i], RGB(50, 255, 0));

		int source7[4] = { CHARACTER_RUN_LEFT_01,CHARACTER_RUN_LEFT_02,CHARACTER_RUN_LEFT_03,CHARACTER_RUN_LEFT_03 };
		for (int i = 0; i < 4; i++)
			_ani_run_left.AddBitmap(source7[i], RGB(50, 255, 0));

		int source8[4] = { CHARACTER_RUN_RIGHT_01,CHARACTER_RUN_RIGHT_02,CHARACTER_RUN_RIGHT_03,CHARACTER_RUN_RIGHT_03 };
		for (int i = 0; i < 4; i++)
			_ani_run_right.AddBitmap(source8[i], RGB(50, 255, 0));

		int source9[9] = { CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_02,
			CHARACTER_DASH_UP_03,CHARACTER_DASH_UP_03,CHARACTER_DASH_UP_04,CHARACTER_DASH_UP_04 };
		for (int i = 0; i < 9; i++)
			_ani_dash_up.AddBitmap(source9[i], RGB(50, 255, 0));

		int source10[9] = { CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_02,
			CHARACTER_DASH_DOWN_03,CHARACTER_DASH_DOWN_03,CHARACTER_DASH_DOWN_04,CHARACTER_DASH_DOWN_04 };
		for (int i = 0; i < 9; i++)
			_ani_dash_down.AddBitmap(source10[i], RGB(50, 255, 0));

		int source11[9] = { CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_02,
			CHARACTER_DASH_LEFT_02,CHARACTER_DASH_LEFT_03,CHARACTER_DASH_LEFT_04,CHARACTER_DASH_LEFT_05 };
		for (int i = 0; i < 9; i++)
			_ani_dash_left.AddBitmap(source11[i], RGB(50, 255, 0));

		int source12[9] = { CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_02,
			CHARACTER_DASH_RIGHT_02,CHARACTER_DASH_RIGHT_03,CHARACTER_DASH_RIGHT_04,CHARACTER_DASH_RIGHT_05 };
		for (int i = 0; i < 9; i++)
			_ani_dash_right.AddBitmap(source12[i], RGB(50, 255, 0));

		//-------------------skill 1-------------------//
		int source13[5] = { CHARACTER_SKILL_AIR_SPINNER_UP_01, CHARACTER_SKILL_AIR_SPINNER_UP_02, CHARACTER_SKILL_AIR_SPINNER_UP_03, CHARACTER_SKILL_AIR_SPINNER_UP_04, CHARACTER_SKILL_AIR_SPINNER_UP_05 };
		for (int i = 0; i < 5; i++)
			_ani_useSkill_1_up.AddBitmap(source13[i], RGB(50, 255, 0));

		int source14[5] = { CHARACTER_SKILL_AIR_SPINNER_DOWN_01, CHARACTER_SKILL_AIR_SPINNER_DOWN_02, CHARACTER_SKILL_AIR_SPINNER_DOWN_03, CHARACTER_SKILL_AIR_SPINNER_DOWN_04, CHARACTER_SKILL_AIR_SPINNER_DOWN_05 };
		for (int i = 0; i < 5; i++)
			_ani_useSkill_1_down.AddBitmap(source14[i], RGB(50, 255, 0));
	
		int source15[5] = { CHARACTER_SKILL_AIR_SPINNER_LEFT_01, CHARACTER_SKILL_AIR_SPINNER_LEFT_02, CHARACTER_SKILL_AIR_SPINNER_LEFT_03, CHARACTER_SKILL_AIR_SPINNER_LEFT_04, CHARACTER_SKILL_AIR_SPINNER_LEFT_05 };
		for (int i = 0; i < 5; i++)
			_ani_useSkill_1_left.AddBitmap(source15[i], RGB(50, 255, 0));

		int source16[5] = { CHARACTER_SKILL_AIR_SPINNER_RIGHT_01, CHARACTER_SKILL_AIR_SPINNER_RIGHT_02, CHARACTER_SKILL_AIR_SPINNER_RIGHT_03, CHARACTER_SKILL_AIR_SPINNER_RIGHT_04, CHARACTER_SKILL_AIR_SPINNER_RIGHT_05 };
		for (int i = 0; i < 5; i++)
			_ani_useSkill_1_right.AddBitmap(source16[i], RGB(50, 255, 0));

		//-------------------skill 2-------------------//
		int source17[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_01, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_02, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_03, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_04, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_05,
			CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_06, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_07, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_08, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_09, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_10,
			CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_down.AddBitmap(source17[i], RGB(50, 255, 0));

		int source18[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_UP_01, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_02, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_03, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_04, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_05,
			CHARACTER_SKILL_REBOUNDING_ICICLES_UP_06, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_07, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_08, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_09, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_10,
			CHARACTER_SKILL_REBOUNDING_ICICLES_UP_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_up.AddBitmap(source18[i], RGB(50, 255, 0));

		int source19[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_01, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_02, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_03, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_04, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_05,
			CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_06, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_07, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_08, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_09, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_10,
			CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_left.AddBitmap(source19[i], RGB(50, 255, 0));

		int source20[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_01, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_02, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_03, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_04, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_05,
			CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_06, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_07, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_08, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_09, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_10,
			CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_right.AddBitmap(source20[i], RGB(50, 255, 0));

		//-------------------skill 3-------------------//
		int source21[14] = { CHARACTER_SKILL_SHOCK_NOVA_DOWN_01, CHARACTER_SKILL_SHOCK_NOVA_DOWN_02, CHARACTER_SKILL_SHOCK_NOVA_DOWN_03, CHARACTER_SKILL_SHOCK_NOVA_DOWN_04, CHARACTER_SKILL_SHOCK_NOVA_DOWN_05,
			CHARACTER_SKILL_SHOCK_NOVA_DOWN_06, CHARACTER_SKILL_SHOCK_NOVA_DOWN_07, CHARACTER_SKILL_SHOCK_NOVA_DOWN_08, CHARACTER_SKILL_SHOCK_NOVA_DOWN_09, CHARACTER_SKILL_SHOCK_NOVA_DOWN_10,
			CHARACTER_SKILL_SHOCK_NOVA_DOWN_11, CHARACTER_SKILL_SHOCK_NOVA_DOWN_12, CHARACTER_SKILL_SHOCK_NOVA_DOWN_13, CHARACTER_SKILL_SHOCK_NOVA_DOWN_14 };
		for (int i = 0; i < 14; i++)
			_ani_useSkill_3_down.AddBitmap(source21[i], RGB(50, 255, 0));

		int source22[14] = { CHARACTER_SKILL_SHOCK_NOVA_UP_01, CHARACTER_SKILL_SHOCK_NOVA_UP_02, CHARACTER_SKILL_SHOCK_NOVA_UP_03, CHARACTER_SKILL_SHOCK_NOVA_UP_04, CHARACTER_SKILL_SHOCK_NOVA_UP_05,
			CHARACTER_SKILL_SHOCK_NOVA_UP_06, CHARACTER_SKILL_SHOCK_NOVA_UP_07, CHARACTER_SKILL_SHOCK_NOVA_UP_08, CHARACTER_SKILL_SHOCK_NOVA_UP_09, CHARACTER_SKILL_SHOCK_NOVA_UP_10,
			CHARACTER_SKILL_SHOCK_NOVA_UP_11, CHARACTER_SKILL_SHOCK_NOVA_UP_12, CHARACTER_SKILL_SHOCK_NOVA_UP_13, CHARACTER_SKILL_SHOCK_NOVA_UP_14 };
		for (int i = 0; i < 14; i++)
			_ani_useSkill_3_up.AddBitmap(source22[i], RGB(50, 255, 0));

		int source23[10] = { UI_MAGIC_BUFF_01, UI_MAGIC_BUFF_02, UI_MAGIC_BUFF_03, UI_MAGIC_BUFF_04, UI_MAGIC_BUFF_05,
			UI_MAGIC_BUFF_06, UI_MAGIC_BUFF_07, UI_MAGIC_BUFF_08, UI_MAGIC_BUFF_09, UI_MAGIC_BUFF_10 };
		for (int i = 0; i < 10; i++)
			_ani_magic_buff.AddBitmap(source23[i], RGB(50, 255, 0));

		int source24[22] = { CHARACTER_DIE_01, CHARACTER_DIE_02, CHARACTER_DIE_03, CHARACTER_DIE_04, CHARACTER_DIE_05, CHARACTER_DIE_06, CHARACTER_DIE_07, CHARACTER_DIE_08,
						CHARACTER_DIE_09, CHARACTER_DIE_10, CHARACTER_DIE_11, CHARACTER_DIE_12, CHARACTER_DIE_13, CHARACTER_DIE_14, CHARACTER_DIE_15, CHARACTER_DIE_16,
						CHARACTER_DIE_17, CHARACTER_DIE_18, CHARACTER_DIE_19, CHARACTER_DIE_20, CHARACTER_DIE_21, CHARACTER_DIE_22 };
		for (int i = 0; i < 22; i++)
			_ani_die.AddBitmap(source24[i], RGB(50, 255, 0));

		int source25[8] = { TRANSFER_01, TRANSFER_02, TRANSFER_03, TRANSFER_04, TRANSFER_05, TRANSFER_06, TRANSFER_07, TRANSFER_08 };
		for (int i = 0; i < 8; i++)
			_ani_transfer.AddBitmap(source25[i], RGB(50, 255, 0));

		_bm_stand_down.LoadBitmap(CHARACTER_STAND_DOWN, RGB(50, 255, 0));
		_bm_stand_up.LoadBitmap(CHARACTER_STAND_UP, RGB(50, 255, 0));
		_bm_stand_left.LoadBitmap(CHARACTER_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(CHARACTER_STAND_RIGHT, RGB(50, 255, 0));
		_bm_hurt_left.LoadBitmap(CHARACTER_HURT_LEFT, RGB(50, 255, 0));
		_bm_hurt_right.LoadBitmap(CHARACTER_HURT_RIGHT, RGB(50, 255, 0));
		_bm_fall_up.LoadBitmap(CHARACTER_FALL_UP, RGB(50, 255, 0));
		_bm_fall_down.LoadBitmap(CHARACTER_FALL_DOWN, RGB(50, 255, 0));

		SetXY();
	}

	void Character::SetXY()
	{
		_ani_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_dash_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_dash_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_dash_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_dash_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_run_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_run_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_run_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_run_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_stand_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_stand_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_stand_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_stand_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_1_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_1_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_1_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_1_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_3_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_3_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_hurt_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_hurt_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_magic_buff.SetTopLeft(CHARACTER_SCREEN_X + 25, CHARACTER_SCREEN_Y - 15);
		_ani_die.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_transfer.SetTopLeft(CHARACTER_SCREEN_X + 15, CHARACTER_SCREEN_Y - 5);
		_bm_fall_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_fall_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
	}

	void Character::OnMove(GameMap *map)
	{
		IsHurt();
		MagicBuff();

		for (int i = 0; i < 3; i++)
			_skill_cooldown_counter[i] > 0 ? _skill_cooldown_counter[i]-- : NULL;

		if (_isDead)
		{
			_ani_die.OnMove();
		}
		else if (_isHurt)
		{
			_dash_delay_counter = DASH_COOLDOWN_TIME;
			ResetDash();
			ResetRun();
		}
		else if (_isUsingSkill)
		{
			ResetRun();
			_ani_useSkill->OnMove();
		}
		else
		{
			if (!_isDashLock)
			{
				_dx = 0;
				_dy = 0;

				//初始移動系數
				if (_isDash)
					_step = DASH_STEP * CharacterData::Instance().MOVE_COEFFICIENT() * _dash_resistance;
				else if (_isRunning)
					_step = RUN_STEP * CharacterData::Instance().MOVE_COEFFICIENT();
				else
					_step = WALK_STEP * CharacterData::Instance().MOVE_COEFFICIENT();

				//計算移動距離		
				if (IsSlash()) //如果斜走
				{
					if (_isMovingDown)
						_dy += _step * SLASH_COEFFICIENT;

					if (_isMovingUp)
						_dy -= _step * SLASH_COEFFICIENT;

					if (_isMovingRight)
						_dx += _step * SLASH_COEFFICIENT;

					if (_isMovingLeft)
						_dx -= _step * SLASH_COEFFICIENT;
				}
				else
				{
					if (_isMovingDown)
						_dy += _step;

					if (_isMovingUp)
						_dy -= _step;

					if (_isMovingRight)
						_dx += _step;

					if (_isMovingLeft)
						_dx -= _step;
				}

				if (_isDash && !IsMoving())
				{
					switch (_direction)
					{
					case RIGHT:
						_dx = _step;
						break;
					case LEFT:
						_dx = -_step;
						break;
					case DOWN:
						_dy = _step;
						break;
					case UP:
						_dy = -_step;
						break;
					}
				}
			}

			//判斷方向
			if (_isDash && IsMoving() && IsSlash()) //在斜向移動時按空白鍵，朝移動方向滑動
			{
				if (_isMovingDown)
					_isDashLock ? NULL : _direction = DOWN;		//Dash中不能改方向
				else
					_isDashLock ? NULL : _direction = UP;
			}
			else if (_dx != 0 && !_isDashLock)
			{
				if (_dx < 0)
					_direction = LEFT;	//左
				else
					_direction = RIGHT;	//右
			}
			else if (!_isDashLock)
			{
				if (_dy < 0)
					_direction = UP;	//上
				else if (_dy > 0)
					_direction = DOWN;	//下
			}

			//維持上一格狀態的方向
			if (_dash_delay_counter < DASH_COOLDOWN_TIME && _dash_delay_counter > 0)
				_dash_delay_counter--;
			else
				_dash_delay_counter = DASH_COOLDOWN_TIME;

			//動畫
			if (_isDash)
			{
				ResetRun();
				_ani_dash_right.OnMove();
				_ani_dash_left.OnMove();
				_ani_dash_down.OnMove();
				_ani_dash_up.OnMove();
				_dash_counter--;
				_isDashLock = true;

				if (_dash_counter < 3)
					_dash_resistance *= 0.1;

				if (_dash_counter == 0)
					ResetDash();

			}
			else if (IsMoving())   //走動
			{
				if (_run_counter >= 0)
					_run_counter--;
				if (_run_counter < 0)
					_isRunning = true;

				switch (_direction)
				{
				case RIGHT:
					_ani_right.OnMove();
					break;
				case LEFT:
					_ani_left.OnMove();
					break;
				case DOWN:
					_ani_down.OnMove();
					break;
				case UP:
					_ani_up.OnMove();
					break;
				}
			}
			else    //站著不動
			{
				ResetRun();
			}
			if (_isRunning)			//跑步氣流動畫
			{
				switch (_direction)
				{
				case RIGHT:
					if (!_ani_run_right.IsFinalBitmap())
						_ani_run_right.OnMove();
					break;
				case LEFT:
					if (!_ani_run_left.IsFinalBitmap())
						_ani_run_left.OnMove();
					break;
				case DOWN:
					if (!_ani_run_down.IsFinalBitmap())
						_ani_run_down.OnMove();
					break;
				case UP:
					if (!_ani_run_up.IsFinalBitmap())
						_ani_run_up.OnMove();
					break;
				}
			}
			else
			{
				_ani_run_right.Reset();
				_ani_run_left.Reset();
				_ani_run_down.Reset();
				_ani_run_up.Reset();
			}
			//更新角色在map的位置
			map->SetCharacterXY(_dx, _dy);
			_xy[0] = map->GetCharacterPosition()[0];
			_xy[1] = map->GetCharacterPosition()[1];
		}
		//掉落
		DropDown(map);
	}

	void Character::OnShow()
	{
		if (_isDead)
		{
			_ani_die.OnShow();
		}
		else if (_isHurt)
		{
			switch (_direction)
			{
			case RIGHT:
				_bm_hurt_right.ShowBitmap();
				break;
			case LEFT:
				_bm_hurt_left.ShowBitmap();
				break;
			case DOWN:
				_bm_hurt_right.ShowBitmap();
				break;
			case UP:
				_bm_hurt_left.ShowBitmap();
				break;
			}
		}
		else if (_isUsingSkill)
		{
			_ani_useSkill->OnShow();

			if (_ani_useSkill->IsFinalBitmap())
			{
				_isUsingSkill = false;
				_ani_useSkill->Reset();
			}
		}
		else if (_isDash)
		{
			switch (_direction)
			{
			case RIGHT:
				_ani_dash_right.OnShow();
				break;
			case LEFT:
				_ani_dash_left.OnShow();
				break;
			case DOWN:
				_ani_dash_down.OnShow();
				break;
			case UP:
				_ani_dash_up.OnShow();
				break;
			}
		}
		else if (_isDrop)
		{
			if (!_isTransfer)
			{
				switch (_direction)
				{
				case UP:
					_bm_fall_up.ShowBitmap(0.8);
					break;
				case LEFT:
					_bm_fall_down.ShowBitmap(0.8);
					break;
				case DOWN:
					_bm_fall_down.ShowBitmap(0.8);
					break;
				case RIGHT:
					_bm_fall_down.ShowBitmap(0.8);
					break;
				}
			}	
			else
			{
				_ani_transfer.OnShow();
			}
		}
		else
		{
			if (_isRunning && !_ani_run_right.IsFinalBitmap() && !_ani_run_left.IsFinalBitmap()
				&& !_ani_run_down.IsFinalBitmap() && !_ani_run_up.IsFinalBitmap())
			{
				switch (_direction)
				{
				case RIGHT:
					_ani_run_right.OnShow();
					break;
				case LEFT:
					_ani_run_left.OnShow();
					break;
				case DOWN:
					_ani_run_down.OnShow();
					break;
				case UP:
					_ani_run_up.OnShow();
					break;
				}
			}

			if (_dx != 0 || _dy != 0) {
				switch (_direction)
				{
				case RIGHT:
					_ani_right.OnShow();
					break;
				case LEFT:
					_ani_left.OnShow();
					break;
				case DOWN:
					_ani_down.OnShow();
					break;
				case UP:
					_ani_up.OnShow();
					break;
				default:
					break;
				}
			}
			else
			{
				switch (_direction)
				{
				case RIGHT:
					_bm_stand_right.ShowBitmap();
					break;
				case LEFT:
					_bm_stand_left.ShowBitmap();
					break;
				case DOWN:
					_bm_stand_down.ShowBitmap();
					break;
				case UP:
					_bm_stand_up.ShowBitmap();
					break;
				default:
					break;
				}
			}
		}

		if (CharacterData::Instance().ISMAGICBUFF())
			_ani_magic_buff.OnShow();
	}

	void Character::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void Character::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void Character::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}

	bool Character::IsSlash()
	{
		if (_isMovingRight != _isMovingLeft)
			if (_isMovingUp != _isMovingDown)
				return true;

		return false;
	}

	bool Character::IsMoving()
	{
		if (_isMovingDown || _isMovingLeft || _isMovingRight || _isMovingUp)
			return true;
		return false;
	}

	void Character::Dash()
	{
		if (CanDash())
		{
			_safePosition[0] = _xy[0];
			_safePosition[1] = _xy[1];
			CharacterData::Instance().SetInvincible(true);
			_isDash = true;
			_isRunning = false;
			_dash_delay_counter--;
			CAudio::Instance()->Play(AUDIO_DASH, false);
		}
	}

	bool Character::CanDash()
	{
		if (_dash_delay_counter == DASH_COOLDOWN_TIME && !_isHurt && !_isDrop)
			return true;
		return false;
	}

	Skill* Character::GenerateSkill(int skillNum, float x, float y)
	{
		if (skillNum == 1)
		{
			int direction = CaculateVector(x, y);

			if (!_isUsingSkill && _skill_cooldown_counter[0] == 0 )
			{
				switch (direction)
				{
				case UP:
					_ani_useSkill = &_ani_useSkill_1_up;
					break;
				case DOWN:
					_ani_useSkill = &_ani_useSkill_1_down;
					break;
				case LEFT:
					_ani_useSkill = &_ani_useSkill_1_left;
					break;
				case RIGHT:
					_ani_useSkill = &_ani_useSkill_1_right;
					break;
				}

				_isUsingSkill = true;
				_skill_cooldown_counter[0] = AIR_SPINNER_COOLDOWN * CharacterData::Instance().CD_COEFFICIENT();

				return new Skill_Air_Spinner(x, y, _xy);
			}
		}
		else if (skillNum == 2)
		{
			int direction = CaculateVector(x, y);

			if (!_isUsingSkill && _skill_cooldown_counter[1] == 0)
			{
				switch (direction)
				{
				case UP:
					_ani_useSkill = &_ani_useSkill_2_up;
					break;
				case DOWN:
					_ani_useSkill = &_ani_useSkill_2_down;
					break;
				case LEFT:
					_ani_useSkill = &_ani_useSkill_2_left;
					break;
				case RIGHT:
					_ani_useSkill = &_ani_useSkill_2_right;
					break;
				}

				_isUsingSkill = true;
				_skill_cooldown_counter[1] = REBOUNDING_ICICKES_COOLDOWN * CharacterData::Instance().CD_COEFFICIENT();

				return new Skill_Rebounding_Icicles(x, y, _xy);
			}
		}
		else if (skillNum == 3 && _skill_cooldown_counter[2] == 0)
		{
			if (!_isUsingSkill)
			{
				if (_direction == UP)
					_ani_useSkill = &_ani_useSkill_3_up;
				else
					_ani_useSkill = &_ani_useSkill_3_down;

				_isUsingSkill = true;
				_skill_cooldown_counter[2] = SHOCK_NOVA_COOLDOWN * CharacterData::Instance().CD_COEFFICIENT();

				return new Skill_Shock_Nova(x, y, _xy);
			}
		}
		else
			throw "skill num does not exist.";
	}

	bool  Character::IsUsingSkill()
	{
		return _isUsingSkill;
	}

	int Character::CaculateVector(int x, int y)
	{
		float angle = atan2(y - CHARACTER_SCREEN_CENTER_Y, x - CHARACTER_SCREEN_CENTER_X) * 180 / 3.14;

		if (angle <= 45 && angle >= -45)	//右  因為螢幕 Y 軸是往下的
		{
			_direction = RIGHT;
			return RIGHT;
		}
		else if (angle > 45 && angle < 135)
		{
			_direction = DOWN;
			return DOWN;
		}
		else if (angle < -45 && angle > -135)
		{
			_direction = UP;
			return UP;
		}
		else
		{
			_direction = LEFT;
			return LEFT;
		}
	}

	const int* Character::GetHitbox()
	{
		return CHARACTER_HITBOX;
	}

	bool Character::IsHurt()
	{
		if (_hit_recover_counter == 0)
		{
			if (CharacterData::Instance().HP() < _hp)
			{
				_isHurt = true;
				_hit_recover_counter = 5;
			}
			else
				_isHurt = false;

			_hp = CharacterData::Instance().HP();
		}
		else
			_hit_recover_counter > 0 ? _hit_recover_counter-- : NULL;

		return _isHurt;
	}

	void Character::ResetRun()
	{
		_isRunning = false;
		_run_counter = WALK_TO_RUN_TIME;
	}

	void Character::ResetDash()
	{
		CharacterData::Instance().SetInvincible(false);
		_isDashLock = false;
		_isDash = false;
		_ani_dash_right.Reset();
		_ani_dash_left.Reset();
		_ani_dash_down.Reset();
		_ani_dash_up.Reset();
		_dash_counter = 9;
		_dash_resistance = 1;
	}

	void Character::MagicBuff()
	{
		CharacterData* _data = &CharacterData::Instance();
		if (_data->ISMAGICBUFF() == true)
		{
			_is_magic_buff_init ? _data->SetAttackCoefficient(2.0) : NULL;
			_is_magic_buff_init = false;

			_ani_magic_buff.OnMove();

			if (_magic_buff_counter == 0)
			{
				_data->AddMP(-1);
				_magic_buff_counter = MAGIC_BUFF_TIME;
			}

			_data->MP() == 0 ? _data->SetAttackCoefficient(-2.0) : NULL;

			_magic_buff_counter--;
		}
		else
		{
			_is_magic_buff_init = true;

			if (_mp_decrease_counter == 0)
			{
				_data->AddMP(-1);
				_mp_decrease_counter = MP_DECREASE_TIME;
			}
			_mp_decrease_counter--;
		}
	}

	bool Character::Dead()
	{
		_isDead = true;

		if (_ani_die.IsFinalBitmap())
		{
			_ani_die.Reset();
			return true;
		}
		else
			return false;
	}

	bool Character::IsSkillCooldown(int skill_num)
	{
		return _skill_cooldown_counter[skill_num - 1] != 0;
	}

	int Character::GetSkillCooldown(int skill_num)
	{
		return _skill_cooldown_counter[skill_num - 1];
	}

	void Character::SetDrop()
	{
		_isDrop = true;
	}

	bool Character::IsDash()
	{
		return _isDash;
	}

	void Character::DropDown(GameMap* map)
	{
		//判斷是否掉落中reset position
		if (_isDrop)
		{
			//掉落期間鎖住移動
			SetMovingDown(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			SetMovingUp(false);
			_drop_counter--;
			if (_drop_counter > DROP_RESET_ANI_TIME)
			{
				_isTransfer = false;
			}
			else
			{
				_isTransfer = true;
				if (_drop_counter == DROP_RESET_ANI_TIME)
				{
					//復原位置
					map->SetCharacterXY(_safePosition[0] - _xy[0], _safePosition[1] - _xy[1]);
					_xy[0] = map->GetCharacterPosition()[0];
					_xy[1] = map->GetCharacterPosition()[1];
					_safePosition[0] = _xy[0];
					_safePosition[1] = _xy[1];

					//受傷害
					CharacterData::Instance().AddHP(-DROP_DAMAGE);
					_hp -= DROP_DAMAGE;
				}
				else if (_drop_counter < 0)	
				{
					_drop_counter = DROP_COUNTER_TIME;
					_isDrop = false;
				}
				else
					_ani_transfer.OnMove();	//播動畫
			}
		}
	}

	void Character::Trap(GameMap* map)
	{
		if (_trap_counter > 0)
		{
			_trap_counter--;
		}
		else
		{
			CharacterData::Instance().AddHP(-TRAP_DAMAGE);
			_trap_counter = TRAP_COUNTER_TIME;
		}
	}
}