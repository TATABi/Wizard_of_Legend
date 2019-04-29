#ifndef HOME_STATE_CONTROLLER_H
#define HOME_STATE_CONTROLLER_H

#include "Map_Home.h"
#include "Box.h"
#include "Book.h"
#include "Global_Class.h"

namespace game_framework {

	class Home_State_Controller {

		enum FLAG {
			FLAG_HOME_NORMAL,
			FLAG_JOIN,
			FLAG_BOX,
			FLAG_BOX_ITEM,
			FLAG_HOME_PAUSED,
			FLAG_HOME_OPTIONS,
			FLAG_HOME_BAG,
			FLAG_BOOK
		};

	public:
		Home_State_Controller();
		~Home_State_Controller();
		void Initialize();
		void LoadBitmap();
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
		CMovingBitmap _bm_join;							// join遊戲的提示選單
		CMovingBitmap _bm_loading;						// loading字樣的圖片
		CAnimation _ani_light_beam;						// 角色在家中現身的動畫
		FLAG _flag;										// 現在畫面的狀態 0:顯示加入遊戲的選項 1:進入遊戲(沒開任何選單) 2:開啟道具箱 3:開啟書 4:傳送至Town
		int _delayCounter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Home _map;									// 地圖
		Box _box;
		Book _book;
		
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		Items *_items;
		UI *_ui;
		
		int _game_state_num;
		bool _isSwitch;
		
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_F = 0x46;
		const char KEY_ESC = 27;
		const char KEY_SPACE = 0x20;
		const char KEY_TAB = 0x09;

	};

}

#endif
