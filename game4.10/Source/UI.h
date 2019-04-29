#ifndef UI_H
#define UI_H
#include "CharacterData.h"

namespace game_framework {
	class UI {
	public:
		UI();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void CalculateHP();	//≠p∫‚HP
		void CalculateMP(); //≠p∫‚MP

	private:
		CMovingBitmap _bm_status;
		CMovingBitmap _bm_money;
		CMovingBitmap _bm_diamond;
		CMovingBitmap _bm_skill1_background;
		CMovingBitmap _bm_skill2_background;
		CMovingBitmap _bm_skill3_background;
		CMovingBitmap _bm_skill4_background;
		CMovingBitmap _bm_skill_1;
		CMovingBitmap _bm_skill_2;
		CMovingBitmap _bm_skill_3;
		CMovingBitmap _bm_skill_4;
		CMovingBitmap _bm_key_q;
		CMovingBitmap _bm_key_space;
		CMovingBitmap _bm_right_button;
		CMovingBitmap _bm_left_button;
		CMovingBitmap _bm_status_hp;
		CMovingBitmap _bm_slash;
		CInteger _integer;
	};
}

#endif
