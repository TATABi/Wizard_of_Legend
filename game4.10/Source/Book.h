#ifndef BOOK_H
#define BOOK_H

namespace game_framework {
	class Book{
	public:
		Book();
		void Initialize();
		void LoadBitmap();
		void Open(bool);
		void OnMove();
		void OnShow();
		void Up();
		void Down();
		void Left();
		void Right();
	private:
		CMovingBitmap _bm_background;
		CMovingBitmap _bm_cursor;
		const int _SKILL_X = 30;
		bool _isOpened;
		int _class_flag;	//�ޯ����
		int _type_flag;	//�ޯ�����	(����,Dash....)
	};

}

#endif