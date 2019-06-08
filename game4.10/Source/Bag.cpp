#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Bag.h"
#include "Items.h"

namespace game_framework {

	Bag& Bag::Instance()
	{
		static Bag instance;
		return instance;
	}

	Bag::Bag()
	{
		Initialize();
	}

	void Bag::Initialize()
	{
		_isOpened =  false;
	}

	void Bag::LoadBitmap()
	{
		_bm_bag.LoadBitmap(BAG_BOARD, RGB(50, 255, 0));
		_bm_skill1.LoadBitmap(SKILL_ICON_AIR_SPINNER, RGB(50, 255, 0));
		_bm_skill2.LoadBitmap(SKILL_ICON_AIR_BURST, RGB(50, 255, 0));
		_bm_skill3.LoadBitmap(SKILL_ICON_REBOUNDING_ICICLES, RGB(50, 255, 0));
		_bm_skill4.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));
		_bm_item_cursor.LoadBitmap(BAG_ITEM_CURSOR, RGB(50, 255, 0));

		SetTopLeft();
	}

	void Bag::SetTopLeft()
	{
		_bm_bag.SetTopLeft(50, 70);
		_bm_skill1.SetTopLeft(75, 103);
		_bm_skill2.SetTopLeft(100, 103);
		_bm_skill3.SetTopLeft(125, 103);
		_bm_skill4.SetTopLeft(150, 103);
		_bm_item_cursor.SetTopLeft(67, 170);
	}

	void Bag::OnMove()
	{
		//背包開啟，匯入持有道具
		if (_isOpened)
			_items = Items::Instance().GetItemInBag();
	}

	void Bag::OnShow()
	{
		_bm_item_cursor.SetTopLeft(67 + 25 * _flags[0], 170 + _flags[1] * 25);

		int row = 0;
		int col = 0;

		//排列並顯示道具
		if (_isOpened)
		{
			_bm_bag.ShowBitmap();

			for (int i = 0; i < _items.size(); i++)
			{
				if (row == 6) 
				{
					row = 0;
					col++;
				}
				_items[i]->SetXY(67 + 25 * row, 170 + 25 * col);
				_items[i]->OnShow();
				row++;						
			}

			_bm_skill1.ShowBitmap(0.7);
			_bm_skill2.ShowBitmap(0.7);
			_bm_skill3.ShowBitmap(0.7);
			_bm_skill4.ShowBitmap(0.7);
			_bm_item_cursor.ShowBitmap();

			//顯示道具資訊
			if (_flags[0] + _flags[1] * 6 < _items.size())
				_items[_flags[0] + _flags[1] * 6]->ShowInfo(70, 255);
		}
	}

	void Bag::Open(bool isOpened)
	{
		_flags[0] = 0;
		_flags[1] = 0;
		_isOpened = isOpened;
	}

	void Bag::Left() 
	{
		if (_flags[0] > 0 )
			_flags[0]--;
	}

	void Bag::Right()
	{
		if (_flags[0] < 5)
			_flags[0]++;
	}

	void Bag::Up()
	{
		if (_flags[1] > 0)
			_flags[1]--;
	}

	void Bag::Down()
	{
		if (_flags[1] < 1 )
			_flags[1]++;
	}
}