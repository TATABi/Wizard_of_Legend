#ifndef HOME_STATE_CONTROLLER_H
#define HOME_STATE_CONTROLLER_H
#include "Map_Home.h"
#include "Box.h"
#include "Book.h"
#include "Bag.h"
#include "UI.h"
#include "Controller.h"
#include "PausedMenu.h"

namespace game_framework {
	class Home_State_Controller :public Controller {
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
		void Initialize();								//初始化
		void Begin();									//重置數據
		void OnKeyUp(UINT, UINT, UINT);					//放開按鍵	
		void OnKeyDown(UINT, UINT, UINT);				//壓下按鍵
		void OnLButtonDown(UINT, CPoint);				//壓下左鍵
		void OnRButtonDown(UINT, CPoint);				//壓下右鍵
		void OnMove();									//邏輯運算
		void OnShow();									//顯示
	private:
		CMovingBitmap _bm_join;							//join遊戲的提示選單
		CMovingBitmap _bm_loading;						//loading字樣的圖片
		CAnimation _ani_light_beam;						//角色在家中現身的動畫
		FLAG _flag;										//紀錄現在所處階段
		int _delayCounter;								//進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Home _map;									//遊戲地圖
		Box _box;										//道具箱
		Book _book;										//書
	};
}

#endif
