#ifndef BOOK_H
#define BOOK_H

namespace game_framework {
	class Book{
	public:
		Book();
		void Initialize();		//��l��
		void LoadBitmap();		//�פJ�Ϥ�
		void SetXY();			//�]�w�Ϥ���l��m
		void Open(bool);		//�}�ҡB����
		void OnMove();			//�]�w�Ϥ���m
		void OnShow();			//��ܹϤ�
		void Left();			//�V�����
		void Right();			//�V�k���
	private:
		CMovingBitmap _bm_background;			//�I��
		CMovingBitmap _bm_cursor;				//���
		CMovingBitmap _bm_skill_1_description	//�ޯ�y�z
					 ,_bm_skill_2_description
					 ,_bm_skill_3_description
					 ,_bm_skill_4_description;
		bool _isOpened;			//�O�_�}��
		int _type_flag;			//�ޯ����
	};
}

#endif