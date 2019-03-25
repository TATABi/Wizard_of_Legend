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

		isequiped = false;
		meet_condition = false;
		have_luanched = false;
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
		isequiped = equip;
	}

	void Item::MeetCondition()
	{
		if (isequiped)
		{
			// do something
			meet_condition = true;
		}

	}

	bool Item:: IsEquiped()
	{
		return isequiped;
	}

	void Item::Effect()
	{
		if (isequiped && meet_condition && !have_luanched)	//裝備 &達成條件 &還未發動
		{
			// do something
			have_luanched = true;
		}

	}

	bool Item::HaveItem() 
	{
		return have_it;
	}

	bool Item::BuyItem()
	{
		if (CharacterData::Money >= money)
		{
			have_it = true;
			CharacterData::Money -= money;
			return true;
		}
		else
			return false;
	}
}