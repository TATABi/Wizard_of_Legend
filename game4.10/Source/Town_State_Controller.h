#ifndef TOWN_STATE_CONTROLLER_H
#define TOWN_STATE_CONTROLLER_H

#include "Map_Town.h"
#include "Store.h"
#include "Controller.h"
#include "Bag.h"
#include "UI.h"
#include "PausedMenu.h"

namespace game_framework {
	class Town_State_Controller : public Controller{
		enum FLAG								
		{
			FLAG_TOWN_NORMAL,
			FLAG_TOWN_PAUSED,
			FLAG_TOWN_OPTIONS,
			FLAG_TOWN_BAG
		};
	public:
		Town_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap _bm_loading;						// loading字樣的圖片
		FLAG _flag;										//狀態flag
		Map_Town _map;									//Town地圖
		Store _item_store;								//道具商店
		int _delayCounter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
	};
}

#endif