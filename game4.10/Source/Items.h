#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"

namespace game_framework {
	class Items {
	public:
		static Items& Instance();
		void Initialize();		//匯入所有道具
		void LoadBitmap();
		bool Buy(int);					//回傳購買失敗/成功
		void Equip(int, bool);			//裝備道具
		void Effect();					//OnMove()中用
		int GetNumberOfItem(string);
		void UnloadAllItem();
		void SetItems(bool[7]);			//用來回復Item狀態(讀檔、離開關卡)
		Item* GetEquipAndOwnedItem();	//回傳裝備且擁有的裝備(因一次只能裝備一件出門)
		vector<Item*> GetItemInBag();	//裝備中的道具
		vector<Item*> GetAllItem();		//所有的道具
		vector<Item*> GetItemInStore();	//還未購買的道具
	protected:
		Items();
		~Items();
	private:
		vector<Item*> _items;			//所有道具
		vector<Item*> _temp_items;		//用來篩選
		int NUMBER_OF_OFFENSE = 2;
		int NUMBER_OF_DEFENSE = 3;
		int NUMBER_OF_MISC = 2;
	};

}

#endif