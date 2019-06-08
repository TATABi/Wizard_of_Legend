#ifndef BAG_H
#define BAG_H
#include "Item.h"

namespace game_framework {
	class Bag {
	public :
		static Bag &Instance();			//Singleton
		void Initialize();				//��l�]�w�ܼ�
		void LoadBitmap();				//�פJ�Ϥ�
		void SetTopLeft();				//�]�w�Ϥ���m
		void OnMove();					//��s�I�]���e
		void OnShow();					//��ܭI�]
		void Open(bool);				//�}��or�����I�]
		void Up();						//��Щ��W
		void Down();					//��Щ��U
		void Left();					//��Щ���
		void Right();					//��Щ��k
	protected:
		Bag();
	private:
		CMovingBitmap _bm_bag;			//�I�]�I����
		CMovingBitmap _bm_skill1		//Skill�Ϥ�
					 ,_bm_skill2
					 ,_bm_skill3
					 ,_bm_skill4;
		CMovingBitmap _bm_item_cursor;	//��ܹD����
		bool _isOpened;					//�O�_�}�ҭI�]
		vector<Item*> _items;			//�I�]�������~
		int _flags[2];					//��Юy��
	};
}

#endif