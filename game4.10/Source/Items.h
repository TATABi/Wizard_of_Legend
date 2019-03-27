#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"

namespace game_framework {
	class Items {
	public:
		Items();
		~Items();
		void Initialize();		//�פJ�Ҧ��D��
		void LoadBitmap();
		bool Buy(int);	//�^���ʶR����/���\
		void Equip(int, bool);	//�˳ƹD��
		void Effect();	//OnMove()������
		vector<Item*> GetItemInBag();	//�˳Ƥ����D��
		vector<Item*> GetAllItem();	//�֦����D��
		vector<Item*> GetItemInStore();	//�٥��ʶR���D��
	private:
		vector<Item*> items;			//�Ҧ��D��
		vector<Item*> temp_items;		//�Ψӿz��
	};

}


#endif