#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Items.h"

namespace game_framework {

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
		_items.push_back(new Item(ITEM_OFFENSE_01, "OFFENSE", 1, 15, 
								[]() {CharacterData::Attack_Coefficient += 0.1; return true; },
								[]() {CharacterData::Attack_Coefficient -= 0.1; }));	

		//狂怒頭盔
		_items.push_back(new Item(ITEM_OFFENSE_02, "OFFENSE", 2, 15, 
								[]() {if (CharacterData::HP < CharacterData::Max_HP * 1 / 3) { CharacterData::Attack_Coefficient += 0.2; return true; } else return false; },
								[]() {CharacterData::Attack_Coefficient -= 0.2; }));	

		//巨人之心
		_items.push_back(new Item(ITEM_DEFENSE_01, "DEFENSE", 3, 15, 
								[]() {CharacterData::Max_HP = (int)(CharacterData::Max_HP * 1.5); return true; },
								[]() { CharacterData::Max_HP = CharacterData::Max_HP / 1.5; if (CharacterData::Max_HP < CharacterData::HP) { CharacterData::HP = CharacterData::Max_HP; } }));	

		//吸血鬼眼鏡
		_items.push_back(new Item(ITEM_DEFENSE_02, "DEFENSE", 4, 15, 
								[]() {CharacterData::Blood_Suck_Constant += 1; return true; }, 
								[]() {CharacterData::Blood_Suck_Constant -= 1; })); 

		//水銀的便鞋
		_items.push_back(new Item(ITEM_DEFENSE_03, "DEFENSE", 5, 15, 
								[]() {CharacterData::Move_Coefficient = 2; return true; }, 
								[]() {CharacterData::Move_Coefficient = 1; }));	

		//羅素的鐘擺
		_items.push_back(new Item(ITEM_MISC_01, "MISC", 6, 15, 
								[]() {CharacterData::CD_Coefficient -= 0.1; return true; }, 
								[]() {CharacterData::CD_Coefficient += 0.1; }));	

		//托茲的懷表
		_items.push_back(new Item(ITEM_MISC_02, "MISC", 7, 15, 
								[]() {CharacterData::CD_Coefficient -= 0.25; CharacterData::MP_Charge_Constant += 2; return true; }, 
								[]() {CharacterData::CD_Coefficient += 0.25; CharacterData::MP_Charge_Constant -= 2;  }));	


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
			if (!((*iter)->HaveItem()))
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
}

