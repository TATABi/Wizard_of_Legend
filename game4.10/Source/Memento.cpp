#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Memento.h"
#include "Global_Class.h"
#include "CharacterData.h"

namespace game_framework
{
	Memento::Memento(const string state, int diamond, int equip_item, bool owned_items[7])
	{
		_state = state;
		_diamond = diamond;
		_equip_item = equip_item;

		for (int i = 0; i < 7; i++)
			_owned_items[i] = owned_items[i];
	}

	Originator::Originator(const string state, int diamond, int equip_item, bool owned_items[7])
	{
		_memento = new Memento(state, diamond, equip_item, owned_items);
	}

	Originator::~Originator()
	{
		delete _memento;
	}

	void Originator::RestoreToMemento(Memento *memento)
	{
		_memento = memento;
	}

	Memento* Originator::CreateMemento()
	{
		return _memento;
	}

	void Originator::SetRecord()
	{
		Global_Class::g_items.SetItems(_memento->_owned_items);
		Global_Class::g_items.Equip(_memento->_equip_item, true);
		CharacterData::Instance()->SetDiamond(_memento->_diamond);
	}

	Caretaker::Caretaker() {}

	void Caretaker::Save(Memento* memento)
	{
		_memento = memento;
	}

	Memento* Caretaker::Load()
	{
		return _memento;
	}

}