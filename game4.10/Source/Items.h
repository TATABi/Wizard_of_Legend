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
		void Initialize();		//�פJ�Ҧ��D��
		void LoadBitmap();
		bool Buy(string);	//�^���ʶR����/���\
		void Equip(string, bool);	//�˳ƹD��
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