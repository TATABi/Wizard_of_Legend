#ifndef BOOK_H
#define BOOK_H

namespace game_framework {
	class Book{
	public:
		Book();
		void Initialize();		//初始化
		void LoadBitmap();		//匯入圖片
		void SetXY();			//設定圖片初始位置
		void Open(bool);		//開啟、關閉
		void OnMove();			//設定圖片位置
		void OnShow();			//顯示圖片
		void Left();			//向左選擇
		void Right();			//向右選擇
	private:
		CMovingBitmap _bm_background;			//背景
		CMovingBitmap _bm_cursor;				//游標
		CMovingBitmap _bm_skill_1_description	//技能描述
					 ,_bm_skill_2_description
					 ,_bm_skill_3_description
					 ,_bm_skill_4_description;
		bool _isOpened;			//是否開啟
		int _type_flag;			//技能種類
	};
}

#endif