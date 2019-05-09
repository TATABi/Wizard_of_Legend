#ifndef BOX_H
#define BOX_H
#include "Items.h"

namespace game_framework {
	class Box {
	public:
		Box();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow(Items*);
		void Down();
		void Up();
		void Left();
		void Right();
		void Open(bool);
		void OpenOpen(bool);
		bool Equip(Items*);
	private:
		CMovingBitmap _bm_board;
		CMovingBitmap _bm_item_board;
		CMovingBitmap _bm_cursor;
		CMovingBitmap _bm_equip_board;
		CMovingBitmap _bm_offense_text;
		CMovingBitmap _bm_defense_text;
		CMovingBitmap _bm_misc_text;
		CMovingBitmap _bm_unknown_item;
		CAnimation _ani_offense;
		CAnimation _ani_defense;
		CAnimation _ani_misc;
		int _category_flag;	//¤ÀÃþ 0:offense 1:defense 2:misc 
		int _item_flag_x;
		int _item_flag_y;
		bool _isOpened;
		bool _isOpendOffense;
		bool _isOpendDefense;
		bool _isOpendMisc;
		Item* _temp_item = nullptr;
		int _choose_flag;
		const int _ITEM_X = 40;
		const int _ITEM_Y = 40;
		int _NUMBER_OF_OFFENSE = 1;
		int _NUMBER_OF_DEFENSE = 1;
		int _NUMBER_OF_MISC = 1;
	
	};

}

#endif