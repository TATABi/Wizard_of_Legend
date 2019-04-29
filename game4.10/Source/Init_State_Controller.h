#ifndef INIT_STATE_CONTROLLER_H
#define INIT_STATE_CONTROLLER_H

namespace game_framework {

	class Init_State_Controller {

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
		bool IsSwitchGameState();
		int GotoGameState();

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
		int _game_state_num;
		bool _isSwitch;
		const char KEY_ESC = 27;
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_SPACE = 0x20;
		const char KEY_ENTER = 0xD;

	};

}

#endif
