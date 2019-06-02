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
		CMovingBitmap _bm_black_mask;	//遮罩
		CAnimation	_ani_play_keyboard;
		CInteger _int_stage, _int_gold_found, _int_gems_collected, _int_enemy_defeated;
		FLAG _flag;
		int _delay_counter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		int _mask_counter;
		bool _isPlayed;
	};
}

#endif
