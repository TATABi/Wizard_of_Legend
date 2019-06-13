#ifndef STORE_H
#define STORE_H
#include "Items.h"

namespace game_framework {
	class Store {
	public:
		Store(int ,int);								// �]�w��l�����I
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove(float *);							
		bool Buy(int);									//�ʶR�ө����ĴX���D��
		void Shelf();									//���s�W�[
		void OnShow();
	private:
		CMovingBitmap _bm_sold_out;
		bool _isItemSoldOut[3] = {false,false,false};	//�O�_�٦��ӫ~
		vector<Item *> _store_item;						//�ө����D��
		int _cx, _cy;									//�����m
		int _x, _y;										//��m
		const int DX = 49;								//�C�Ӫ��~�\�񪺶��Z
	};
}
#endif