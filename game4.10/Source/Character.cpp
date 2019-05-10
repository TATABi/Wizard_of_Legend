#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Skill_Rebounding_Icicles.h"
#include "Skill_Shock_Nova.h"
#include "math.h"

const float M_PI = atan(1.0) * 4;

namespace game_framework {

	Character::Character()
	{
		int xy[2] = { 0, 0 };
		Initialize(xy);
	}

	void Character::Initialize(int* xy)
	{
		this->_xy[0] = xy[0];
		this->_xy[1] = xy[1];
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

		_ani_useSkill_1.SetDelayCount(1);
		_ani_useSkill_2_down.SetDelayCount(1);
		_ani_useSkill_2_up.SetDelayCount(1);
		_ani_useSkill_2_left.SetDelayCount(1);
		_ani_useSkill_2_right.SetDelayCount(1);
		_ani_useSkill_3_down.SetDelayCount(1);
		_ani_useSkill_3_up.SetDelayCount(1);

		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = _isDash = _isRunning = false;
		_horizontal = 0;
		_vertical = 0;
		_directionFlag = DOWN; //面向下
		_run_counter = 45;
		_isDashLock = false;
		_isSlash = false;
		_dash_delay_counter = DASH_DELAY;
		_dash_counter = 9;
		_isUsingSkill = false;
		_isHurt = false;
		_useSkillNum = 0;
		_dash_resistance = 1;
		_hit_recover_counter = 0;
		
	}

