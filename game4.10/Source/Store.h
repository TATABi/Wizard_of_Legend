#ifndef STORE_H
#define STORE_H
#include "Items.h"

namespace game_framework {
	class Store {
	public:
		Store(int ,int);  // 設定初始中心點
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove(float *);
		bool Buy(int, Items *);
		void Shelf(Items *);
		void OnShow();
	private:
		CMovingBitmap _bm_sold_out;
		bool _isItemSoldOut[3] = {false,false,false};
		vector<Item *> _store_item;
		int _cx, _cy;
		int _x, _y;
		const int DX = 49;				//每個物品擺放的間距
	};
}
#endif