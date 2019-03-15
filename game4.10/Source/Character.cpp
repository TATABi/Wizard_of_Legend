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
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;	
		_horizontal = 0;
		_vertical = 0;
		_directionFlag = 2; //���V�U
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

		bm_stand_down.LoadBitmap(CHARACTER_STAND_DOWN, RGB(50, 255, 0));
		bm_stand_up.LoadBitmap(CHARACTER_STAND_UP, RGB(50, 255, 0));
		bm_stand_left.LoadBitmap(CHARACTER_STAND_LEFT, RGB(50, 255, 0));
		bm_stand_right.LoadBitmap(CHARACTER_STAND_RIGHT, RGB(50, 255, 0));

		ani_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		ani_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_down.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_up.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_left.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);
		bm_stand_right.SetTopLeft(CHARACTER_SCREEN_X, CHARACTER_SCREEN_Y);

	}

	void Character::OnMove(GameMap *map)
	{
		int sx = map->GetScreenX();
		int sy = map->GetScreenY();
		_horizontal = 0;
		_vertical = 0;
		if (isRunning)	//�O�_���]�B
		{
			STR_PIXEL = 7;
			SLASH_PIXEL = 5;
		}
		else
		{
			STR_PIXEL = 3;
			SLASH_PIXEL = 2;
		}

		if (isSlash())	//�O�_���ר�
		{
			if (isMovingUp)		//�V�W
			{
				if (map->IsEmpty(_cx, _cy - SLASH_PIXEL))			//�e�i��V�S����ê
				{
					_cy -= SLASH_PIXEL;
					_vertical -= SLASH_PIXEL;
				}
			}

			if (isMovingDown)	//�V�U
			{
				if (map->IsEmpty(_cx, _cy + SLASH_PIXEL))			//�e�i��V�S����ê
				{
					_cy += SLASH_PIXEL;
					_vertical += SLASH_PIXEL;
				}
			}
			if (isMovingLeft)	//�V��
			{
				if (map->IsEmpty(_cx - SLASH_PIXEL, _cy))			//�e�i��V�S����ê
				{
					_cx -= SLASH_PIXEL;
					_horizontal -= SLASH_PIXEL;
				}
			}
			if (isMovingRight)	//�V�k
			{
				if (map->IsEmpty(_cx + SLASH_PIXEL, _cy))			//�e�i��V�S����ê
				{
					_cx += SLASH_PIXEL;
					_horizontal += SLASH_PIXEL;
				}
			}
		}
		else
		{
			if (isMovingUp)		//�V�W
			{
				if (map->IsEmpty(_cx, _cy - STR_PIXEL))			//�e�i��V�S����ê
				{
					_cy -= STR_PIXEL;
					_vertical -= STR_PIXEL;
				}
			}

			if (isMovingDown)	//�V�U
			{
				if (map->IsEmpty(_cx, _cy + STR_PIXEL))			//�e�i��V�S����ê
				{
					_cy += STR_PIXEL;
					_vertical += STR_PIXEL;
				}
			}
			if (isMovingLeft)	//�V��
			{
				{
					_cx -= STR_PIXEL;
					_horizontal -= STR_PIXEL;
				}
			}
			if (isMovingRight)	//�V�k
			{
				if (map->IsEmpty(_cx + STR_PIXEL, _cy))			//�e�i��V�S����ê
				{
					_cx += STR_PIXEL;
					_horizontal += STR_PIXEL;
				}
			}
		}
		map->SetScreenPosition(sx + _horizontal, sy + _vertical);		//�վ�e��

																		//���ۤ�V
		if (_horizontal != 0)
		{
			if (_horizontal < 0)
			{
				_directionFlag = 1;	//��
				ani_left.OnMove();
			}
			else
			{
				_directionFlag = 0;	//�k
				ani_right.OnMove();
			}
		}
		else
		{
			if (_vertical < 0)
			{
				_directionFlag = 3;	//�W
				ani_up.OnMove();
			}
			else if (_vertical > 0)
			{
				_directionFlag = 2;	//�U
				ani_down.OnMove();
			}
		}
	}

	
	//�����ŦX�A�����e�@�Ӫ��A����V

	void Character::Dash() 
	{
		switch (_directionFlag)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}

	void Character::OnShow() 
	{
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
		{
			if (isMovingUp != isMovingDown)
				return true;
		}
		return false;
	}

	bool Character::isMoving()
	{
		if (isMovingDown || isMovingLeft || isMovingRight || isMovingUp)
		{
			return true;
		}
		return false;
	}

	void Character::SetRunning(bool runningFlag)
	{

		isRunning = runningFlag;
	}

	void Character::SetCharacterXY(int x, int y)
	{
		_cx = x;
		_cy = y;
	}
}