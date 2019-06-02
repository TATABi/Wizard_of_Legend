#ifndef ITEM_H
#define ITEM_H


namespace game_framework {
	class Item {
	public:
		Item(int, int, string, int, int, bool (*) (), void (*) ());		//item�Ϥ�, item�����Ϥ�, ����, �s��, ��, �ĪG
		void Initialize();
		void LoadBitmap();
		void SetXY(int, int);
		void OnShow();
		void Equip(bool);	// ��/�� �˳�
		bool IsEquiped();	// �O�_�˳�
		void Effect();		// �Ұʯ�O
		bool OwnedItem();
		bool BuyItem();
		string GetType();
		int GetNumber();
		void SetItem(bool);		//�ΨӦ^�_Item���A(Ū�ɡB���}���d)
		void ShowInfo(int, int);		//���Item���ĪG����
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
		int _pic;			//�Ȧs�Ϥ��s���A��LoadBitmap�ɦA�פJ�Ϥ�
		int _info_pic;	
	};
}


#endif