#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"

namespace game_framework {
	class Items {
	public:
		Items();
		~Items();
		void Initialize();		//匯入所有道具
		void LoadBitmap();
		bool Buy(int);	//回傳購買失敗/成功
		void Equip(int, bool);	//裝備道具
		void Effect();	//OnMove()中用
		int GetNumberOfItem(string);
		void UnloadAllItem();
		vector<Item*> GetItemInBag();	//裝備中的道具
		vector<Item*> GetAllItem();	//擁有的道具
		vector<Item*> GetItemInStore();	//還未購買的道具
	private:
		vector<Item*> _items;			//所有道具
		vector<Item*> _temp_items;		//用來篩選
		const int NUMBER_OF_OFFENSE = 2;
		const int NUMBER_OF_DEFENSE = 3;
		const int NUMBER_OF_MISC = 2;
	};

}


#endif