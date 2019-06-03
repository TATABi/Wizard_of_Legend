#ifndef UI_H
#define UI_H
#include "CharacterData.h"

namespace game_framework {
	class UI {
	public:
		static UI &Instance();		//Singleton
		void LoadBitmap();			//匯入圖片
		void SetXY();				//設定位置
		void OnMove();				//計算
		void OnShow();				//顯示
		void CalculateHP();			//計算 & 顯示HP
		void CalculateMP();			//計算 & 顯示MP
	protected:
		UI();
	private:
		CMovingBitmap _bm_status;
		CMovingBitmap _bm_money;
		CMovingBitmap _bm_diamond;
		CMovingBitmap _bm_skill1_background,	//Skill UI 背景
					  _bm_skill2_background,
					  _bm_skill3_background,
					  _bm_skill4_background;
		CMovingBitmap _bm_skill_1,				//Skill UI 圖示
					  _bm_skill_2,
					  _bm_skill_3,
					  _bm_skill_4;
		CMovingBitmap _bm_key_q;				//UI Q鍵
		CMovingBitmap _bm_key_space;			//UI Space鍵
		CMovingBitmap _bm_right_button;			//UI Right button鍵
		CMovingBitmap _bm_left_button;			//UI Left button鍵
		CMovingBitmap _bm_slash;				//UI 斜線
		CAnimation _ani_mp_bar;
		CInteger _int_diamond,					//基本數值的數字
				 _int_money,
				 _int_maxhp,
			     _int_hp;
		CInteger _skiil_2_cooldown,				//Skill冷卻計時
				 _skiil_3_cooldown;
	};
}

#endif
