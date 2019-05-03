#ifndef TOWN_STATE_CONTROLLER_H
#define TOWN_STATE_CONTROLLER_H

#include "Map_Town.h"
#include "Store.h"
#include "Global_Class.h"

namespace game_framework {

	class Town_State_Controller {

		enum FLAG 
		{
			FLAG_TOWN_NORMAL,
			FLAG_TOWN_PAUSED,
			FLAG_TOWN_OPTIONS,
			FLAG_TOWN_BAG
		};

	public:
		Town_State_Controller();
		~Town_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();
		bool IsSwitchGameState();
		int GameState();

	private:
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		FLAG _flag;										
		Map_Town _map;								
		Store _item_store;								//�D��ө�
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		Items *_items;
		UI *_ui;
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		int _game_state_num;
		bool _isSwitch;

		
		
		
	};

}

#endif
