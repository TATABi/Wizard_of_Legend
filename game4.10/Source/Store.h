#ifndef STORE_H
#define STORE_H
#include "Items.h"

namespace game_framework {
	class Store {
	public:
		Store(int ,int);								// 設定初始中心點
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove(float *);							
		bool Buy(int);									//購買商店內第幾號道具
		void Shelf();									//重新上架
		void OnShow();
	private:
		CMovingBitmap _bm_sold_out;
		bool _isItemSoldOut[3] = {false,false,false};	//是否還有商品
		vector<Item *> _store_item;						//商店的道具
		int _cx, _cy;									//角色位置
		int _x, _y;										//位置
		const int DX = 49;								//每個物品擺放的間距
	};
}
#endif