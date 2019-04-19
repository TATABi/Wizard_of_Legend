#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

namespace game_framework {
	Box::Box()
	{
		Initialize();
	}

	void Box::Initialize() 
	{
		ani_offense.SetDelayCount(2);
		ani_defense.SetDelayCount(2);
		ani_misc.SetDelayCount(2);
		category_flag = 0;
		item_flag_x = 0;
		item_flag_y = 0;
		isOpened = isOpendOffense = isOpendDefense = isOpendMisc = false;
		choose_flag = 0;
	}
	void Box::LoadBitmap()
	{	
		bm_board.LoadBitmap(BOX_BOARD, RGB(50, 255, 0));

		int m1[5] = { BOX_OFFENSE_01,BOX_OFFENSE_02,BOX_OFFENSE_03,BOX_OFFENSE_04,BOX_OFFENSE_05 };
		for (int i = 0; i < 5; i++)
			ani_offense.AddBitmap(m1[i], RGB(50, 255, 0));

		int m2[5] = { BOX_DEFENSE_01,BOX_DEFENSE_02,BOX_DEFENSE_03,BOX_DEFENSE_04,BOX_DEFENSE_05 };
		for (int i = 0; i < 5; i++)
			ani_defense.AddBitmap(m2[i], RGB(50, 255, 0));

		int m3[5] = { BOX_MISC_01,BOX_MISC_02,BOX_MISC_03,BOX_MISC_04,BOX_MISC_05 };
		for (int i = 0; i < 5; i++)
			ani_misc.AddBitmap(m3[i], RGB(50, 255, 0));

		bm_item_board.LoadBitmap(BOX_ITEM_BOARD, RGB(50, 255, 0));
		bm_cursor.LoadBitmap(BOX_CURSOR, RGB(50, 255, 0));
		bm_equip_board.LoadBitmap(BOX_EQUIP_BOARD, RGB(50, 255, 0));
		bm_offense_text.LoadBitmap(BOX_TEXT_OFFENSE, RGB(50, 255, 0));
		bm_defense_text.LoadBitmap(BOX_TEXT_DEFENSE, RGB(50, 255, 0));
		bm_misc_text.LoadBitmap(BOX_TEXT_MISC, RGB(50, 255, 0));
		bm_unknown_item.LoadBitmap(ITEM_UNKNOWN, RGB(50, 255, 0));

		bm_board.SetTopLeft(50, 70);
		bm_equip_board.SetTopLeft(45, 300);
		bm_item_board.SetTopLeft(50, 70);
		bm_offense_text.SetTopLeft(70, 95);
		bm_defense_text.SetTopLeft(70, 95);
		bm_misc_text.SetTopLeft(70, 95);
		bm_cursor.SetTopLeft(75,133);

		ani_offense.SetTopLeft(50, 70);
		ani_defense.SetTopLeft(50, 70);
		ani_misc.SetTopLeft(50, 70);

	}

