#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"


namespace game_framework {
	
	Item::Item(int bm, string type, int number,int diamond, bool (*effect)(), void (*strip)())
	{
		Initialize();
		bm_number = bm;
		this->type = type;
		this->number = number;
		this->diamond = diamond;
		Launched = effect;
		Stripping = strip;
	}
	
	void Item::Initialize()
	{
		isEquiped = false; 
		isLuanched = false;
		isOwned = false;
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
		if (isOwned)
		{
			isEquiped = equip;

			if (isEquiped == false && isLuanched)
			{
				isLuanched = false;
				Stripping();
				/*
				if (number == 3) {
					CharacterData::Max_HP = 500;
					if (CharacterData::Max_HP < CharacterData::HP)
						CharacterData::HP = CharacterData::Max_HP;
				}
				if (number == 5)
					CharacterData::Move_Coefficient = 1;
				*/
			}
			
		}
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
		if (CharacterData::Diamond >= diamond && !isOwned)
		{
			isOwned = true;
			CharacterData::Diamond -= diamond;
			return true;
		}
		else
			return false;
	}

	string Item::GetType()
	{	
		return type;
	}

	int Item::GetNumber()
	{
		return number;
	}


}
