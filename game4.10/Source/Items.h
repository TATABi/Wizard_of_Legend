#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"

namespace game_framework {
	class Items {
	public:
		static Items& Instance();
		void Initialize();		//�פJ�Ҧ��D��
		void LoadBitmap();
		bool Buy(int);					//�^���ʶR����/���\
		void Equip(int, bool);			//�˳ƹD��
		void Effect();					//OnMove()����
		int GetNumberOfItem(string);
		void UnloadAllItem();
		void SetItems(bool[7]);			//�ΨӦ^�_Item���A(Ū�ɡB���}���d)
		vector<bool> GetSaveData();		//�^�ǩҦ�item���֦����A
		Item* GetItem(int);				//���o�s�����D��
		Item* GetEquipAndOwnedItem();	//�^�Ǹ˳ƥB�֦����˳�(�]�@���u��˳Ƥ@��X��)
		vector<Item*> GetItemInBag();	//�˳Ƥ����D��
		vector<Item*> GetAllItem();		//�Ҧ����D��
		vector<Item*> GetItemInStore();	//�٥��ʶR���D��
		~Items();
	protected:
		Items();
	private:
		//static Items* _instance;
		vector<Item*> _items;			//�Ҧ��D��
		vector<Item*> _temp_items;		//�Ψӿz��
		int NUMBER_OF_OFFENSE = 2;
		int NUMBER_OF_DEFENSE = 3;
		int NUMBER_OF_MISC = 2;
	};

}

#endif