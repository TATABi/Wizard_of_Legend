#ifndef BAG_H
#define BAG_H
#include "Item.h"

namespace game_framework {
	class Bag {
	public :
		static Bag &Instance();			//Singleton
		void Initialize();				//初始設定變數
		void LoadBitmap();				//匯入圖片
		void SetTopLeft();				//設定圖片位置
		void OnMove();					//更新背包內容
		void OnShow();					//顯示背包
		void Open(bool);				//開啟or關閉背包
		void Up();						//游標往上
		void Down();					//游標往下
		void Left();					//游標往左
		void Right();					//游標往右
	protected:
		Bag();
	private:
		CMovingBitmap _bm_bag;			//背包背景圖
		CMovingBitmap _bm_skill1		//Skill圖片
					 ,_bm_skill2
					 ,_bm_skill3
					 ,_bm_skill4;
		CMovingBitmap _bm_item_cursor;	//選擇道具游標
		bool _isOpened;					//是否開啟背包
		vector<Item*> _items;			//背包內的物品
		int _flags[2];					//游標座標
	};
}

#endif