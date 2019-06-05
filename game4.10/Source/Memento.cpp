#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <fstream>
#include "audio.h"
#include "gamelib.h"
#include "Memento.h"
#include "CharacterData.h"
#include "Items.h"

namespace game_framework
{
/////////////////////////////////////////////////
	//State
	State::State(const string stage, int diamond, int equip_item, bool owned_items[NUM_ITEMS])
	{
		_stage = stage;
		_diamond = diamond;
		_equip_item = equip_item;

		for (int i = 0; i < NUM_ITEMS; i++)
			_owned_items[i] = owned_items[i];
	}

	State::~State() {}

	string State::Stage()
	{
		return _stage;
	}

	int State::Diamond()
	{
		return _diamond;
	}

	int State::EquipItem()
	{
		return	_equip_item;
	}

	bool* State::OwnedItem()
	{
		return _owned_items;
	}
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	//Memento
	Memento::Memento(State* state)
	{
		_state = state;
	}
	
	Memento::~Memento()
	{
		delete _state;
	}
	string Memento::Stage()
	{
		return _state->Stage();
	}

	void Memento::SetState(State* state)
	{
		_state = state;
	}
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	//Originator
	Originator& Originator::Instance()
	{
		static Originator instance;
		return instance;
	}

	Originator::Originator() {}

	void Originator::SetState(State* state)
	{
		_state = state;
	}

	void Originator::RestoreToMemento(Memento *memento)
	{
		_state = memento->_state;
		Items::Instance().SetItems(_state->OwnedItem());
		Items::Instance().UnloadAllItem();
		Items::Instance().Equip(_state->EquipItem(), true);
		CharacterData::Instance()->SetDiamond(_state->Diamond());
	}

	Memento* Originator::CreateMemento()
	{
		return new Memento(this->_state);
	}

/////////////////////////////////////////////////

/////////////////////////////////////////////////
	//Caretaker
	Caretaker::Caretaker() {}

	Caretaker::~Caretaker()
	{
		map<string, Memento*>::iterator it;
		for (it = _mementos.begin(); it != _mementos.end(); it++)
		{
			delete it->second;
		}
	}

	void Caretaker::SetMemento(Memento* memento)
	{
		//解決memory leak
		//如果key已經存在map之中，刪除舊的
		std::map<string, Memento*>::iterator it = _mementos.find(memento->Stage());
		if (it != _mementos.end())
		{
			delete it->second;
			_mementos.erase(memento->Stage());
		}
		_mementos[memento->Stage()] = memento;
	}

	Memento* Caretaker::GetMemento(string state)
	{	
		//避免沒有對應的memento
		std::map<string, Memento*>::iterator it = _mementos.find(state);
		if (it == _mementos.end())
		{
			return nullptr;
		}
		return _mementos[state];
	}

	Caretaker& Caretaker::Instance()
	{
		static Caretaker instance;
		return instance;
	}
}

/////////////////////////////////////////////////