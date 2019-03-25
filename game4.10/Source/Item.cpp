#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"
#include "CharacterData.h"

namespace game_framework {
	
	Item::Item(int bm) 
	{
		Initialize();
		bm_item.LoadBitmap(bm);
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

	void Item::MeetCondition()
	{
		if (isEquiped)
		{
			// do something
			isReady = true;
		}

	}

	bool Item:: IsEquiped()
	{
		return isEquiped;
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