#ifndef LEVEL_ONE_STATE_CONTROLLER_H
#define LEVEL_ONE_STATE_CONTROLLER_H

#include "Map_Level_One.h"
#include "Global_Class.h"
#include "Controller.h"

namespace game_framework {

	class Level_One_State_Controller : public Controller{

		enum FLAG {
			FLAG_NORMAL,
			FLAG_PAUSED,
			FLAG_OPTIONS,
			FLAG_BAG
		};

	public:
		Level_One_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();

	private:
		CMovingBitmap _bm_loading_level;						// loading�r�˪��Ϥ�
		CMovingBitmap _bm_loading_chess;
		FLAG _flag;
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Level_One _map;
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		int _chess_xy[2];
		bool _isUpDown;
	};
}

#endif

