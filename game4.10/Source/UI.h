#include "CharacterData.h"

namespace game_framework {
	class UI {
	public:
		UI() ;
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void StatusOnShow();
	private:
		int UI_status_x, UI_status_y, UI_hp_x, UI_hp_y, hp= 500;
		CMovingBitmap bm_status;
		CMovingBitmap bm_money;
		CMovingBitmap bm_diamond;
		CMovingBitmap bm_skill_background;
		CMovingBitmap bm_key_q;
		CMovingBitmap bm_key_space;
		CMovingBitmap bm_right_button;
		CMovingBitmap bm_left_button;
		CMovingBitmap bm_hp_bar;
		CDC *pDC;
		CBrush brush_hp_1, brush_hp_2, brush_hp_3, pOldBrush;
		long RGB_hp_1, RGB_hp_2, RGB_hp_3;			//血條顏色依序由內到外
	};
}
