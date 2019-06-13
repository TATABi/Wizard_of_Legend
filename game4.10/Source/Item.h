#ifndef ITEM_H
#define ITEM_H

namespace game_framework { 
	enum ITEM_NUMBER
	{
		Amulet = 1,		//�������@����
		Helmet,			//�g���Y��
		Heart,			//���H����
		Glasses,		//�l�尭����
		Shoes,			//���Ȫ��K�c
		Pendulum,		//ù�������\
		Pocket_Watch	//�������h��
	};
	class Item {
	public:
		Item(int, int, string, enum ITEM_NUMBER, int, bool (*) (), void (*) ());	//item�Ϥ�, item�����Ϥ�, ����, �s��, ��, �ĪG
		void Initialize();							//��l�Ƹ��
		void LoadBitmap();							//�פJ�Ϥ�
		void SetXY(int, int);						//�]�wItem�y��
		void OnShow();								//���
		void Equip(bool);							//��/�� �˳�
		bool IsEquiped();							//�O�_�˳�
		void Effect();								//�P�_�ñҰʯ�O
		bool OwnedItem();							//�֦��˳�?
		bool BuyItem();								//�ʶR�˳�
		bool BuyAndEquip();							//�ʶR�ø˳�
		string GetType();							//���oItem������
		int GetNumber();							//����Item�s��
		void SetItem(bool);							//�ΨӦ^�_Item���A(Ū�ɡB���}���d)
		void ShowInfo(int, int);					//���Item���ĪG����
		void TakeOff();
	private:
		bool (*_Launched)();						//�ˬd�O�_�����o�ʱ���A�����N�o�ʡA�^��true�F�����������ơA�^��false
		void (*_Stripping)();						//�Ѱ��˳ƮɭY���o�ʮĪG�h�n���榹�禡�Ѱ��ĪG
		CMovingBitmap _bm_item;						//Item��
		CMovingBitmap _bm_info;						//Item Information��
		string _type;								//item ����
		enum ITEM_NUMBER _number;					//item �s��
		bool _isEquiped;							//�O�_�˳�
		bool _isLuanched;							//�o��
		bool _isOwned;								//�֦��Ӹ˳�
		int _diamond;								//����
		int _pic;									//�Ȧs�Ϥ��s���A��LoadBitmap�ɦA�פJ�Ϥ�
		int _info_pic;								//Item ��T�Ϫ��s��
	};
}

#endif