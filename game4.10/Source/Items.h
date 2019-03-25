#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"
namespace game_framework {
	class Items {
	public:
		Items();
		void Initialize();		//匯入所有道具
		bool Buy(int);	//回傳購買失敗/成功
	private:
		std::vector<Item*> items;
	};

}


#endif