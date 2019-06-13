#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Item.h"
#include "CharacterData.h"

namespace game_framework {
	
	Item::Item(int bm, int bm_info, string type, enum ITEM_NUMBER number,int diamond, bool (*effect)(), void (*strip)())
	{
		Initialize();
		_pic = bm;
		_info_pic = bm_info;
		_type = type;
		_number = number;
		_diamond = diamond;
		_Launched = effect;
		_Stripping = strip;
	}
	
	void Item::Initialize()
	{
		_isEquiped = false; 
		_isLuanched = false;
		_isOwned = false;
	}

	void Item::LoadBitmap()
	{
		_bm_item.LoadBitmap(_pic, RGB(50, 255, 0));
		_bm_info.LoadBitmap(_info_pic, RGB(50, 255, 0));
	}

	void Item::SetXY(int x, int y)
	{
		_bm_item.SetTopLeft(x, y);
	}
	
	void Item::OnShow()
	{
		_bm_item.ShowBitmap();
	}

	void Item::Equip(bool equip)
	{
		if (_isOwned)
		{
			_isEquiped = equip;

			if (_isEquiped == false && _isLuanched)
			{
				_isLuanched = false;
				_Stripping();
			}
		}
	}

	bool Item::IsEquiped()
	{
		return _isEquiped;
	}

	void Item::TakeOff()
	{
		_isEquiped = false;
		if (_isEquiped == false && _isLuanched)
		{
			_isLuanched = false;
			_Stripping();
		}
	}

	void Item::Effect()					//�@����
	{
		if (_isEquiped && !_isLuanched)	//�˳� &�٥��o�ʮĪG
			_isLuanched = _Launched();
	}
	
	bool Item::OwnedItem()	//�O�_�֦�Item
	{
		return _isOwned;
	}

	bool Item::BuyItem()
	{
		CharacterData *data = &CharacterData::Instance();
		if (data->DIAMOND() >= _diamond && !_isOwned)
		{
			_isOwned = true;
			data->AddDiamond(-_diamond);
			return true;
		}
		else
			return false;
	}

	string Item::GetType()
	{	
		return _type;
	}

	int Item::GetNumber()
	{
		return _number;
	}

	void Item::SetItem(bool owned)
	{
 		_isOwned = owned;
	}

	void Item::ShowInfo(int x, int y)
	{
		_bm_info.SetTopLeft(x, y);
		_bm_info.ShowBitmap();
	}

	bool Item::BuyAndEquip()
	{
		if (CharacterData::Instance().MONEY() >= _diamond && !_isEquiped)	//�o�̪�_diamond�O�D�����A���O�p��
		{
			CharacterData::Instance().AddMoney(-_diamond);
			_isEquiped = true;												//�˳�
			return true;
		}
		else
			return false;
	}
}
