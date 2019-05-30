#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Store.h"
#include "GameData.h"

namespace game_framework 
{
	Store::Store(int x, int y)
	{
		Initialize(x, y);
	}

	void Store::Initialize(int x, int y)
	{
		_isItemSoldOut[0] = false;
		_isItemSoldOut[1] = false;
		_isItemSoldOut[2] = false;
		_x = x;
		_y = y;
	}

	void Store::LoadBitmap()
	{
		_bm_sold_out.LoadBitmap(ITEM_SOLD_OUT, RGB(50, 255, 0));
	}

	bool Store::Buy(int number, Items *gitem)
	{
		srand((unsigned int)time(NULL));
		int item_1, item_2, num = number;

		switch (num)
		{
		case 0:
			item_1 = 1;
			item_2 = 2;
			break;
		case 1:
			item_1 = 0;
			item_2 = 2;
			break;
		case 2:
			item_1 = 0;
			item_2 = 1;
			break;
		}

		if (_store_item[num]->BuyItem()) 
		{
			int r;

			if (gitem->GetItemInStore().size() > 2) {
				r = rand() % gitem->GetItemInStore().size();

				while (_store_item[item_1]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber() || _store_item[item_2]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber())
					r = rand() % gitem->GetItemInStore().size();

				_store_item.erase(_store_item.begin() + num);
				_store_item.insert(_store_item.begin() + num, gitem->GetItemInStore()[r]);
			}
			else
				_isItemSoldOut[num] = true;

			return true;
		}
		else
			return false;
	}

	void Store::Shelf(Items *gitem)
	{
		if (gitem->GetItemInStore().size() > 0)
		{
			srand((unsigned int)time(NULL));	//�üƺؤl
			_store_item.clear();
			int r;
			for (int i = 0; i < 3; i++) 
			{
				r = rand() % gitem->GetItemInStore().size();

				for (int j = 0; j < i; j++) 
				{
					if (_store_item[j]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber())
					{
						r = rand() % gitem->GetItemInStore().size();
						j = 0;
					}
				}
				_store_item.push_back(gitem->GetItemInStore()[r]);
			}
		}
	}

	void Store::SetXY(float *cxy)
	{
		_store_item[0]->SetXY(285 + 525 - cxy[0], 205 + 990 - cxy[1]);
		_store_item[1]->SetXY(285 + 575 - cxy[0], 205 + 990 - cxy[1]);
		_store_item[2]->SetXY(285 + 620 - cxy[0], 205 + 990 - cxy[1]);
		_cx = int(cxy[0]);
		_cy = int(cxy[1]);
	}

	void Store::OnShow()
	{
		_isItemSoldOut[0] ? NULL : _store_item[0]->OnShow();
		_isItemSoldOut[1] ? NULL : _store_item[1]->OnShow();
		_isItemSoldOut[2] ? NULL : _store_item[2]->OnShow();
		
		if (_store_item[0]->HaveItem()) 
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
		if (_store_item[1]->HaveItem())
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x + DX - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
		if (_store_item[2]->HaveItem())
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x + 2 * DX - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
	}
}

