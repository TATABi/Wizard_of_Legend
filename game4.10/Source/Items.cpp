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

	Items::~Items()
	{

		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			delete *iter;
		
	}

	void Items::Initialize()
	{
		
		items.push_back(new Item(ITEM_OFFENSE_01, "OFFENSE", 1, 15, []() {CharacterData::Attack_Coefficient += 0.1; return true; }));	//分裂的護身符
		items.push_back(new Item(ITEM_OFFENSE_02, "OFFENSE", 2, 15, []() {if (CharacterData::HP < CharacterData::Max_HP * 1 / 3) { CharacterData::Attack_Coefficient += 0.2; return true; } else return false; }));	//狂怒頭盔

		items.push_back(new Item(ITEM_DEFENSE_01, "DEFENSE", 3, 15, []() {CharacterData::Max_HP = (int)(CharacterData::Max_HP * 1.5); return true; }));	//巨人之心
		items.push_back(new Item(ITEM_DEFENSE_02, "DEFENSE", 4, 15, []() {CharacterData::Blood_Suck_Constant = 1; return true; })); //吸血鬼眼鏡
		items.push_back(new Item(ITEM_DEFENSE_03, "DEFENSE", 5, 15, []() {CharacterData::Move_Coefficient = 1.5; return true; }));	//水銀的便鞋

		items.push_back(new Item(ITEM_MISC_01, "MISC", 6, 15, []() {CharacterData::CD_Coefficient -= 0.1; return true; }));	//羅素的鐘擺
		items.push_back(new Item(ITEM_MISC_02, "MISC", 7, 15, []() {CharacterData::CD_Coefficient -= 0.25; CharacterData::MP_Charge_Constant += 2; return true; }));	//托茲的懷表



	}

	void Items::LoadBitmap()
	{
		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			(*iter)->LoadBitmap();

	}

	void Items::Effect()		
	{
		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			(*iter)->Effect();
	}

	
	bool Items::Buy(int Item_number)
	{
		if (items[Item_number-1]->BuyItem())
			return true;
		else
			return false;
	}
	
	
	void Items::Equip(int Item_number, bool isEquip)
	{
		items[Item_number-1]->Equip(isEquip);
	}

	vector<Item*> Items::GetItemInBag()
	{
		temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = items.begin(); iter != items.end(); iter++)
		{
			if((*iter)->IsEquiped())
				temp_items.push_back((*iter));
		}

		return temp_items;
	}
	
	vector<Item*> Items::GetAllItem()
	{
		temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = items.begin(); iter != items.end(); iter++)
		{
			temp_items.push_back((*iter));
		}

		return temp_items;
	}

	vector<Item*> Items::GetItemInStore()
	{
		temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = items.begin(); iter != items.end(); iter++)
		{
			if (!((*iter)->HaveItem()))
				temp_items.push_back((*iter));
		}

		return temp_items;
	}
}

