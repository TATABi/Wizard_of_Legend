#ifndef BAG_H
#define BAG_H
#include "Item.h"
namespace game_framework {
	
	class Bag {
	public :
		Bag();
		void Initialize();
		void LoadBitmap();
		void OnMove(vector<Item*>);
		void OnShow();
		void Open(bool);
	private:
		CMovingBitmap bm_bag;
		bool isOpened;
		vector<Item*> temp_item;

		CMovingBitmap skill1;
		CMovingBitmap skill2;

	};

}

#endif