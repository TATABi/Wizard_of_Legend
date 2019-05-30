#ifndef STORE_H
#define STORE_H
#include "Items.h"

namespace game_framework {
	class Store {
	public:
		Store(int ,int);  // �]�w��l�����I
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
		const int DX = 49;				//�C�Ӫ��~�\�񪺶��Z
	};
}
#endif