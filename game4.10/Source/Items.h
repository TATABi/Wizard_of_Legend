#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"
namespace game_framework {
	class Items {
	public:
		Items();
		void Initialize();		//�פJ�Ҧ��D��
		bool Buy(int);	//�^���ʶR����/���\
	private:
		std::vector<Item*> items;
	};

}


#endif