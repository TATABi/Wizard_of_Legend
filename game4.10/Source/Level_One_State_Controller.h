#ifndef LEVEL_ONE_STATE_CONTROLLER_H
#define LEVEL_ONE_STATE_CONTROLLER_H

#include "Map_Level_One.h"
#include "Controller.h"
#include "Bag.h"
#include "UI.h"
#include "PausedMenu.h"
#include "Items.h"
#include "Store.h"

namespace game_framework {

	class Level_One_State_Controller : public Controller{

		enum FLAG {								//控制flag
			FLAG_NORMAL,
			FLAG_PAUSED,
			FLAG_OPTIONS,
			FLAG_BAG,
			FLAG_MAP
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
		CMovingBitmap _bm_loading_level;				// loading字樣的圖片
		CMovingBitmap _bm_loading_chess;				//棋子圖片
		FLAG _flag;										//控制用flag
		int _delayCounter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Level_One _map;								//地圖Level one
		int _chess_xy[2];								//棋子位置
		bool _isUpDown;
	};
}

#endif