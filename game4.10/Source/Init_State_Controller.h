#ifndef INIT_STATE_CONTROLLER_H
#define INIT_STATE_CONTROLLER_H
#include "Controller.h"

namespace game_framework {

	class Init_State_Controller : public Controller{

		enum FLAG {
			FLAG_INIT_INIT,
			FLAG_INIT_MENU,
			FLAG_INIT_OPTION,
			FLAG_INIT_KEY_CONFIG,
			FLAG_INIT_RESET_DATA,
			FLAG_INIT_ABOUT
		};

		enum INSTRUCTION_MENU {
			SINGLE_PLAYER,
			OPTIONS,
			QUIT
		};

		enum INSTRUCTION_OPTIONS {
			KEY_CONFIG,
			RESET_DATA,
			ABOUT
		};

	public:
		Init_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();

	private:
		CAnimation _ani_menu_1;
		CAnimation _ani_menu_2;
		CAnimation _ani_reset_data;
		CMovingBitmap _bm_option;
		CMovingBitmap _bm_quit;
		CMovingBitmap _bm_single_player;
		CMovingBitmap _bm_loading;
		CMovingBitmap _bm_options_page_1, _bm_options_page_2, _bm_options_page_3;
		CMovingBitmap _bm_key_config;
		CMovingBitmap _bm_about;
		int _flag;
		int _instruction_1;
		int _instruction_2;
		int _audio_delay_counter;
	};
}

#endif
