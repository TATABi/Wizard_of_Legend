#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

namespace game_framework {
	Box::Box() {
		Initialize();
	}

	void Box::Initialize() 
	{
		ani_offense.SetDelayCount(2);
		ani_defense.SetDelayCount(2);
		ani_misc.SetDelayCount(2);
		classification = 0;
		isOpened = false;
	}
	void Box::LoadBitmap()
	{	
		bm_board.LoadBitmap(BOX_BOARD, RGB(50, 255, 0));

		ani_offense.AddBitmap(BOX_OFFENSE_01, RGB(50, 255, 0));
		ani_offense.AddBitmap(BOX_OFFENSE_02, RGB(50, 255, 0));
		ani_offense.AddBitmap(BOX_OFFENSE_03, RGB(50, 255, 0));
		ani_offense.AddBitmap(BOX_OFFENSE_04, RGB(50, 255, 0));
		ani_offense.AddBitmap(BOX_OFFENSE_05, RGB(50, 255, 0));
	
		ani_defense.AddBitmap(BOX_DEFENSE_01, RGB(50, 255, 0));
		ani_defense.AddBitmap(BOX_DEFENSE_02, RGB(50, 255, 0));
		ani_defense.AddBitmap(BOX_DEFENSE_03, RGB(50, 255, 0));
		ani_defense.AddBitmap(BOX_DEFENSE_04, RGB(50, 255, 0));
		ani_defense.AddBitmap(BOX_DEFENSE_05, RGB(50, 255, 0));

		ani_misc.AddBitmap(BOX_MISC_01, RGB(50, 255, 0));
		ani_misc.AddBitmap(BOX_MISC_02, RGB(50, 255, 0));
		ani_misc.AddBitmap(BOX_MISC_03, RGB(50, 255, 0));
		ani_misc.AddBitmap(BOX_MISC_04, RGB(50, 255, 0));
		ani_misc.AddBitmap(BOX_MISC_05, RGB(50, 255, 0));

		bm_board.SetTopLeft(50, 70);
		ani_offense.SetTopLeft(50, 70);
		ani_defense.SetTopLeft(50, 70);
		ani_misc.SetTopLeft(50, 70);
	}

	void Box::OnMove() 
	{
		if (isOpened)
		{
			switch (classification)
			{
			case 0:
				if (!ani_offense.IsFinalBitmap())
					ani_offense.OnMove();
				break;
			case 1:
				if (!ani_defense.IsFinalBitmap())
					ani_defense.OnMove();
				break;
			case 2:
				if (!ani_misc.IsFinalBitmap())
					ani_misc.OnMove();
				break;
			default:
				break;
			}
		}
	}
	
	void Box::OnShow()
	{
		if (isOpened)
		{
			bm_board.ShowBitmap();
			ani_offense.OnShow();
			ani_defense.OnShow();
			ani_misc.OnShow();
		}
	}

	void Box::Next()
	{
		if (classification < 2 && isOpened)
		{
			classification++;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}
	void Box::Previous()
	{
		if (classification > 0 && isOpened)
		{
			classification--;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}

	void Box::Open(bool openBox)
	{
		isOpened = openBox;
		if (!openBox)
		{
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
			classification=0;
		}

	}
}