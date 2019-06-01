#ifndef BAG_H
#define BAG_H
#include "Item.h"

namespace game_framework {
	
	class Bag {
	public :
		static Bag &Instance();
		void Initialize();
		void LoadBitmap();
		void SetTopLeft();
		void OnMove();
		void OnShow();
		void Open(bool);
		void Up();
		void Down();
		void Left();
		void Right();
	protected:
		Bag();
	private:
		CMovingBitmap _bm_bag;
		CMovingBitmap _bm_skill1;
		CMovingBitmap _bm_skill2;
		CMovingBitmap _bm_skill3;
		CMovingBitmap _bm_skill4;
		CMovingBitmap _bm_item_cursor;
		bool _isOpened;
		vector<Item*> _items;
		int _flags[2];
		int _itemAmount;
	};

}

#endif