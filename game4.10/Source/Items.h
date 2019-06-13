#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"
#include "GameData.h"

namespace game_framework {
	class Items {
	public:

		static Items& Instance();
		void Initialize();				//匯入所有道具
		void LoadBitmap();
		bool Buy(int);					//回傳購買失敗/成功
		void Equip(int, bool);			//裝備道具
		void Effect();					//OnMove()中用
		int GetNumberOfItem(string);	//透過裝備種類取得種類編號
		void UnloadAllItem();			//解除所有裝備中的道具
		void SetItems(bool[NUM_ITEMS]);	//用來回復Item狀態(讀檔、離開關卡)
		vector<bool> GetSaveData();		//回傳所有item的擁有狀態
		Item* GetItem(int);				//取得編號的道具
		Item* GetEquipAndOwnedItem();	//回傳裝備且擁有的裝備(因一次只能裝備一件出門)
		vector<Item*> GetItemInBag();	//裝備中的道具
		vector<Item*> GetAllItem();		//所有的道具
		vector<Item*> GetItemInStore();	//還未購買的道具
		~Items();
	protected:
		Items();
	private:
		vector<Item*> _items;			//所有道具
		vector<Item*> _temp_items;		//用來篩選
	};
}

#endif