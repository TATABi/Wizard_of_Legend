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
		CMovingBitmap bm_background;
		CMovingBitmap bm_cursor;
		const int SKILL_X = 30;
		bool isOpened;
		int class_flag;	//技能種類
		int type_flag;	//技能類型	(普攻,Dash....)
	};

}

#endif