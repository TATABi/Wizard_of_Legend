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
		if (keycode == KEY_F1)	//跳到地圖home
		{
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
		}
		else if (keycode == KEY_F2)	//跳到地圖town
		{
			_game_state_num = GAME_STATE_RUN_TOWN;
			_isSwitch = true;
		}
		else if (keycode == KEY_F3)	//跳到地圖關卡1
		{
			_game_state_num = GAME_STATE_RUN_LEVEL_1;
			_isSwitch = true;
		}
		
		else if (keycode == KEY_F4)
		{
			Items::Instance().Equip(2, true);
			/*
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
			*/
		}
		else if (keycode == KEY_F5)
		{
			/*
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
			*/
		}
		
		else if (keycode == KEY_F6)	//無敵、錢、鑽石999、傷害係數100
		{
			CharacterData::Instance()->LockHP();
			CharacterData::Instance()->SetAttackCoefficient(100);
			CharacterData::Instance()->AddMoney(999);
			CharacterData::Instance()->AddDiamond(999);
		}
		else if (keycode == KEY_F7)	//自殺
		{
			CharacterData::Instance()->AddHP(-CharacterData::Instance()->HP());
		}
		else if (keycode == KEY_F8)	//建立memento，stateName = home
		{
			UpdateMemento("home");
		}
		else if (keycode == KEY_F9)	//復原memento，stateName = home
		{
			LoadMemento("home");
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
		if (CharacterData::Instance()->HP() == 0)
		{
			bool isDead;
			isDead = Character::Instance().Dead();	//角色死亡
			isDead ? _isSwitch = true, _game_state_num = GAME_STATE_OVER : NULL;
		}
	}

	void Controller::UpdateMemento(std::string stateName)
	{
		State *state;
		vector<bool> bool_items = Items::Instance().GetSaveData();
		bool own_Items[NUM_ITEMS];
		for (int i = 0; i < NUM_ITEMS; i++)
		{
			own_Items[i] = bool_items[i];
		}
		//沒有裝備在身上，GetEquipAndOwnedItem回傳nullptr
		if (Items::Instance().GetEquipAndOwnedItem() == nullptr)
		{
			state = new State(stateName, CharacterData::Instance()->DIAMOND(), 0, own_Items);
		}
		else 
		{
			state = new State(stateName, CharacterData::Instance()->DIAMOND(), Items::Instance().GetEquipAndOwnedItem()->GetNumber(), own_Items);
		}
		Originator::Instance().SetState(state);
		Caretaker::Instance().SetMemento(Originator::Instance().CreateMemento());
	}

	void Controller::LoadMemento(std::string stateName)
	{
		//找不到memento回傳nullptr
		Memento *memento = Caretaker::Instance().GetMemento(stateName);
		if (memento != nullptr)
		{
			Originator::Instance().RestoreToMemento(Caretaker::Instance().GetMemento(stateName));
		}
	}
}

/*
	bool _owned_items[7] = { true, true, true, true, true, true, true };
	State* state = new State("Stage 1", 20, 1, _owned_items);
	Originator::Instance().SetState(state);
	Originator::Instance().SetRecord();
	Caretaker::Instance().SetMemento(Originator::Instance().CreateMemento());
	delete state; 
*/