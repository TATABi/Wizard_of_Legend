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
		_ani_offense.SetDelayCount(2);
		_ani_defense.SetDelayCount(2);
		_ani_misc.SetDelayCount(2);
		_category_flag = 0;
		_item_flag_x = 0;
		_item_flag_y = 0;
		_isOpened = _isOpendOffense = _isOpendDefense = _isOpendMisc = false;
		_choose_flag = 0;
	}

	void Box::LoadBitmap()
	{	
		int m1[5] = { BOX_OFFENSE_01,BOX_OFFENSE_02,BOX_OFFENSE_03,BOX_OFFENSE_04,BOX_OFFENSE_05 };
		for (int i = 0; i < 5; i++)
			_ani_offense.AddBitmap(m1[i], RGB(50, 255, 0));

		int m2[5] = { BOX_DEFENSE_01,BOX_DEFENSE_02,BOX_DEFENSE_03,BOX_DEFENSE_04,BOX_DEFENSE_05 };
		for (int i = 0; i < 5; i++)
			_ani_defense.AddBitmap(m2[i], RGB(50, 255, 0));

		int m3[5] = { BOX_MISC_01,BOX_MISC_02,BOX_MISC_03,BOX_MISC_04,BOX_MISC_05 };
		for (int i = 0; i < 5; i++)
			_ani_misc.AddBitmap(m3[i], RGB(50, 255, 0));

		_bm_board.LoadBitmap(BOX_BOARD, RGB(50, 255, 0));
		_bm_item_board.LoadBitmap(BOX_ITEM_BOARD, RGB(50, 255, 0));
		_bm_cursor.LoadBitmap(BOX_CURSOR, RGB(50, 255, 0));
		_bm_equip_board.LoadBitmap(BOX_EQUIP_BOARD, RGB(50, 255, 0));
		_bm_offense_text.LoadBitmap(BOX_TEXT_OFFENSE, RGB(50, 255, 0));
		_bm_defense_text.LoadBitmap(BOX_TEXT_DEFENSE, RGB(50, 255, 0));
		_bm_misc_text.LoadBitmap(BOX_TEXT_MISC, RGB(50, 255, 0));
		_bm_unknown_item.LoadBitmap(ITEM_UNKNOWN, RGB(50, 255, 0));
		_bm_item_description_board.LoadBitmap(BOX_ITEM_DESCRIPTION_BOARD, RGB(50, 255, 0));
		SetXY();
	}

	void Box::SetXY()
	{
		_bm_board.SetTopLeft(50, 70);
		_bm_equip_board.SetTopLeft(45, 300);
		_bm_item_board.SetTopLeft(50, 70);
		_bm_offense_text.SetTopLeft(70, 95);
		_bm_defense_text.SetTopLeft(70, 95);
		_bm_misc_text.SetTopLeft(70, 95);
		_bm_cursor.SetTopLeft(75, 133);
		_bm_item_description_board.SetTopLeft(50, 320);
		_ani_offense.SetTopLeft(50, 70);
		_ani_defense.SetTopLeft(50, 70);
		_ani_misc.SetTopLeft(50, 70);
	}

	void Box::OnMove()
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)		//開第二層
		{
			_bm_cursor.SetTopLeft(75 + _item_flag_x * _ITEM_X, 133 + _item_flag_y * _ITEM_Y);

			if (_isOpendOffense)
			{
				if ((_item_flag_x == 0 || _item_flag_x == 1) && _item_flag_y == 0)
				{
					chosed_item = Items::Instance().GetItem(_item_flag_x + 1);
					chosed_item->OwnedItem() ? NULL : chosed_item = nullptr;
				}
				else
					chosed_item = nullptr;
			}
			else if (_isOpendDefense)
			{
				if ((_item_flag_x == 0 || _item_flag_x == 1 || _item_flag_x == 2) && _item_flag_y == 0)
				{
					chosed_item = Items::Instance().GetItem(_item_flag_x + 3);
					chosed_item->OwnedItem() ? NULL : chosed_item = nullptr;
				}
				else
					chosed_item = nullptr;
			}
			else if (_isOpendMisc)
			{
				if ((_item_flag_x == 0 || _item_flag_x == 1) && _item_flag_y == 0)
				{
					chosed_item = Items::Instance().GetItem(_item_flag_x + 6);
					chosed_item->OwnedItem() ? NULL : chosed_item = nullptr;
				}
				else
					chosed_item = nullptr;
			}
		}
		else if (_isOpened)											//開第一層
		{
			equiped_item = Items::Instance().GetEquipAndOwnedItem();

			switch (_category_flag)
			{
			case 0:
				if (!_ani_offense.IsFinalBitmap())
					_ani_offense.OnMove();
				break;
			case 1:
				if (!_ani_defense.IsFinalBitmap())
					_ani_defense.OnMove();
				break;
			case 2:
				if (!_ani_misc.IsFinalBitmap())
					_ani_misc.OnMove();
				break;
			default:
				break;
			}
		}
	}
	
	void Box::OnShow(Items *items)
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)
		{
			_bm_item_board.ShowBitmap();
			int row = 0, col = 0;
			switch (_category_flag)
			{
			case 0:
				_bm_offense_text.ShowBitmap();
				
				for (int i = 0; i < items->GetAllItem().size(); i++)
				{
					if (items->GetAllItem()[i]->GetType() == "OFFENSE")
					{
						if (row == 6) 
						{
							row = 0;
							col++;
						}

						if (items->GetAllItem()[i]->OwnedItem())
						{
							items->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							items->GetAllItem()[i]->OnShow();
							row++;
						}
						else
						{
							_bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							_bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;

			case 1:
				_bm_defense_text.ShowBitmap();

				for (int i = 0; i < items->GetAllItem().size(); i++)
				{
					if (items->GetAllItem()[i]->GetType() == "DEFENSE")
					{
						if (row == 6) 
						{
							row = 0;
							col++;
						}

						if (items->GetAllItem()[i]->OwnedItem())
						{
							items->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							items->GetAllItem()[i]->OnShow();
							row++;
						}
						else 
						{
							_bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							_bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;

			case 2:
				_bm_misc_text.ShowBitmap();

				for (int i = 0; i < items->GetAllItem().size(); i++)
				{
					if (items->GetAllItem()[i]->GetType() == "MISC")
					{
						if (row == 6) 
						{
							row = 0;
							col++;
						}

						if (items->GetAllItem()[i]->OwnedItem())
						{
							items->GetAllItem()[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							items->GetAllItem()[i]->OnShow();
							row++;
						}
						else 
{
							_bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							_bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				break;
			}
			
			_bm_item_description_board.ShowBitmap();
			_bm_cursor.ShowBitmap();
			
			if (chosed_item != nullptr)
				chosed_item->ShowInfo(60, 330);
		}
		else if (_isOpened)
		{
			_bm_board.ShowBitmap();
			_ani_offense.OnShow();
			_ani_defense.OnShow();
			_ani_misc.OnShow();
			_bm_equip_board.ShowBitmap();
			
			if (equiped_item != nullptr) {
				equiped_item->SetXY(60, 310);
				equiped_item->OnShow();
			}
		}
	}

	void Box::Down()
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)
		{
			if (_item_flag_y < 3)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				_item_flag_y++;
			}
		}
		else if (_category_flag < 2 && _isOpened)
		{
			CAudio::Instance()->Play(AUDIO_PULL2, false);
			_category_flag++;
			_ani_offense.Reset();
			_ani_defense.Reset();
			_ani_misc.Reset();
		}
	}
	void Box::Up()
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)
		{
			if (_item_flag_y > 0)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				_item_flag_y--;
			}
		}
		else if (_category_flag > 0 && _isOpened)
		{
			CAudio::Instance()->Play(AUDIO_PULL2, false);
			_category_flag--;
			_ani_offense.Reset();
			_ani_defense.Reset();
			_ani_misc.Reset();
		}
	}

	void Box::Left()
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)
		{
			if (_item_flag_x > 0)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				_item_flag_x--;
			}
		}
	}

	void Box::Right()
	{
		if (_isOpendOffense || _isOpendDefense || _isOpendMisc)
		{
			if (_item_flag_x < 5)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				_item_flag_x++;
			}
		}
	}

	void Box::Open(bool openBox)
	{
		_isOpened = openBox;
		if (!openBox)
		{
			_ani_offense.Reset();
			_ani_defense.Reset();
			_ani_misc.Reset();
			_category_flag =0;
		}

	}

	void Box::OpenOpen(bool openopenBox)
	{
		if (!openopenBox)
		{
			CAudio::Instance()->Play(AUDIO_PULL, false);
			_isOpendOffense = false;
			_isOpendDefense = false;
			_isOpendMisc = false;
			_item_flag_x = 0;
			_item_flag_y = 0;
		}
		else
		{
			switch (_category_flag)
			{
			case 0:
				_isOpendOffense = true;
				break;
			case 1:
				_isOpendDefense = true;
				break;
			case 2:
				_isOpendMisc = true;
				break;
			}
		}
	}

	bool Box::Equip(Items *items)
	{
		int item_num;
		_NUMBER_OF_OFFENSE = items->GetNumberOfItem("OFFENSE");
		_NUMBER_OF_DEFENSE = items->GetNumberOfItem("DEFENSE");
		_NUMBER_OF_MISC = items->GetNumberOfItem("MISC");

		if (_isOpendOffense) {
			item_num = _item_flag_x + _item_flag_y * 6;
			if (item_num >= _NUMBER_OF_OFFENSE)
			{
				CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				return false;
			}
			if (items->GetAllItem()[item_num]->OwnedItem())
			{
				items->UnloadAllItem();
				items->GetAllItem()[item_num]->Equip(true);
				equiped_item = items->GetAllItem()[item_num];
				return true;
			}
		}
		else if (_isOpendDefense) {
			item_num = _item_flag_x + _item_flag_y * 6 + _NUMBER_OF_OFFENSE;
			if (item_num >= _NUMBER_OF_OFFENSE + _NUMBER_OF_DEFENSE)
			{
				CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				return false;
			}
			if (items->GetAllItem()[item_num]->OwnedItem())
			{
				items->UnloadAllItem();
				items->GetAllItem()[item_num]->Equip(true);
				equiped_item = items->GetAllItem()[item_num];
				return true;
			}
		}
		else if (_isOpendMisc) {
			item_num = _item_flag_x + _item_flag_y * 6 + _NUMBER_OF_OFFENSE + _NUMBER_OF_DEFENSE;
			if (item_num >= _NUMBER_OF_OFFENSE + _NUMBER_OF_DEFENSE + _NUMBER_OF_MISC)
			{
				CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				return false;
			}
			if (items->GetAllItem()[item_num]->OwnedItem())
			{
				items->UnloadAllItem();
				items->GetAllItem()[item_num]->Equip(true);
				equiped_item = items->GetAllItem()[item_num];
				return true;
			}
		}
		CAudio::Instance()->Play(AUDIO_NOMONEY, false);
		return false;
	}
}