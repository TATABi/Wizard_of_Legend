#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"


namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// Character: Character class
	/////////////////////////////////////////////////////////////////////////////

	Character::Character()
	{
		Initialize();
	}

	void Character::Initialize()
	{
		ani_down.SetDelayCount(2);
		ani_up.SetDelayCount(2);
		ani_left.SetDelayCount(2);
		ani_right.SetDelayCount(2);
		ani_dash_right.SetDelayCount(1);
		ani_dash_left.SetDelayCount(1);
		ani_dash_down.SetDelayCount(1);
		ani_dash_up.SetDelayCount(1);
		ani_run_down.SetDelayCount(2);
		ani_run_up.SetDelayCount(2);
		ani_run_right.SetDelayCount(2);
		ani_run_left.SetDelayCount(2);
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isDash = isRunning = false;
		_horizontal = 0;
		_vertical = 0;
		_directionFlag = 2; //面向下
		run_counter = 45;
		dash_lock = false;
		dash_delay_counter = DASH_DELAY;
	}

	void Character::LoadBitmap()
	{
		ani_down.AddBitmap(CHARACTER_DOWN_01, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_02, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_03, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_04, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_05, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_06, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_07, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_08, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_09, RGB(50, 255, 0));
		ani_down.AddBitmap(CHARACTER_DOWN_10, RGB(50, 255, 0));

		ani_up.AddBitmap(CHARACTER_UP_01, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_02, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_03, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_04, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_05, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_06, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_07, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_08, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_09, RGB(50, 255, 0));
		ani_up.AddBitmap(CHARACTER_UP_10, RGB(50, 255, 0));

		ani_left.AddBitmap(CHARACTER_LEFT_01, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_02, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_03, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_04, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_05, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_06, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_07, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_08, RGB(50, 255, 0));
		ani_left.AddBitmap(CHARACTER_LEFT_09, RGB(50, 255, 0));

		ani_right.AddBitmap(CHARACTER_RIGHT_01, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_02, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_03, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_04, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_05, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_06, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_07, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_08, RGB(50, 255, 0));
		ani_right.AddBitmap(CHARACTER_RIGHT_09, RGB(50, 255, 0));

		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_01, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_01, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_01, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_01, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_02, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_03, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_03, RGB(50, 255, 0));
		//ani_dash_up.AddBitmap(CHARACTER_DASH_UP_03, RGB(50, 255, 0));
		//ani_dash_up.AddBitmap(CHARACTER_DASH_UP_04, RGB(50, 255, 0));
		//ani_dash_up.AddBitmap(CHARACTER_DASH_UP_04, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_04, RGB(50, 255, 0));
		ani_dash_up.AddBitmap(CHARACTER_DASH_UP_04, RGB(50, 255, 0));

		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_01, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_01, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_01, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_01, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_02, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_03, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_03, RGB(50, 255, 0));
		//ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_03, RGB(50, 255, 0));
		//ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_04, RGB(50, 255, 0));
		//ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_04, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_04, RGB(50, 255, 0));
		ani_dash_down.AddBitmap(CHARACTER_DASH_DOWN_04, RGB(50, 255, 0));

		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_01, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_01, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_01, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_01, RGB(50, 255, 0));
		//ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_02, RGB(50, 255, 0));
		//ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_02, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_02, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_02, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_03, RGB(50, 255, 0));
		//ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_04, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_04, RGB(50, 255, 0));
		ani_dash_left.AddBitmap(CHARACTER_DASH_LEFT_05, RGB(50, 255, 0));

		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_01, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_01, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_01, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_01, RGB(50, 255, 0));
		//ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_02, RGB(50, 255, 0));
		//ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_02, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_02, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_02, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_03, RGB(50, 255, 0));
		//ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_04, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_04, RGB(50, 255, 0));
		ani_dash_right.AddBitmap(CHARACTER_DASH_RIGHT_05, RGB(50, 255, 0));

		bm_stand_down.LoadBitmap(CHARACTER_STAND_DOWN, RGB(50, 255, 0));
		bm_stand_up.LoadBitmap(CHARACTER_STAND_UP, RGB(50, 255, 0));
		bm_stand_left.LoadBitmap(CHARACTER_STAND_LEFT, RGB(50, 255, 0));
		bm_stand_right.LoadBitmap(CHARACTER_STAND_RIGHT, RGB(50, 255, 0));

		ani_run_down.AddBitmap(CHARACTER_RUN_DOWN_01, RGB(50, 255, 0));
		ani_run_down.AddBitmap(CHARACTER_RUN_DOWN_02, RGB(50, 255, 0));
		ani_run_down.AddBitmap(CHARACTER_RUN_DOWN_03, RGB(50, 255, 0));
		ani_run_down.AddBitmap(CHARACTER_RUN_DOWN_04, RGB(50, 255, 0));

		ani_run_up.AddBitmap(CHARACTER_RUN_UP_01, RGB(50, 255, 0));
		ani_run_up.AddBitmap(CHARACTER_RUN_UP_02, RGB(50, 255, 0));
		ani_run_up.AddBitmap(CHARACTER_RUN_UP_03, RGB(50, 255, 0));
		ani_run_up.AddBitmap(CHARACTER_RUN_UP_04, RGB(50, 255, 0));
		ani_run_up.AddBitmap(CHARACTER_RUN_UP_05, RGB(50, 255, 0));

		ani_run_left.AddBitmap(CHARACTER_RUN_LEFT_01, RGB(50, 255, 0));
		ani_run_left.AddBitmap(CHARACTER_RUN_LEFT_02, RGB(50, 255, 0));
		ani_run_left.AddBitmap(CHARACTER_RUN_LEFT_03, RGB(50, 255, 0));
		ani_run_left.AddBitmap(CHARACTER_RUN_LEFT_03, RGB(50, 255, 0));

		ani_run_right.AddBitmap(CHARACTER_RUN_RIGHT_01, RGB(50, 255, 0));
		ani_run_right.AddBitmap(CHARACTER_RUN_RIGHT_02, RGB(50, 255, 0));
		ani_run_right.AddBitmap(CHARACTER_RUN_RIGHT_03, RGB(50, 255, 0));
		ani_run_right.AddBitmap(CHARACTER_RUN_RIGHT_03, RGB(50, 255, 0));

		ani_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_dash_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_dash_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_dash_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_dash_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_run_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_run_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_run_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_run_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);

	}

	void Character::OnMove(GameMap *map)
	{	
		map->GetCharacterStatus();

		if (!dash_lock)
		{
			_horizontal = 0;
			_vertical = 0;
		}

		//初始移動系數
		if (isDash)
		{
			SLASH_PIXEL = 14;
			STR_PIXEL = 20;
		}
		else if (isRunning)
		{
			SLASH_PIXEL = 7;
			STR_PIXEL = 10;
		}
		else
		{
			SLASH_PIXEL = 5;
			STR_PIXEL = 6;
		}

		//計算移動距離
		if (isSlash() && !dash_lock) //如果斜走
		{
			if (isMovingDown)
			{
				if (_vertical < SLASH_PIXEL)
					_vertical += SLASH_PIXEL;
			}
			if (isMovingUp)
			{
				if (_vertical > -SLASH_PIXEL)
					_vertical -= SLASH_PIXEL;
			}
			if (isMovingRight)
			{
				if (_horizontal < SLASH_PIXEL)
					_horizontal += SLASH_PIXEL;
			}
			if (isMovingLeft)
			{
				if (_horizontal > -SLASH_PIXEL)
					_horizontal -= SLASH_PIXEL;
			}
		}
		else if(!dash_lock)
		{
			if (isMovingDown)
			{
				if (_vertical < STR_PIXEL)
					_vertical += STR_PIXEL;
			}
			if (isMovingUp)
			{
				if (_vertical > -STR_PIXEL)
					_vertical -= STR_PIXEL;
			}
			if (isMovingRight)
			{
				if (_horizontal < STR_PIXEL)
					_horizontal += STR_PIXEL;
			}
			if (isMovingLeft)
			{
				if (_horizontal > -STR_PIXEL)
					_horizontal -= STR_PIXEL;
			}
		}

		
		//判斷方向
		if (_horizontal != 0 && !dash_lock)
		{
			if (_horizontal < 0)
				_directionFlag = 1;	//左
			else
				_directionFlag = 0;	//右
		}
		else if (!dash_lock)
		{
			if (_vertical < 0)
				_directionFlag = 3;	//上
			else if (_vertical > 0)
				_directionFlag = 2;	//下
		}

		//維持上一格狀態的方向

		if (dash_delay_counter < DASH_DELAY && dash_delay_counter > 0)
			dash_delay_counter--;
		else
			dash_delay_counter = DASH_DELAY;

		//動畫
		if (isDash)
		{
			run_counter = 45;
			if (isMoving() && isSlash()) //在斜向移動時按空白鍵，朝移動方向滑動
			{
				if (isMovingDown)
				{
					ani_dash_down.OnMove();
					dash_lock ? NULL : _directionFlag = 2;		//Dash中不能改方向
				}
				else
				{
					ani_dash_up.OnMove();
					dash_lock ? NULL : _directionFlag = 3;
				}
			}
			else		//停止移動時按空白鍵，朝面相方向滑動(沒有斜向)；或是非斜向移動時		
			{
				switch (_directionFlag)
				{
				case 0:
					_horizontal = STR_PIXEL;
					ani_dash_right.OnMove();
					break;
				case 1:
					_horizontal = -STR_PIXEL;
					ani_dash_left.OnMove();
					break;
				case 2:
					_vertical = STR_PIXEL;
					ani_dash_down.OnMove();
					break;
				case 3:
					_vertical = -STR_PIXEL;
					ani_dash_up.OnMove();
					break;
				}
			}

			dash_lock = true;

			if ((ani_dash_right.IsFinalBitmap() || ani_dash_left.IsFinalBitmap()
				|| ani_dash_down.IsFinalBitmap() || ani_dash_up.IsFinalBitmap()))
			{
				dash_lock = false;
				isDash = false;
				ani_dash_right.Reset();
				ani_dash_left.Reset();
				ani_dash_down.Reset();
				ani_dash_up.Reset();
			}
		
		}
		else if (isMoving())   //走動
		{
			if(run_counter>=0)
				run_counter--;		
			if (run_counter < 0)
				isRunning = true;

			switch (_directionFlag)
			{
			case 0:
				ani_right.OnMove();
				break;
			case 1:
				ani_left.OnMove();
				break;
			case 2:
				ani_down.OnMove();
				break;
			case 3:
				ani_up.OnMove();
				break;
			}
		}
		else    //站著不動
		{
			isRunning = false;
			run_counter = 45;
			ani_run_right.Reset();
			ani_run_left.Reset();
			ani_run_down.Reset();
			ani_run_up.Reset();
		}


		if (isRunning)			//跑步氣流動畫
		{
			switch (_directionFlag)
			{
			case 0:
				if (!ani_run_right.IsFinalBitmap())
					ani_run_right.OnMove();
				break;
			case 1:
				if (!ani_run_left.IsFinalBitmap())
					ani_run_left.OnMove();
				break;
			case 2:
				if (!ani_run_down.IsFinalBitmap())
					ani_run_down.OnMove();
				break;
			case 3:
				if (!ani_run_up.IsFinalBitmap())
					ani_run_up.OnMove();
				break;
			}
		}
		else
		{
			ani_run_right.Reset();
			ani_run_left.Reset();
			ani_run_down.Reset();
			ani_run_up.Reset();
		}

		map->SetCharacterXY(_horizontal, _vertical);	//更新角色在map的位置
	}

	void Character::Dash() 
	{
		isDash = true;
		isRunning = false;
		dash_delay_counter--;
	}

	void Character::OnShow() 
	{	
		if (isDash) 
		{
			switch (_directionFlag)
			{
			case 0:
				ani_dash_right.OnShow();
				break;
			case 1:
				ani_dash_left.OnShow();
				break;
			case 2:
				ani_dash_down.OnShow();
				break;
			case 3:
				ani_dash_up.OnShow();
				break;
			}

		}
		else
		{
			if (isRunning && !ani_run_right.IsFinalBitmap() && !ani_run_left.IsFinalBitmap()
				&& !ani_run_down.IsFinalBitmap() && !ani_run_up.IsFinalBitmap())
			{
				switch (_directionFlag)
				{
				case 0:
					ani_run_right.OnShow();
					break;
				case 1:
					ani_run_left.OnShow();
					break;
				case 2:
					ani_run_down.OnShow();
					break;
				case 3:
					ani_run_up.OnShow();
					break;
				}
			}

			if (_horizontal != 0 || _vertical != 0) {
				switch (_directionFlag)
				{
				case 0:
					ani_right.OnShow();
					break;
				case 1:
					ani_left.OnShow();
					break;
				case 2:
					ani_down.OnShow();
					break;
				case 3:
					ani_up.OnShow();
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
					bm_stand_right.ShowBitmap();
					break;
				case 1:
					bm_stand_left.ShowBitmap();
					break;
				case 2:
					bm_stand_down.ShowBitmap();
					break;
				case 3:
					bm_stand_up.ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
		

	}

	void Character::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Character::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Character::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	bool Character::isSlash()
	{
		if (isMovingRight != isMovingLeft)
			if (isMovingUp != isMovingDown)
				return true;

		return false;
	}

	bool Character::isMoving()
	{
		if (isMovingDown || isMovingLeft || isMovingRight || isMovingUp)
			return true;

		return false;
	}

	bool Character::CanDash()
	{
		if (dash_delay_counter == DASH_DELAY)
			return true;

		return false;
	}

}