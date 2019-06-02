#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Controller.h"
#include "CharacterData.h"
#include "Items.h"

namespace game_framework {

	Controller::Controller() {}

	Controller::~Controller() {}

	void Controller::Cheater(UINT keycode)
	{
		if (keycode == KEY_F1)
		{
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
		}
		else if (keycode == KEY_F2)
		{
			_game_state_num = GAME_STATE_RUN_TOWN;
			_isSwitch = true;
		}
		else if (keycode == KEY_F3)
		{
			_game_state_num = GAME_STATE_RUN_LEVEL_1;
			_isSwitch = true;
		}
		/*
		else if (keycode == KEY_F4)
		{
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
		}
		else if (keycode == KEY_F5)
		{
			_game_state_num = GAME_STATE_RUN_HOME;
			_isSwitch = true;
		}
		*/
		else if (keycode == KEY_F6)
		{
			bool _owned_items[7] = { true, true, true, true, true, true, true };
			State* state = new State("Stage 1", 20, 1, _owned_items);
			Originator o;
			o.SetState(state);
			o.SetRecord();
			Caretaker caretaker;
			caretaker.SetMemento(o.CreateMemento());

			delete state;
			
		}
		else if (keycode == KEY_F7)
		{
			CharacterData::Instance()->LockHP();
			CharacterData::Instance()->SetAttackCoefficient(100);
			CharacterData::Instance()->AddMoney(999);
			CharacterData::Instance()->AddDiamond(999);
		}
	}

	void Controller::Initialize() {}
	void Controller::Begin() {}
	void Controller::OnKeyUp(UINT, UINT, UINT) {}
	void Controller::OnKeyDown(UINT, UINT, UINT) {}
	void Controller::OnLButtonDown(UINT, CPoint) {}
	void Controller::OnRButtonDown(UINT, CPoint) {}
	void Controller::OnShow() {}

	bool Controller::IsSwitchGameState()
	{
		return _isSwitch;
	}
	int Controller::GameState()
	{
		return _game_state_num;
	}
}