#ifndef ITEM_H
#define ITEM_H
#include "CharacterData.h"

namespace game_framework {
	class Item {
	public:
		Item(int, string, int, int, bool (*) (), void (*) ());		//�Ϥ�,����, �s��, ��, �ĪG
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
		int GetNumber();
	private:
		bool (*_Launched)();		//�ˬd�O�_�����o�ʱ���A�����N�o�ʡA�^��true�F�����������ơA�^��false
		void (*_Stripping)();	//�Ѱ��˳ƮɭY���o�ʮĪG�h�n���榹�禡�Ѱ��ĪG
		CMovingBitmap _bm_item;
		CMovingBitmap _bm_info;
		string _type;			//item ����
		int _number;				//item �s��
		bool _isEquiped;			//�O�_�˳�
		bool _isLuanched;		//�o��
		bool _isOwned;			//�֦��Ӹ˳�
		int _diamond;
		int _bm_number;			//�Ȧs�Ϥ��s���A��LoadBitmap�ɦA�פJ�Ϥ�
		
	};

}


#endif