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
		/*
		map<string, Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			delete iter->second;
			*/
		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			delete *iter;
		
	}

	void Items::Initialize()
	{
		/*
		items.insert(pair<string, Item*>("Offense_01", new Item(ITEM_UNKNOWN, "OFFENSE", 15, []() {CharacterData::Attack_Coefficient += 0.1; return true; })));	//�������@����
		items.insert(pair<string, Item*>("Offense_02", new Item(ITEM_UNKNOWN, "OFFENSE", 15, []() {if (CharacterData::HP < CharacterData::Max_HP * 1/3) { CharacterData::Attack_Coefficient += 0.2; return true; } else return false; })));	//�g���Y��

		items.insert(pair<string, Item*>("Defense_01", new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Max_HP = (int)(CharacterData::Max_HP * 1.5); return true; })));	//���H����
		items.insert(pair<string, Item*>("Defense_02", new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Blood_Suck_Constant = 1; return true; }))); //�l�尭����
		items.insert(pair<string, Item*>("Defense_03", new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Move_Coefficient = 1.5; return true; })));	//���Ȫ��K�c
		
		items.insert(pair<string, Item*>("MISC_01", new Item(ITEM_UNKNOWN, "MISC", 15, []() {CharacterData::CD_Coefficient -= 0.1; return true; })));	//ù�������\
		items.insert(pair<string, Item*>("MISC_02", new Item(ITEM_UNKNOWN, "MISC", 15, []() {CharacterData::CD_Coefficient -= 0.25; CharacterData::MP_Charge_Constant += 2; return true; })));	//�������h��
		*/
		
		items.push_back(new Item(ITEM_UNKNOWN, "OFFENSE", 15, []() {CharacterData::Attack_Coefficient += 0.1; return true; }));	//�������@����
		items.push_back(new Item(ITEM_UNKNOWN, "OFFENSE", 15, []() {if (CharacterData::HP < CharacterData::Max_HP * 1 / 3) { CharacterData::Attack_Coefficient += 0.2; return true; } else return false; }));	//�g���Y��

		items.push_back(new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Max_HP = (int)(CharacterData::Max_HP * 1.5); return true; }));	//���H����
		items.push_back(new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Blood_Suck_Constant = 1; return true; })); //�l�尭����
		items.push_back(new Item(ITEM_UNKNOWN, "DEFENSE", 15, []() {CharacterData::Move_Coefficient = 1.5; return true; }));	//���Ȫ��K�c

		items.push_back(new Item(ITEM_UNKNOWN, "MISC", 15, []() {CharacterData::CD_Coefficient -= 0.1; return true; }));	//ù�������\
		items.push_back(new Item(ITEM_UNKNOWN, "MISC", 15, []() {CharacterData::CD_Coefficient -= 0.25; CharacterData::MP_Charge_Constant += 2; return true; }));	//�������h��



	}

	void Items::LoadBitmap()
	{
		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			(*iter)->LoadBitmap();

	}

	void Items::Effect()		//OnMove()������
	{
		vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++)
			(*iter)->Effect();
	}

	/*
	bool Items::Buy(string Item_number)
	{
		if (items[Item_number]->BuyItem())
			return true;
		else
			return false;
	}
	*/
	/*
	void Items::Equip(string Item_number, bool isEquip)
	{
		items[Item_number]->Equip(isEquip);
	}

	*/
	/*
	std::map<std::string, Item*>Items::GetItemInBag()
	{
		temp_items.clear();
		map<string, Item*>::iterator iter;

		for (iter = items.begin(); iter != items.end(); iter++)
		{
			if (iter->second->IsEquiped())
				temp_items.insert(pair<string, Item*>(iter->first, iter->second));
		}

		return temp_items;
	}
	*/
	
	vector<Item*> Items::GetItemInBox()
	{
		temp_items.clear();
		vector<Item*>::iterator iter;

		for (iter = items.begin(); iter != items.end(); iter++)
		{
			temp_items.push_back((*iter));
		}

		return temp_items;
	}

}

