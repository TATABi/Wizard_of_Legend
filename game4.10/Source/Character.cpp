#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "Skill_Rebounding_Icicles.h"
#include "Skill_Shock_Nova.h"

namespace game_framework {

	Character::Character()
	{
		int xy[2] = { 0, 0 };
		Initialize(xy);
	}

	void Character::Initialize(int* xy)
	{
		this->xy[0] = xy[0];
		this->xy[1] = xy[1];
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
		_isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = _isDash = _isRunning = false;
		_horizontal = 0;
		_vertical = 0;
		_directionFlag = 2; //面向下
		_run_counter = 45;
		_isDashLock = false;
		_isSlash = false;
		_dash_delay_counter = DASH_DELAY;
		_dash_counter = 9;
		_isUseSkill = false;
		_useSkillCounter = 0;

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
		

		_bm_stand_down.LoadBitmap(CHARACTER_STAND_DOWN, RGB(50, 255, 0));
		_bm_stand_up.LoadBitmap(CHARACTER_STAND_UP, RGB(50, 255, 0));
		_bm_stand_left.LoadBitmap(CHARACTER_STAND_LEFT, RGB(50, 255, 0));
		_bm_stand_right.LoadBitmap(CHARACTER_STAND_RIGHT, RGB(50, 255, 0));

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

	}

	void Character::OnMove(GameMap *map)
	{
		if (_useSkillCounter == 0)
		{

			if (!_isDashLock)
			{
				_horizontal = 0;
				_vertical = 0;
			}

			//初始移動系數
			if (_isDash)
			{
				_SLASH_PIXEL = (int)(DASH_SLASH_PIXEL * CharacterData::Move_Coefficient);
				_STR_PIXEL = (int)(DASH_STR_PIXEL * CharacterData::Move_Coefficient);
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
					_directionFlag = 1;	//左
				else
					_directionFlag = 0;	//右
			}
			else if (!_isDashLock)
			{
				if (_vertical < 0)
					_directionFlag = 3;	//上
				else if (_vertical > 0)
					_directionFlag = 2;	//下
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
						_isDashLock ? NULL : _directionFlag = 2;		//Dash中不能改方向
					}
					else
					{
						_isDashLock ? NULL : _directionFlag = 3;
					}
				}
				else		//停止移動時按空白鍵，朝面相方向滑動(沒有斜向)；或是非斜向移動時		
				{
					switch (_directionFlag)
					{
					case 0:
						_horizontal = _STR_PIXEL;
						break;
					case 1:
						_horizontal = -_STR_PIXEL;
						break;
					case 2:
						_vertical = _STR_PIXEL;
						break;
					case 3:
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

				if (_dash_counter == 0)
				{
					_isDashLock = false;
					_isDash = false;
					_ani_dash_right.Reset();
					_ani_dash_left.Reset();
					_ani_dash_down.Reset();
					_ani_dash_up.Reset();
					_dash_counter = 9;
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
				case 0:
					_ani_right.OnMove();
					break;
				case 1:
					_ani_left.OnMove();
					break;
				case 2:
					_ani_down.OnMove();
					break;
				case 3:
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
				case 0:
					if (!_ani_run_right.IsFinalBitmap())
						_ani_run_right.OnMove();
					break;
				case 1:
					if (!_ani_run_left.IsFinalBitmap())
						_ani_run_left.OnMove();
					break;
				case 2:
					if (!_ani_run_down.IsFinalBitmap())
						_ani_run_down.OnMove();
					break;
				case 3:
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
			xy[0] = temp_xy[0];
			xy[1] = temp_xy[1];
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
		if (_isDash)
		{
			switch (_directionFlag)
			{
			case 0:
				_ani_dash_right.OnShow();
				break;
			case 1:
				_ani_dash_left.OnShow();
				break;
			case 2:
				_ani_dash_down.OnShow();
				break;
			case 3:
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
				case 0:
					_ani_run_right.OnShow();
					break;
				case 1:
					_ani_run_left.OnShow();
					break;
				case 2:
					_ani_run_down.OnShow();
					break;
				case 3:
					_ani_run_up.OnShow();
					break;
				}
			}

			if (_horizontal != 0 || _vertical != 0) {
				switch (_directionFlag)
				{
				case 0:
					_ani_right.OnShow();
					break;
				case 1:
					_ani_left.OnShow();
					break;
				case 2:
					_ani_down.OnShow();
					break;
				case 3:
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
				case 0:
					_bm_stand_right.ShowBitmap();
					break;
				case 1:
					_bm_stand_left.ShowBitmap();
					break;
				case 2:
					_bm_stand_down.ShowBitmap();
					break;
				case 3:
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

	Skill* Character::generateSkill(int skillNum, int x, int y)
	{
		if (skillNum == 1 && _useSkillCounter == 0)
		{
			
		}
		else if (skillNum == 2 && _useSkillCounter == 0)
		{
			return new Skill_Rebounding_Icicles(x, y, xy);
			_useSkillCounter = 30;
		}
		else if (skillNum == 3 && _useSkillCounter == 0)
		{
			return new Skill_Shock_Nova(x, y, xy);
			_useSkillCounter = 30;
		}
	}

}
