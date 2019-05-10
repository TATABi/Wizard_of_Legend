#ifndef LEVEL_ONE_STATE_CONTROLLER_H
#define LEVEL_ONE_STATE_CONTROLLER_H

#include "Map_Level_One.h"
#include "Global_Class.h"

namespace game_framework {

	class Level_One_State_Controller {

		enum FLAG {
			FLAG_NORMAL,
			FLAG_PAUSED,
			FLAG_OPTIONS,
			FLAG_BAG
		};

	public:
		Level_One_State_Controller();
		~Level_One_State_Controller();
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
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Level_One _map;
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		Items *_items;
		UI *_ui;
		int _game_state_num;
		bool _isSwitch;

	};

}

#endif

