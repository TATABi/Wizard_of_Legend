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
	//State
	State::State(const string stage, int diamond, int equip_item, bool owned_items[7])
	{
		_stage = stage;
		_diamond = diamond;
		_equip_item = equip_item;

		for (int i = 0; i < 7; i++)
			_owned_items[i] = owned_items[i];
	}

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


	//Memento
	Memento::Memento(State* state)
	{
		_state = state;
	}

	string Memento::Stage()
	{
		return _state->Stage();
	}

	void Memento::SetState(State* state)
	{
		_state = state;
	}


	//Originator
	Originator::Originator(){}

	void Originator::SetState(State* state)
	{
		_state = state;
	}

	void Originator::RestoreToMemento(Memento *memento)
	{
		_state = memento->_state;
	}

	Memento* Originator::CreateMemento()
	{
		return new Memento(this->_state);
	}

	void Originator::SetRecord()
	{
		Memento* memento = CreateMemento();
		Items::Instance().SetItems(memento->_state->OwnedItem());
		Items::Instance().Equip(memento->_state->EquipItem(), true);
		CharacterData::Instance()->SetDiamond(memento ->_state->Diamond());
		delete memento;
	}


	//Caretaker
	Caretaker::Caretaker() {}

	Caretaker::~Caretaker()
	{
		map<string, Memento*>::iterator it;
		for (it = _mementos.begin(); it != _mementos.end(); it++)
			delete it->second;
	}

	void Caretaker::SetMemento(Memento* memento)
	{
		_mementos[memento->Stage()] = memento;
	}

	Memento* Caretaker::GetMemento(string state)
	{
		return _mementos[state];
	}

}