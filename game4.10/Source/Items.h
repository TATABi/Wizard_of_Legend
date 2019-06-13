#ifndef ITEMS_H
#define ITEMS_H
#include "Item.h"
#include "vector"
#include "GameData.h"

namespace game_framework {
	class Items {
	public:

		static Items& Instance();
		void Initialize();				//�פJ�Ҧ��D��
		void LoadBitmap();
		bool Buy(int);					//�^���ʶR����/���\
		void Equip(int, bool);			//�˳ƹD��
		void Effect();					//OnMove()����
		int GetNumberOfItem(string);	//�z�L�˳ƺ������o�����s��
		void UnloadAllItem();			//�Ѱ��Ҧ��˳Ƥ����D��
		void SetItems(bool[NUM_ITEMS]);	//�ΨӦ^�_Item���A(Ū�ɡB���}���d)
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
		vector<Item*> _items;			//�Ҧ��D��
		vector<Item*> _temp_items;		//�Ψӿz��
	};
}

#endif