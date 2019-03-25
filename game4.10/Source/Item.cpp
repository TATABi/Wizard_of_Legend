#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"

/*
namespace game_framework {
	
	Item::Item(int bm, int money, void *Effect()) 
	{
		Initialize();
		bm_item.LoadBitmap(bm, RGB(50, 255, 0));
		(*this).money = money;
		fptr = Effect;
	}

	void Item::Initialize()
	{
		isEquiped = false;
		isReady = false;
		isLuanched = false;
	}

	
	void Item::OnMove() 
	{
		Effect();
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

	void Item::MeetCondition()
	{
		if (isEquiped && !isLuanched)		//發動
		{
			// do something if
			Effect();
			isLuanched = true;
		} 
		else if(!isEquiped)
		{
			//do something		//解除
		
			isLuanched = false;
		}
	}
	
	void Item::Effect()
	{
		
		if (isEquiped && isReady && !isLuanched)	//裝備 &達成條件 &還未發動
		{
			// do something
			isLuanched = true;
		}
		
	}
	

	bool Item::HaveItem() 
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
}
*/