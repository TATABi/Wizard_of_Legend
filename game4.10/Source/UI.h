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
		const int statusX = 30;
		const int statusY = 20;
		int hp_array[4] = {26, 8, 109, 19};		//�Mstatus�۹��m(���Wx,���Wy,�k�Ux,�k�Uy)
		int maxHp, currentHp;
		int change;
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
		CBrush brush_hp, pOldBrush;		//brush
		long RGB_hp;					//����C��
	};
}
