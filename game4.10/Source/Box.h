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
		CMovingBitmap bm_board;
		CMovingBitmap bm_item_board;
		CMovingBitmap bm_cursor;
		CMovingBitmap bm_equip_board;
		CMovingBitmap bm_offense_text;
		CMovingBitmap bm_defense_text;
		CMovingBitmap bm_misc_text;
		CMovingBitmap bm_unknown_item;
		CAnimation ani_offense;
		CAnimation ani_defense;
		CAnimation ani_misc;
		int category_flag;	//¤ÀÃþ 0:offense 1:defense 2:misc 
		int item_flag_x;
		int item_flag_y;
		bool isOpened;
		bool isOpendOffense;
		bool isOpendDefense;
		bool isOpendMisc;
		Item* temp_item = nullptr;
		int choose_flag;
		const int ITEM_X = 40;
		const int ITEM_Y = 40;
		int NUMBER_OF_OFFENSE = 1;
		int NUMBER_OF_DEFENSE = 1;
		int NUMBER_OF_MISC = 1;
	
	};

}

#endif