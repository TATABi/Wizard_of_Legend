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
		void OpenMap(bool ,int);				//開啟地圖
		void ResetMapMask();		//重置地圖遮罩
	protected:
		UI();
	private:
		CMovingBitmap _bm_status;				//角色資訊
		CMovingBitmap _bm_money;				//money icon
		CMovingBitmap _bm_diamond;				//diamond icon
		CMovingBitmap _bm_skill1_background,	//Skill UI 背景
					  _bm_skill2_background,
					  _bm_skill3_background,
					  _bm_skill4_background;
		CMovingBitmap _bm_skill_1,				//Skill UI 圖示
					  _bm_skill_2,
					  _bm_skill_3,
					  _bm_skill_4;
		CMovingBitmap _bm_key_q;				//UI Q鍵
		CMovingBitmap _bm_key_m;				//UI M鍵
		CMovingBitmap _bm_key_tab;				//UI Tab鍵
		CMovingBitmap _bm_map;					//UI Map圖示
		CMovingBitmap _bm_info;					//UI Info圖示
		CMovingBitmap _bm_key_space;			//UI Space鍵
		CMovingBitmap _bm_right_button;			//UI Right button鍵
		CMovingBitmap _bm_left_button;			//UI Left button鍵
		CMovingBitmap _bm_slash;				//UI 斜線
		CMovingBitmap _bm_map_1;				//Level 1的小地圖
		CMovingBitmap _bm_map_mask;				//Map遮罩
		CMovingBitmap _bm_character_head;		//Map上角色頭像
		CMovingBitmap _bm_map_board;			//Map Board
		CAnimation _ani_mp_bar;					//Mp閃爍動畫
		CInteger _int_diamond,					//基本數值的數字
				 _int_money,
				 _int_maxhp,
			     _int_hp;
		CInteger _skiil_2_cooldown,				//Skill冷卻計時
				 _skiil_3_cooldown;
		bool _isOpenMap = false;				//是否開啟地圖
		bool _map_mask[10][10];					//紀錄Map Mask值
		int _map_num;							//紀錄開啟Map的編號
	};
}

#endif
