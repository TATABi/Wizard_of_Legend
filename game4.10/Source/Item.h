#ifndef ITEM_H
#define ITEM_H
#include "CharacterData.h"

namespace game_framework {
	class Item {
	public:
		Item(int, string, int, int, bool (*) ());		//�Ϥ�,����, �s��, ��, �ĪG
		void Initialize();
		void LoadBitmap();
		void SetXY(int, int);
		void OnShow();
		void Equip(bool);	// ��/�� �˳�
		bool IsEquiped();	// �O�_�˳�
		void Effect();		// �Ұʯ�O
		bool HaveItem();
		bool BuyItem();
		string GetType();
	private:
		bool (*Launched)();		//�ˬd�O�_�����o�ʱ���A�����N�o�ʡA�^��true�F�����������ơA�^��false
		CMovingBitmap bm_item;
		string type;			//item ����
		int number;				//item �s��
		bool isEquiped;			//�O�_�˳�
		bool isLuanched;		//�o��
		bool isOwned;			//�֦��Ӹ˳�
		int money;
		int bm_number;			//�Ȧs�Ϥ��s���A��LoadBitmap�ɦA�פJ�Ϥ�
		
	};

}


#endif