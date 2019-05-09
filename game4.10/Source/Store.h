#ifndef STORE_H
#define STORE_H
#include "Items.h"

namespace game_framework {
	class Store {
	public:
		Store();  // 設定初始中心點
		void Initialize();
		void LoadBitmap();
		void SetXY(int *);
		bool Buy(int, Items *);
		void Shelf(Items *);

		void OnShow(int *);
	private:
		CMovingBitmap _bm_sold_out;
		bool _isItemSoldOut[3] = {false,false,false};
		vector<Item *> _store_item;

	};

}
#endif