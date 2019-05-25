#ifndef INIT_STATE_CONTROLLER_H
#define INIT_STATE_CONTROLLER_H
#include "Controller.h"

namespace game_framework {

	class Init_State_Controller : public Controller{

		enum FLAG {
			FLAG_INIT_INIT,
			FLAG_INIT_MENU,
			FLAG_INIT_OPTION
		};

		enum INSTRUCTION {
			SINGLE_PLAYER,
			OPTION,
			QUIT
		};

	public:
		Init_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnShow();

	private:
		CAnimation _ani_menu_1;
		CAnimation _ani_menu_2;
		CMovingBitmap _bm_option;
		CMovingBitmap _bm_quit;
		CMovingBitmap _bm_single_player;
		CMovingBitmap _bm_loading;
		CMovingBitmap _bm_option_page;
		int _flag;
		int _instruction;
	};
}

#endif
