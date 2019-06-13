#ifndef BOX_H
#define BOX_H
#include "Items.h"

namespace game_framework {
	class Box {
	public:
		Box();					
		void Initialize();			//初始化
		void LoadBitmap();			//匯入圖片
		void SetXY();				//設定初始位置
		void OnMove();				//選取道具和裝備的判斷
		void OnShow(Items*);		//顯示
		void Down();				//往下選擇
		void Up();					//往上選擇
		void Left();				//往左選擇
		void Right();				//往右選擇
		void Open(bool);			//開道or關閉Box(外層)
		void OpenOpen(bool);		//開道or關閉Box(內層)
		bool Equip(Items*);			//裝備道具
	private:
		CMovingBitmap _bm_board;
		CMovingBitmap _bm_item_board;	
		CMovingBitmap _bm_cursor;		
		CMovingBitmap _bm_equip_board;
		CMovingBitmap _bm_offense_text;
		CMovingBitmap _bm_defense_text;
		CMovingBitmap _bm_misc_text;
		CMovingBitmap _bm_unknown_item;
		CMovingBitmap _bm_item_description_board;
		CAnimation _ani_offense;			//開櫃子動畫
		CAnimation _ani_defense;
		CAnimation _ani_misc;
		Item* equiped_item = nullptr;		//穿著的裝備
		Item* chosed_item = nullptr;		//選擇要裝備上的裝備
		int _category_flag;					//分類 0:offense 1:defense 2:misc 
		int _item_flag_x;					//游標x,y
		int _item_flag_y;
		bool _isOpened;
		bool _isOpendOffense;
		bool _isOpendDefense;
		bool _isOpendMisc;
		int _choose_flag;
		int _NUMBER_OF_OFFENSE;				//該類別總道具數量
		int _NUMBER_OF_DEFENSE;
		int _NUMBER_OF_MISC;
		const int _ITEM_X = 40;
		const int _ITEM_Y = 40;
	};
}

#endif