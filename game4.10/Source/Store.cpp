#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Store.h"
#include "GameData.h"
#include "CharacterData.h"
#include <random>

namespace game_framework 
{
	Store::Store(int x, int y)
	{
		Initialize(x, y);
	}

	void Store::Initialize(int x, int y)
	{
		_isItemSoldOut[0] = true;
		_isItemSoldOut[1] = true;
		_isItemSoldOut[2] = true;
		_x = x;
		_y = y;
	}

	void Store::LoadBitmap()
	{
		_bm_sold_out.LoadBitmap(ITEM_SOLD_OUT, RGB(50, 255, 0));
	}

	bool Store::Buy(int number)
	{
		Items* gitem = &Items::Instance();
		std::random_device rd;
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

		if (!_isItemSoldOut[num])
		{
			if (_store_item[num]->BuyItem())
			{
				int r;

				if (gitem->GetItemInStore().size() > 2) {
					r = rd() % gitem->GetItemInStore().size();

					while (_store_item[item_1]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber() || _store_item[item_2]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber())
						r = rd() % gitem->GetItemInStore().size();

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

		return false;
	}

	void Store::Shelf()
	{
		Items* gitem = &Items::Instance();
		vector<Item*> unwoned_items = gitem->GetItemInStore();
		int num_of_item = unwoned_items.size();
		_store_item.clear();
		_isItemSoldOut[0] = true;
		_isItemSoldOut[1] = true;
		_isItemSoldOut[2] = true;
		std::random_device rd;
		for (int i = 0; (i < 3 && i < num_of_item); i++)
		{
			int r = rd() % num_of_item;

			for (int j = 0; j < i; j++)
			{
				if (_store_item[j]->GetNumber() == unwoned_items[r]->GetNumber())
				{
					r = rd() % num_of_item;
					j = -1;
				}
			}
			_store_item.push_back(unwoned_items[r]);
 			_isItemSoldOut[i] = false;
		}
	}

	void Store::OnMove(float *cxy)
	{
		_isItemSoldOut[0] ? NULL : _store_item[0]->SetXY(CHARACTER_SCREEN_X + TOWN_STORE_ITEM[0] - cxy[0], CHARACTER_SCREEN_Y + TOWN_STORE_ITEM[1] - cxy[1]);
		_isItemSoldOut[1] ? NULL : _store_item[1]->SetXY(CHARACTER_SCREEN_X + TOWN_STORE_ITEM[0] + DX - cxy[0], CHARACTER_SCREEN_Y + TOWN_STORE_ITEM[1] - cxy[1]);
		_isItemSoldOut[2] ? NULL : _store_item[2]->SetXY(CHARACTER_SCREEN_X + TOWN_STORE_ITEM[0]  + 2 * DX - cxy[0], CHARACTER_SCREEN_Y + TOWN_STORE_ITEM[1] - cxy[1]);
		_cx = int(cxy[0]);
		_cy = int(cxy[1]);
	}

	void Store::OnShow()
	{
		if (_isItemSoldOut[0])
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
		else
			_store_item[0]->OnShow();

		if (_isItemSoldOut[1])
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x + DX - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
		else
			_store_item[1]->OnShow();

		if (_isItemSoldOut[2])
		{
			_bm_sold_out.SetTopLeft(CHARACTER_SCREEN_X + _x + DX * 2 - _cx, CHARACTER_SCREEN_Y + _y - _cy);
			_bm_sold_out.ShowBitmap();
		}
		else
			_store_item[2]->OnShow();
	}
}

