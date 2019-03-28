#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"


namespace game_framework {
	
	Item::Item(int bm, string type, int number,int money, bool (*effect)()) 
	{
		Initialize();
		bm_number = bm;
		this->type = type;
		this->number = number;
		this->money = money;
		Launched = effect;
		
	}
	
	void Item::Initialize()
	{
		//isEquiped = false;
		isEquiped = true; //test
		isLuanched = false;
		isOwned = true; //test
	}

	void Item::LoadBitmap()
	{
		bm_item.LoadBitmap(bm_number, RGB(50, 255, 0));
	}

	void Item::SetXY(int x, int y)
	{
		bm_item.SetTopLeft(x, y);
	}
	
	void Item::OnShow()
	{
		bm_item.ShowBitmap();
	}

	void Item::Equip(bool equip)
	{
		isEquiped = equip;
	}

	bool Item::IsEquiped()
	{
		return isEquiped;
	}

	void Item::Effect()			//一直做
	{
		if (isEquiped && !isLuanched)	//裝備 &還未發動效果
			isLuanched = Launched();
	}
	
	bool Item::HaveItem()	//是否擁有Item
	{
		return isOwned;
	}

	bool Item::BuyItem()
	{
		if (CharacterData::Money >= money)
		{
			isOwned = true;
			CharacterData::Money -= money;
			return true;
		}
		else
			return false;
	}

	string Item::GetType()
	{	
		return type;
	}
}
