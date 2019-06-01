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
	Memento::Memento(const string state, int diamond, int equip_item, bool owned_items[7])
	{
		_state = state;
		_diamond = diamond;
		_equip_item = equip_item;

		for (int i = 0; i < 7; i++)
			_owned_items[i] = owned_items[i];
	}

	vector<string> Memento::ToString()
	{
		vector<string> data;
		stringstream ss;
		string diamond, equip, owned;

		for (int i = 0; i < sizeof(_owned_items) / sizeof(_owned_items[0]); i++)
			_owned_items[i] ? owned += "1" : owned += "0";

		ss << _diamond;
		ss >> diamond;
		ss.str("");
		ss.clear();
		
		ss << _equip_item;
		ss >> equip;

		data.push_back(_state);
		data.push_back(diamond);
		data.push_back(equip);
		data.push_back(owned);

		return data;
	}

	string Memento::State()
	{
		return _state;
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
		Items::Instance().SetItems(_memento->_owned_items);
		Items::Instance().Equip(_memento->_equip_item, true);
		CharacterData::Instance()->SetDiamond(_memento->_diamond);
	}

	string Originator::State()
	{
		return _memento->_state;
	}

	Caretaker::Caretaker() {}

	void Caretaker::Save(Memento* memento)
	{
		_mementos[memento->State()] = memento;
	
		fstream file;
		file.open("Data/save_data", ios::out);
		vector<string> data = memento->ToString();
		
		for (int i = 0; i < data.size(); i++)
			file << data[i] << " ";

		file.close();
	}

	Memento* Caretaker::Load(string state)
	{
		return _mementos[state];
	}

}