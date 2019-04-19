#ifndef ITEM_H
#define ITEM_H
#include "CharacterData.h"

namespace game_framework {
	class Item {
	public:
		Item(int, string, int, int, bool (*) (), void (*) ());		//圖片,種類, 編號, 錢, 效果
		void Initialize();
		void LoadBitmap();
		void SetXY(int, int);
		void OnShow();
		void Equip(bool);	// 穿/脫 裝備
		bool IsEquiped();	// 是否裝備
		void Effect();		// 啟動能力
		bool HaveItem();
		bool BuyItem();
		string GetType();
		int GetNumber();
	private:
		bool (*Launched)();		//檢查是否滿足發動條件，滿足就發動，回傳true；不滿足不做事，回傳false
		void (*Stripping)();	//解除裝備時若有發動效果則要執行此函式解除效果
		CMovingBitmap bm_item;
		string type;			//item 種類
		int number;				//item 編號
		bool isEquiped;			//是否裝備
		bool isLuanched;		//發動
		bool isOwned;			//擁有該裝備
		int diamond;
		int bm_number;			//暫存圖片編號，等LoadBitmap時再匯入圖片
		
	};

}


#endif