	void Box::OnMove()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)		//開第二層
		{
			bm_cursor.SetTopLeft(75 + item_flag_x * ITEM_X, 133 + item_flag_y * ITEM_Y);
		}
		else if (isOpened)											//開第一層
		{
			switch (category_flag)
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
	
	void Box::OnShow(Items *gitem)
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			bm_item_board.ShowBitmap();
			int row = 0, col = 0;
			switch (category_flag)
			{
			
			case 0:
				bm_offense_text.ShowBitmap();
				
				for (int i = 0; i < gitem->GetAllItem().size(); i++)
				{
					if (gitem->GetAllItem()[i]->GetType() == "OFFENSE")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (gitem->GetAllItem()[i]->HaveItem()) {
							gitem->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							gitem->GetAllItem()[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;
			case 1:
				bm_defense_text.ShowBitmap();

				for (int i = 0; i < gitem->GetAllItem().size(); i++)
				{
					if (gitem->GetAllItem()[i]->GetType() == "DEFENSE")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (gitem->GetAllItem()[i]->HaveItem()) {
							gitem->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							gitem->GetAllItem()[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;

			case 2:
				bm_misc_text.ShowBitmap();

				for (int i = 0; i < gitem->GetAllItem().size(); i++)
				{
					if (gitem->GetAllItem()[i]->GetType() == "MISC")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (gitem->GetAllItem()[i]->HaveItem()) {
							gitem->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							gitem->GetAllItem()[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;
			}

			bm_cursor.ShowBitmap();
		}
		else if (isOpened)
		{
			bm_board.ShowBitmap();
			ani_offense.OnShow();
			ani_defense.OnShow();
			ani_misc.OnShow();
			bm_equip_board.ShowBitmap();
			
			if (temp_item != nullptr) {
				temp_item->SetXY(60, 310);
				temp_item->OnShow();
			}
		}
	}

	void Box::Down()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			if(item_flag_y < 3)
				item_flag_y++;
		}
		else if (category_flag < 2 && isOpened)
		{
			category_flag++;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}
	void Box::Up()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			if (item_flag_y > 0)
				item_flag_y--;
		}
		else if (category_flag > 0 && isOpened)
		{
			category_flag--;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}

	void Box::Left()
	{
		if (item_flag_x > 0)
			item_flag_x--;
	}

	void Box::Right()
	{
	
		
		if (item_flag_x < 5 )
			item_flag_x++;
		

		
	}

	void Box::Open(bool openBox)
	{
		isOpened = openBox;
		if (!openBox)
		{
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
			category_flag =0;
		}

	}

	void Box::OpenOpen(bool openopenBox)
	{
		if (!openopenBox)
		{
			isOpendOffense = false;
			isOpendDefense = false;
			isOpendMisc = false;
			item_flag_x = 0;
			item_flag_y = 0;
		}
		else
		{
			switch (category_flag)
			{
			case 0:
				isOpendOffense = true;
				break;
			case 1:
				isOpendDefense = true;
				break;
			case 2:
				isOpendMisc = true;
				break;
			}
		}
	}

	bool Box::Equip(Items *gitem)
	{
		int item_num;
		NUMBER_OF_OFFENSE = gitem->GetNumberOfItem("OFFENSE");
		NUMBER_OF_DEFENSE = gitem->GetNumberOfItem("DEFENSE");
		NUMBER_OF_MISC = gitem->GetNumberOfItem("MISC");
		

		if (isOpendOffense) {
			item_num = item_flag_x + item_flag_y * 6;
			if (item_num >= NUMBER_OF_OFFENSE)
				return false;
			if (gitem->GetAllItem()[item_num]->HaveItem())
			{
				gitem->UnloadAllItem();
				gitem->GetAllItem()[item_num]->Equip(true);
				temp_item = gitem->GetAllItem()[item_num];
				return true;
			}
		}
		else if (isOpendDefense) {
			item_num = item_flag_x + item_flag_y * 6 + NUMBER_OF_OFFENSE;
			if (item_num >= NUMBER_OF_OFFENSE + NUMBER_OF_DEFENSE)
				return false;
			if (gitem->GetAllItem()[item_num]->HaveItem())
			{
				gitem->UnloadAllItem();
				gitem->GetAllItem()[item_num]->Equip(true);
				temp_item = gitem->GetAllItem()[item_num];
				return true;
			}
		}
		else if (isOpendMisc) {
			item_num = item_flag_x + item_flag_y * 6 + NUMBER_OF_OFFENSE + NUMBER_OF_DEFENSE;
			if (item_num >= NUMBER_OF_OFFENSE + NUMBER_OF_DEFENSE + NUMBER_OF_MISC)
				return false;
			if (gitem->GetAllItem()[item_num]->HaveItem())
			{
				gitem->UnloadAllItem();
				gitem->GetAllItem()[item_num]->Equip(true);
				temp_item = gitem->GetAllItem()[item_num];
				return true;
			}
		}

		return false;

		
	}
}