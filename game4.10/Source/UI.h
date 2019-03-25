#ifndef UI_H
#define UI_H
#include "CharacterData.h"
namespace game_framework {
	class UI {
	public:
		UI();
		~UI();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void CalculateHP();	//≠p∫‚HP
		void CalculateMP(); //≠p∫‚MP

	private:
		CMovingBitmap bm_status;
		CMovingBitmap bm_money;
		CMovingBitmap bm_diamond;
		CMovingBitmap bm_skill1_background;
		CMovingBitmap bm_skill2_background;
		CMovingBitmap bm_skill3_background;
		CMovingBitmap bm_skill4_background;
		CMovingBitmap bm_key_q;
		CMovingBitmap bm_key_space;
		CMovingBitmap bm_right_button;
		CMovingBitmap bm_left_button;
		CMovingBitmap bm_status_hp;
		CMovingBitmap bm_slash;
		CInteger integer;
	};
}

#endif
