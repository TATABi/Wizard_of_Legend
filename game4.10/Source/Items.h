#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"

namespace game_framework {
	class Items {
	public:
		Items();
		~Items();
		void Initialize();				//�פJ�Ҧ��D��
		void LoadBitmap();
		bool Buy(int);					//�^���ʶR����/���\
		void Equip(int, bool);			//�˳ƹD��
		void Effect();					//OnMove()����
		int GetNumberOfItem(string);
		void UnloadAllItem();
		void SetItems(bool[7]);			//�ΨӦ^�_Item���A(Ū�ɡB���}���d)
		Item* GetEquipAndOwnedItem();	//�^�Ǹ˳ƥB�֦����˳�(�]�@���u��˳Ƥ@��X��)
		vector<Item*> GetItemInBag();	//�˳Ƥ����D��
		vector<Item*> GetAllItem();		//�Ҧ����D��
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