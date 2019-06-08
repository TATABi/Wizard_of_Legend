#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Items.h"
#include "CharacterData.h"

namespace game_framework {

	Items& Items::Instance()
	{
		static Items instance;
		return instance;
	}

	Items::Items()
	{
		Initialize();
	}

	Items::~Items()
	{
		vector<Item*>::iterator iter;
		for (iter = _items.begin(); iter != _items.end(); iter++)
			delete *iter;
	}

	void Items::Initialize()
	{
		//分裂的護身符
		_items.push_back(new Item(ITEM_OFFENSE_01, ITEM_OFFENSE_01_INFO, "OFFENSE", Amulet, 15,
								[]() {CharacterData::Instance().SetAttackCoefficient(1.1); return true; },
								[]() {CharacterData::Instance().SetAttackCoefficient(-1.1); }));

		//狂怒頭盔
		_items.push_back(new Item(ITEM_OFFENSE_02, ITEM_OFFENSE_02_INFO, "OFFENSE", Helmet, 15,
								[]() {if (CharacterData::Instance().HP() < CharacterData::Instance().MAX_HP() * 1 / 3) { CharacterData::Instance().SetAttackCoefficient(1.2); return true; } else return false; },
								[]() { CharacterData::Instance().SetAttackCoefficient(-1.2); }));

		//巨人之心
		_items.push_back(new Item(ITEM_DEFENSE_01, ITEM_DEFENSE_01_INFO, "DEFENSE", Heart, 15,
								[]() { CharacterData::Instance().AddMaxHP(200); return true; },
								[]() { CharacterData::Instance().AddMaxHP(-200);}));

		//吸血鬼眼鏡
		_items.push_back(new Item(ITEM_DEFENSE_02, ITEM_DEFENSE_02_INFO, "DEFENSE", Glasses, 15,
								[]() {CharacterData::Instance().SetBloodSuckCoefficient(2.0); return true; },
								[]() {CharacterData::Instance().SetBloodSuckCoefficient(-2.0); }));

		//水銀的便鞋
		_items.push_back(new Item(ITEM_DEFENSE_03, ITEM_DEFENSE_03_INFO,"DEFENSE", Shoes, 15,
								[]() {CharacterData::Instance().SetNoveCoefficient(1.5); return true; },
								[]() {CharacterData::Instance().SetNoveCoefficient(-1.5); }));

		//羅素的鐘擺
		_items.push_back(new Item(ITEM_MISC_01, ITEM_MISC_01_INFO, "MISC", Pendulum, 15,
								[]() {CharacterData::Instance().SetCDCoefficient(-2.0); return true; },
								[]() {CharacterData::Instance().SetCDCoefficient(2.0); }));

		//托茲的懷表
		_items.push_back(new Item(ITEM_MISC_02, ITEM_MISC_02_INFO, "MISC", Pocket_Watch, 15,
								[]() {CharacterData::Instance().SetCDCoefficient(-1.5); CharacterData::Instance().CharacterData::SetMPChargeCoefficient(2.0); return true; },
								[]() {CharacterData::Instance().SetCDCoefficient(1.5); CharacterData::Instance().CharacterData::SetMPChargeCoefficient(-2.0);  }));
	}

	void Items::LoadBitmap()
	{
		vector<Item*>::iterator iter;
		for (iter = _items.begin(); iter != _items.end(); iter++)
			(*iter)->LoadBitmap();
	}

	void Items::Effect()
	{
		vector<Item*>::iterator iter;
		for (iter = _items.begin(); iter != _items.end(); iter++)
			(*iter)->Effect();
	}

	bool Items::Buy(int Item_number)
	{
		if (_items[Item_number - 1]->BuyItem())
			return true;
		else
			return false;
	}

	void Items::Equip(int Item_number, bool isEquip)
	{
		_items[Item_number - 1]->Equip(isEquip);
	}

	vector<Item*> Items::GetItemInBag()
	{
		_temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			if ((*iter)->IsEquiped())
				_temp_items.push_back((*iter));
		}
		return _temp_items;
	}

	Item* Items::GetEquipAndOwnedItem()
	{
		Item* item = nullptr;
		vector<Item*>::iterator iter;

		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			if ((*iter)->OwnedItem() && (*iter)->IsEquiped())
			{
				item = *iter;
				break;
			}
		}
		return item;
	}

	vector<Item*> Items::GetAllItem()
	{
		_temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			_temp_items.push_back((*iter));
		}
		return _temp_items;
	}

	vector<Item*> Items::GetItemInStore()
	{
		_temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			if (!((*iter)->OwnedItem()))
				_temp_items.push_back((*iter));
		}
		return _temp_items;
	}

	int Items::GetNumberOfItem(string s)
	{
		if (s == "OFFENSE")
			return NUMBER_OF_OFFENSE;
		else if (s == "DEFENSE")
			return NUMBER_OF_DEFENSE;
		else if (s == "MISC")
			return NUMBER_OF_MISC;
		else
			return false;
	}

	void Items::UnloadAllItem() 
	{
		vector<Item*>::iterator iter;
		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			(*iter)->Equip(false);
		}
	}

	void Items::SetItems(bool items[7])
	{
		for (int i = 0; i < 7; i++)
		{
			_items[i]->SetItem(items[i]);
		}
	}

	vector<bool> Items::GetSaveData()
	{
		vector<bool> owned_items;

		for (int i = 0; i < _items.size(); i++)
		{
			if (_items[i]->OwnedItem())
				owned_items.push_back(true);
			else
				owned_items.push_back(false);
		}
		return owned_items;
	}

	Item* Items::GetItem(int num)
	{
		vector<Item*>::iterator iter;
		for (iter = _items.begin(); iter != _items.end(); iter++)
		{
			if ((*iter)->GetNumber() == num)
				return (*iter);
		}
		return nullptr;
	}
}

