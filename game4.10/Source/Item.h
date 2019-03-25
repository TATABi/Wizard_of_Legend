#ifndef ITEM_H
#define ITEM_H

namespace game_framework {
	class Item {
	public:
		Item(int);
		void Initialize();
		void OnMove();
		void OnShow();
		void Equip(bool);	// ��/�� �˳�
		void MeetCondition();	//�����o�ʯ�O����
		bool IsEquiped();	// �O�_�˳�
		void Effect();		// �Ұʯ�O
		bool HaveItem();
		bool BuyItem();
	private:
		CMovingBitmap bm_item;
		bool isEquiped;			//�O�_�˳�
		bool isReady;	//�����o�ʱ���
		bool isLuanched;		//�o��
		bool isOwned;			//�֦��Ӹ˳�
		int money;
	};

}


#endif