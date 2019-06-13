#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Controller.h"
#include "CharacterData.h"
#include "Items.h"
#include "Character.h"
#include "Memento.h"
#include <fstream>

namespace game_framework {

	Controller::Controller() {}

	Controller::~Controller() {}

	void Controller::Initialize() {}
	void Controller::Begin() {}
	void Controller::OnKeyUp(UINT, UINT, UINT) {}
	void Controller::OnKeyDown(UINT, UINT, UINT) {}
	void Controller::OnLButtonDown(UINT, CPoint) {}
	void Controller::OnRButtonDown(UINT, CPoint) {}
	void Controller::OnShow() {}

	void Controller::Cheater(UINT keycode)
	{
		if (keycode == KEY_F1)	//����a��home
		{
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
		}
		else if (keycode == KEY_F2)	//����a��town
		{
			_game_state_num = GAME_STATE_RUN_TOWN;
			_isSwitch = true;
		}
		else if (keycode == KEY_F3)	//����a�����d1
		{
			_game_state_num = GAME_STATE_RUN_LEVEL_1;
			_isSwitch = true;
		}
		else if (keycode == KEY_F4)	//�L�ġB���B�p��999�B�ˮ`�Y��100
		{
			CharacterData::Instance().SuperMode(!CharacterData::Instance().ISSUPERMODE());
		}
		else if (keycode == KEY_F5)	//�۱�
		{
			CharacterData::Instance().SuperMode(false);
			CharacterData::Instance().AddHP(-CharacterData::Instance().HP());
		}
	}
	
	bool Controller::IsSwitchGameState()
	{
		return _isSwitch;
	}

	int Controller::GameState()
	{
		return _game_state_num;
	}

	void Controller::CharacterDead()
	{
		if (CharacterData::Instance().HP() == 0)
		{
			bool isDead;
			isDead = Character::Instance().Dead();	//���⦺�`
			isDead ? (_isSwitch = true, _game_state_num = GAME_STATE_OVER) : NULL;
		}
	}

	void Controller::SaveMemento(std::string stateName)
	{
		State *state;
		vector<bool> bool_items = Items::Instance().GetSaveData();
		bool own_Items[NUM_ITEMS];
		for (int i = 0; i < NUM_ITEMS; i++)
		{
			own_Items[i] = bool_items[i];
		}
		//�S���˳Ʀb���W�AGetEquipAndOwnedItem�^��nullptr
		if (Items::Instance().GetEquipAndOwnedItem() == nullptr)
		{
			state = new State(stateName, 0, own_Items);
		}
		else 
		{
			state = new State(stateName, Items::Instance().GetEquipAndOwnedItem()->GetNumber(), own_Items);
		}
		Originator::Instance().SetState(state);
		Caretaker::Instance().SetMemento(Originator::Instance().CreateMemento());
	}

	void Controller::LoadMemento(std::string stateName)
	{
		//�䤣��memento�^��nullptr
		Memento *memento = Caretaker::Instance().GetMemento(stateName);
		if (memento != nullptr)
		{
			Originator::Instance().RestoreToMemento(Caretaker::Instance().GetMemento(stateName));
		}
	}
	
	void Controller::SaveData()
	{
		fstream file;
		file.open(SAVE_DATA_PATH, ios::out);
		if (file)
		{
			//�g�J�p��
			file << CharacterData::Instance().DIAMOND() << CHAR_TAB;

			//�g�J�ϥΥB�֦����˳�
			if (Items::Instance().GetEquipAndOwnedItem() == nullptr)
			{
				file << 0 << CHAR_TAB;
			}
			else
			{
				file << Items::Instance().GetEquipAndOwnedItem()->GetNumber() << CHAR_TAB;
			}

			//�g�J�֦����˳�
			vector<bool> bool_items = Items::Instance().GetSaveData();
			for (int i = 0; i < NUM_ITEMS; i++)
			{
				if (bool_items[i] == true)
					file << STRING_TURE << CHAR_TAB;
				else
					file << STRING_FALSE << CHAR_TAB;
			}
			file.close();
		}
	}

	void Controller::LoadData()
	{
		fstream file;
		file.open(SAVE_DATA_PATH, ios::in);
		if (file)
		{
			string s;
			bool bool_items[NUM_ITEMS];

			//Ū���B�]�w�p�ۼƶq
			getline(file, s, CHAR_TAB);
			CharacterData::Instance().SetDiamond(atoi(s.c_str()));

			//Ū���B�]�w�֦��B�ϥΤ����˳�
			getline(file, s, CHAR_TAB);
			if (Items::Instance().GetItem(atoi(s.c_str())) != nullptr)
			{
				Items::Instance().GetItem(atoi(s.c_str()))->SetItem(true);
				Items::Instance().Equip(atoi(s.c_str()), true);
			}

			for (int i = 0; i < NUM_ITEMS; i++)
			{
				getline(file, s, CHAR_TAB);
				if (s == STRING_TURE)
					bool_items[i] = true;
				else
					bool_items[i] = false;
			}
			Items::Instance().SetItems(bool_items);
			file.close();
		}
		else
		{
			//�p�G�ɮפ��s�b�A�s�ؤ@��
			ResetData();
		}
	}

	void Controller::ResetData()
	{
		fstream file;
		file.open(SAVE_DATA_PATH, ios::out);
		if (file)
		{
			//�s�ɹw�]0\t0\tfalse\tfalse\tfalse\tfalse\tfalse\tfalse\tfalse\t
			file << 0 << CHAR_TAB;
			file << 0 << CHAR_TAB;
			for (int i = 0; i < NUM_ITEMS; i++)
			{
				file << STRING_FALSE << CHAR_TAB;
			}
			file.close();
		}
	}
}