#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"
#include "Items.h"

namespace game_framework {

	Items::Items() 
	{
		Initialize();
	}

	void Items::Initialize()
	{
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
		items.push_back(new Item(ITEM_UNKNOWN));
	}

	bool Items::Buy(int number)
	{
		if (items[number]->BuyItem())
			return true;
		else
			return false;
	}

}