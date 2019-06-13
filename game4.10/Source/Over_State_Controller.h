#ifndef OVER_STATE_CONTROLLER_H
#define OVER_STATE_CONTROLLER_H

#include "Controller.h"

namespace game_framework {
	class Over_State_Controller :public Controller {
		enum FLAG {
			FLAG_NORMAL
		};
	public:
		Over_State_Controller();
		~Over_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyDown(UINT, UINT, UINT);
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap _bm_result;							
		CMovingBitmap _bm_black_mask;				//小地圖遮罩
		CAnimation	_ani_play_keyboard;
		CInteger _int_stage;						//到達的關卡
		CInteger _int_gold_found;					//找到的money數量
		CInteger _int_gems_collected;				//找到的diamond數量
		CInteger _int_enemy_defeated;				//擊敗的敵人數量
		FLAG _flag;
		int _delay_counter;							//進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		int _mask_counter;							//讓數字慢慢出現用的counter
		bool _isPlayed;								//判斷是否破關
		int result[4];								//存4個CInteger的數值
	};
}

#endif
