#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"
#include "Items.h"
/*
namespace game_framework {

	Items::Items() 
	{
		Initialize();
	}

	void Items::Initialize()
	{
		//items.insert(pair<string, Item*>("Offense_01", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Offense_02", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Offense_03", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Defense_01", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Defense_02", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Defense_03", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Misc_01", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Misc_02", new Item(ITEM_UNKNOWN)));
		//items.insert(pair<string, Item*>("Misc_03", new Item(ITEM_UNKNOWN)));

		items.insert(pair<string, Item*>("Defense_01", new Item(ITEM_UNKNOWN, 15, Item::&Offense_01_Effect)));
	}

	bool Items::Buy(string Item_number)
	{
		if (items[Item_number]->BuyItem())
			return true;
		else
			return false;
	}

	void Items::Equip(string Item_number, bool isEquip)
	{
		items[Item_number]->Equip(isEquip);
	}

	void Items::MeetCondition()	//一直檢查是否滿足發動條件
	{
		map<string, Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
		{
			(iter->second)->MeetCondition();
		}
	}

	void Items::Offense_01_Effect()
	{
		CharacterData::Max_HP = 550;
	}
}
*/