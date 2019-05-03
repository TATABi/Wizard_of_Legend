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
		FLAG _flag;								
		int _delayCounter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Home _map;									
		Box _box;
		Book _book;
		
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
