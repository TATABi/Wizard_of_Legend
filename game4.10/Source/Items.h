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
		void Effect();	//OnMove()����
		int GetNumberOfItem(string);
		void UnloadAllItem();
		vector<Item*> GetItemInBag();	//�˳Ƥ����D��
		vector<Item*> GetAllItem();	//�֦����D��
		vector<Item*> GetItemInStore();	//�٥��ʶR���D��
	private:
		vector<Item*> _items;			//�Ҧ��D��
		vector<Item*> _temp_items;		//�Ψӿz��
		const int NUMBER_OF_OFFENSE = 2;
		const int NUMBER_OF_DEFENSE = 3;
		const int NUMBER_OF_MISC = 2;
	};

}


#endif