	void Character::LoadBitmap()
	{
		int m1[10] = { CHARACTER_DOWN_01,CHARACTER_DOWN_02,CHARACTER_DOWN_03,CHARACTER_DOWN_04,CHARACTER_DOWN_05,
					   CHARACTER_DOWN_06,CHARACTER_DOWN_07,CHARACTER_DOWN_08,CHARACTER_DOWN_09,CHARACTER_DOWN_10};
		for (int i = 0; i < 10; i++)
			_ani_down.AddBitmap(m1[i], RGB(50, 255, 0));

		int m2[10] = { CHARACTER_UP_01,CHARACTER_UP_02,CHARACTER_UP_03,CHARACTER_UP_04,CHARACTER_UP_05,
			           CHARACTER_UP_06,CHARACTER_UP_07,CHARACTER_UP_08,CHARACTER_UP_09,CHARACTER_UP_10 };
		for (int i = 0; i < 10; i++)
			_ani_up.AddBitmap(m2[i], RGB(50, 255, 0));

		int m3[9] = { CHARACTER_LEFT_01,CHARACTER_LEFT_02,CHARACTER_LEFT_03,CHARACTER_LEFT_04,CHARACTER_LEFT_05,
					  CHARACTER_LEFT_06,CHARACTER_LEFT_07,CHARACTER_LEFT_08,CHARACTER_LEFT_09 };
		for (int i = 0; i < 9; i++)
			_ani_left.AddBitmap(m3[i], RGB(50, 255, 0));

		int m4[9] = { CHARACTER_RIGHT_01,CHARACTER_RIGHT_02,CHARACTER_RIGHT_03,CHARACTER_RIGHT_04,CHARACTER_RIGHT_05,
				      CHARACTER_RIGHT_06,CHARACTER_RIGHT_07,CHARACTER_RIGHT_08,CHARACTER_RIGHT_09 };
		for (int i = 0; i < 9; i++)
			_ani_right.AddBitmap(m4[i], RGB(50, 255, 0));

		int m5[9] = { CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_01,CHARACTER_DASH_UP_02,
					  CHARACTER_DASH_UP_03,CHARACTER_DASH_UP_03,CHARACTER_DASH_UP_04,CHARACTER_DASH_UP_04 };
		for (int i = 0; i < 9; i++)
			_ani_dash_up.AddBitmap(m5[i], RGB(50, 255, 0));

		int m6[9] = { CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_01,CHARACTER_DASH_DOWN_02,
					  CHARACTER_DASH_DOWN_03,CHARACTER_DASH_DOWN_03,CHARACTER_DASH_DOWN_04,CHARACTER_DASH_DOWN_04 };
		for (int i = 0; i < 9; i++)
			_ani_dash_down.AddBitmap(m6[i], RGB(50, 255, 0));


		int m7[9] = { CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_01,CHARACTER_DASH_LEFT_02,
					  CHARACTER_DASH_LEFT_02,CHARACTER_DASH_LEFT_03,CHARACTER_DASH_LEFT_04,CHARACTER_DASH_LEFT_05 };
		for (int i = 0; i < 9; i++)
			_ani_dash_left.AddBitmap(m7[i], RGB(50, 255, 0));

		int m8[9] = { CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_01,CHARACTER_DASH_RIGHT_02,
					  CHARACTER_DASH_RIGHT_02,CHARACTER_DASH_RIGHT_03,CHARACTER_DASH_RIGHT_04,CHARACTER_DASH_RIGHT_05 };
		for (int i = 0; i < 9; i++)
			_ani_dash_right.AddBitmap(m8[i], RGB(50, 255, 0));

		int m9[4] = { CHARACTER_RUN_DOWN_01,CHARACTER_RUN_DOWN_02,CHARACTER_RUN_DOWN_03,CHARACTER_RUN_DOWN_04 };
		for (int i = 0; i < 4; i++)
			_ani_run_down.AddBitmap(m9[i], RGB(50, 255, 0));

		int m10[5] = { CHARACTER_RUN_UP_01,CHARACTER_RUN_UP_02,CHARACTER_RUN_UP_03,CHARACTER_RUN_UP_04, CHARACTER_RUN_UP_05 };
		for (int i = 0; i < 5; i++)
			_ani_run_up.AddBitmap(m10[i], RGB(50, 255, 0));

		int m11[4] = { CHARACTER_RUN_LEFT_01,CHARACTER_RUN_LEFT_02,CHARACTER_RUN_LEFT_03,CHARACTER_RUN_LEFT_03 };
		for (int i = 0; i < 4; i++)
			_ani_run_left.AddBitmap(m11[i], RGB(50, 255, 0));
		
		int m12[4] = { CHARACTER_RUN_RIGHT_01,CHARACTER_RUN_RIGHT_02,CHARACTER_RUN_RIGHT_03,CHARACTER_RUN_RIGHT_03 };
		for (int i = 0; i < 4; i++)
			_ani_run_right.AddBitmap(m12[i], RGB(50, 255, 0));
		
		//////temp
		int m13[14] = {CHARACTER_SKILL_SHOCK_NOVA_UP_01, CHARACTER_SKILL_SHOCK_NOVA_UP_02, CHARACTER_SKILL_SHOCK_NOVA_UP_03, CHARACTER_SKILL_SHOCK_NOVA_UP_04, CHARACTER_SKILL_SHOCK_NOVA_UP_05,
			CHARACTER_SKILL_SHOCK_NOVA_UP_06, CHARACTER_SKILL_SHOCK_NOVA_UP_07, CHARACTER_SKILL_SHOCK_NOVA_UP_08, CHARACTER_SKILL_SHOCK_NOVA_UP_09, CHARACTER_SKILL_SHOCK_NOVA_UP_10,
			CHARACTER_SKILL_SHOCK_NOVA_UP_11, CHARACTER_SKILL_SHOCK_NOVA_UP_12, CHARACTER_SKILL_SHOCK_NOVA_UP_13, CHARACTER_SKILL_SHOCK_NOVA_UP_14 };
		for (int i = 0; i < 14; i++)
			_ani_useSkill_1.AddBitmap(m13[i], RGB(50, 255, 0));
		////////
		int m14_1[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_01, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_02, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_03, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_04, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_05,
						CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_06, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_07, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_08, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_09, CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_10,
						CHARACTER_SKILL_REBOUNDING_ICICLES_DOWN_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_down.AddBitmap(m14_1[i], RGB(50, 255, 0));

		int m14_2[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_UP_01, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_02, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_03, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_04, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_05,
						  CHARACTER_SKILL_REBOUNDING_ICICLES_UP_06, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_07, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_08, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_09, CHARACTER_SKILL_REBOUNDING_ICICLES_UP_10,
						  CHARACTER_SKILL_REBOUNDING_ICICLES_UP_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_up.AddBitmap(m14_2[i], RGB(50, 255, 0));

		int m14_3[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_01, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_02, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_03, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_04, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_05,
						  CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_06, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_07, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_08, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_09, CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_10,
						  CHARACTER_SKILL_REBOUNDING_ICICLES_LEFT_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_left.AddBitmap(m14_3[i], RGB(50, 255, 0));

		int m14_4[11] = { CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_01, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_02, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_03, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_04, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_05,
						  CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_06, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_07, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_08, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_09, CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_10,
					      CHARACTER_SKILL_REBOUNDING_ICICLES_RIGHT_11 };
		for (int i = 0; i < 11; i++)
			_ani_useSkill_2_right.AddBitmap(m14_4[i], RGB(50, 255, 0));

		int m15[14] = { CHARACTER_SKILL_SHOCK_NOVA_DOWN_01, CHARACTER_SKILL_SHOCK_NOVA_DOWN_02, CHARACTER_SKILL_SHOCK_NOVA_DOWN_03, CHARACTER_SKILL_SHOCK_NOVA_DOWN_04, CHARACTER_SKILL_SHOCK_NOVA_DOWN_05,
						CHARACTER_SKILL_SHOCK_NOVA_DOWN_06, CHARACTER_SKILL_SHOCK_NOVA_DOWN_07, CHARACTER_SKILL_SHOCK_NOVA_DOWN_08, CHARACTER_SKILL_SHOCK_NOVA_DOWN_09, CHARACTER_SKILL_SHOCK_NOVA_DOWN_10,
						CHARACTER_SKILL_SHOCK_NOVA_DOWN_11, CHARACTER_SKILL_SHOCK_NOVA_DOWN_12, CHARACTER_SKILL_SHOCK_NOVA_DOWN_13, CHARACTER_SKILL_SHOCK_NOVA_DOWN_14 };
		for (int i = 0; i < 14; i++)
			_ani_useSkill_3_down.AddBitmap(m15[i], RGB(50, 255, 0));

		
		int m16[14] = { CHARACTER_SKILL_SHOCK_NOVA_UP_01, CHARACTER_SKILL_SHOCK_NOVA_UP_02, CHARACTER_SKILL_SHOCK_NOVA_UP_03, CHARACTER_SKILL_SHOCK_NOVA_UP_04, CHARACTER_SKILL_SHOCK_NOVA_UP_05,
						CHARACTER_SKILL_SHOCK_NOVA_UP_06, CHARACTER_SKILL_SHOCK_NOVA_UP_07, CHARACTER_SKILL_SHOCK_NOVA_UP_08, CHARACTER_SKILL_SHOCK_NOVA_UP_09, CHARACTER_SKILL_SHOCK_NOVA_UP_10,
						CHARACTER_SKILL_SHOCK_NOVA_UP_11, CHARACTER_SKILL_SHOCK_NOVA_UP_12, CHARACTER_SKILL_SHOCK_NOVA_UP_13, CHARACTER_SKILL_SHOCK_NOVA_UP_14};
		for (int i = 0; i < 14; i++)
			_ani_useSkill_3_up.AddBitmap(m16[i], RGB(50, 255, 0));

		
		_bm_stand_down.LoadBitmap(CHARACTER_STAND_DOWN, RGB(50, 255, 0));
		_bm_stand_up.LoadBitmap(CHARACTER_STAND_UP, RGB(50, 255, 0));
		_bm_stand_left.LoadBitmap(CHARACTER_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(CHARACTER_STAND_RIGHT, RGB(50, 255, 0));
		_bm_hurt_left.LoadBitmap(CHARACTER_HURT_LEFT, RGB(50, 255, 0));
		_bm_hurt_right.LoadBitmap(CHARACTER_HURT_RIGHT, RGB(50, 255, 0));

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
		_ani_useSkill_1.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_2_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_3_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_ani_useSkill_3_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_hurt_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		_bm_hurt_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
	}

	void Character::Suffer(int damage)
	{
		CharacterData::HP -= damage;
		_isHurt = true;
		_hit_recover_counter = 30 * 0.5;
	}

	void Character::OnMove(GameMap *map)
	{
		if (_isHurt)
		{
			_run_counter = 0;
			_hit_recover_counter > 0 ? _hit_recover_counter-- : NULL;
			_hit_recover_counter == 0 ? _isHurt = false : NULL;
		}
		else if (_isUsingSkill)
		{
			_run_counter = 0;
			_ani_useSkill->OnMove();
		}
		else {
			if (!_isDashLock)
			{
				_horizontal = 0;
				_vertical = 0;
			}
			//初始移動系數
			if (_isDash)
			{
				_SLASH_PIXEL = (int)(DASH_SLASH_PIXEL * CharacterData::Move_Coefficient) * _dash_resistance;
				_STR_PIXEL = (int)(DASH_STR_PIXEL * CharacterData::Move_Coefficient) * _dash_resistance;
			}
			else if (_isRunning)
			{
				_SLASH_PIXEL = (int)(RUN_SLASH_PIXEL * CharacterData::Move_Coefficient);
				_STR_PIXEL = (int)(RUN_STR_PIXEL * CharacterData::Move_Coefficient);
			}
			else
			{
				_SLASH_PIXEL = (int)(NORMAL_SLASH_PIXEL * CharacterData::Move_Coefficient);
				_STR_PIXEL = (int)(NORMAL_STR_PIXEL * CharacterData::Move_Coefficient);
			}
				//計算移動距離
			if (IsSlash() && !_isDashLock) //如果斜走
			{
				if (_isMovingDown)
				{
					if (_vertical < _SLASH_PIXEL)
						_vertical += _SLASH_PIXEL;
				}
				if (_isMovingUp)
				{
					if (_vertical > -_SLASH_PIXEL)
						_vertical -= _SLASH_PIXEL;
				}
				if (_isMovingRight)
				{
					if (_horizontal < _SLASH_PIXEL)
						_horizontal += _SLASH_PIXEL;
				}
				if (_isMovingLeft)
				{
					if (_horizontal > -_SLASH_PIXEL)
						_horizontal -= _SLASH_PIXEL;
				}
			}
			else if (!_isDashLock)
			{
				if (_isMovingDown)
				{
					if (_vertical < _STR_PIXEL)
						_vertical += _STR_PIXEL;
				}
				if (_isMovingUp)
				{
					if (_vertical > -_STR_PIXEL)
						_vertical -= _STR_PIXEL;
				}
				if (_isMovingRight)
				{
					if (_horizontal < _STR_PIXEL)
						_horizontal += _STR_PIXEL;
				}
				if (_isMovingLeft)
				{
					if (_horizontal > -_STR_PIXEL)
						_horizontal -= _STR_PIXEL;
				}
			}

			//判斷方向
			if (_horizontal != 0 && !_isDashLock)
			{
				if (_horizontal < 0)
					_directionFlag = LEFT;	//左
				else
					_directionFlag = RIGHT;	//右
			}
			else if (!_isDashLock)
			{
				if (_vertical < 0)
					_directionFlag = UP;	//上
				else if (_vertical > 0)
					_directionFlag = DOWN;	//下
			}

			//維持上一格狀態的方向
			if (_dash_delay_counter < DASH_DELAY && _dash_delay_counter > 0)
				_dash_delay_counter--;
			else
				_dash_delay_counter = DASH_DELAY;
			
			//動畫
			if (_isDash)
			{
				_run_counter = 45;
				if (IsMoving() && IsSlash()) //在斜向移動時按空白鍵，朝移動方向滑動
				{
					if (_isMovingDown)
					{
						_isDashLock ? NULL : _directionFlag = DOWN;		//Dash中不能改方向
					}
					else
					{
						_isDashLock ? NULL : _directionFlag = UP;
					}
				}
				else		//停止移動時按空白鍵，朝面相方向滑動(沒有斜向)；或是非斜向移動時		
				{
					switch (_directionFlag)
					{
					case RIGHT:
						_horizontal = _STR_PIXEL;
						break;
					case LEFT:
						_horizontal = -_STR_PIXEL;
						break;
					case DOWN:
						_vertical = _STR_PIXEL;
						break;
					case UP:
						_vertical = -_STR_PIXEL;
						break;
					}
				}
				_ani_dash_right.OnMove();
				_ani_dash_left.OnMove();
				_ani_dash_down.OnMove();
				_ani_dash_up.OnMove();
				_dash_counter--;
				_isDashLock = true;
				if (_dash_counter < 3)
				{
					_dash_resistance *= 0.1;
				}
				if (_dash_counter == 0)
				{
					_isDashLock = false;
					_isDash = false;
					_ani_dash_right.Reset();
					_ani_dash_left.Reset();
					_ani_dash_down.Reset();
					_ani_dash_up.Reset();
					_dash_counter = 9;
					_dash_resistance = 1;
				}
			}
			else if (IsMoving())   //走動
			{
				if (_run_counter >= 0)
					_run_counter--;
				if (_run_counter < 0)
					_isRunning = true;
				switch (_directionFlag)
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
				_isRunning = false;
				_run_counter = 45;
				_ani_run_right.Reset();
				_ani_run_left.Reset();
				_ani_run_down.Reset();
				_ani_run_up.Reset();
			}

			if (_isRunning)			//跑步氣流動畫
			{
				switch (_directionFlag)
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
				int *temp_xy = map->SetCharacterXY(_horizontal, _vertical);	//更新角色在map的位置
				_xy[0] = temp_xy[0];
				_xy[1] = temp_xy[1];
		}
	}

	void Character::Dash()
	{
		if (CanDash())
		{
			_isDash = true;
			_isRunning = false;
			_dash_delay_counter--;
			CAudio::Instance()->Play(AUDIO_DASH, false);
		}
	}

	void Character::OnShow() 
	{	
		/////////////////////////////////  受傷圖片待加上下 /////////////////////////////
		if (_isHurt)
		{
			switch (_directionFlag)
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
			switch (_directionFlag)
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
		else
		{
			if (_isRunning && !_ani_run_right.IsFinalBitmap() && !_ani_run_left.IsFinalBitmap()
				&& !_ani_run_down.IsFinalBitmap() && !_ani_run_up.IsFinalBitmap())
			{
				switch (_directionFlag)
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

			if (_horizontal != 0 || _vertical != 0) {
				switch (_directionFlag)
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
				switch (_directionFlag)
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

	bool Character::CanDash()
	{
		if (_dash_delay_counter == DASH_DELAY)
			return true;
		return false;
	}

	Skill* Character::GenerateSkill(int skillNum, int x, int y)
	{
		int direction = CaculateDirection(x, y);

		if (skillNum == 1)
		{
			if (!_isUsingSkill)
			{
				_isUsingSkill = true;
				_useSkillNum = 1;
				_ani_useSkill = &_ani_useSkill_1;
			}
		}
		else if (skillNum == 2)
		{
			if (!_isUsingSkill)
			{
				_isUsingSkill = true;
				_useSkillNum = 2;

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

				return new Skill_Rebounding_Icicles(x, y, _xy);
			}
		}
		else if (skillNum == 3)
		{
			if (!_isUsingSkill)
			{
				_isUsingSkill = true;
				_useSkillNum = 3;
				
				if (y > SIZE_Y / 2)
					_ani_useSkill = &_ani_useSkill_3_down;
				else
					_ani_useSkill = &_ani_useSkill_3_up;
					
				return new Skill_Shock_Nova(x, y, _xy);
			}
		}
		else
		{
			throw "skill num does not exist.";
		}
	}

	bool  Character::IsUsingSkill()
	{
		return _isUsingSkill;
	}

	int Character::CaculateDirection(int x, int y)
	{
		float angle = atan2(y - CHARACTER_SCREEN_CENTER_Y, x - CHARACTER_SCREEN_CENTER_X) * 180 / 3.14;

		if (angle <= 45 && angle >= -45)	//右  因為螢幕 Y 軸是往下的
		{
			_directionFlag = RIGHT;
			return RIGHT;
		}
		else if (angle > 45 && angle < 135)
		{
			_directionFlag = DOWN;
			return DOWN;
		}
		else if (angle < -45 && angle > -135)
		{
			_directionFlag = UP;
			return UP;
		}
		else
		{
			_directionFlag = LEFT;
			return LEFT;
		}
	}

	int* Character::GetPosition()
	{
		return _xy;
	}

	int* Character::GetHitbox()
	{
		return _hitbox;
	}
}
