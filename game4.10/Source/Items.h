#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "map"
#include "vector"

namespace game_framework {
	class Items {
	public:
		Items();
		~Items();
		void Initialize();		//匯入所有道具
		void LoadBitmap();
		bool Buy(string);	//回傳購買失敗/成功
		void Equip(string, bool);	//裝備道具
		void Effect();
		//vector<Item*> GetItemInBag();
		vector<Item*> GetItemInBox();
	//private:
		//std::map<std::string, Item*> items;
		vector<Item*> items;
		vector<Item*> temp_items;
	};

}


#endif