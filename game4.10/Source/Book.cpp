#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Book.h"

namespace game_framework {
	Book::Book() 
	{
		Initialize();
	}

	void Book::Initialize() {
		_class_flag = 0;
		_type_flag = 0;
		_isOpened = false;
	}

	void Book::LoadBitmap() {
		_bm_background.LoadBitmap(BOOK_BOARD, RGB(50, 255, 0));
		_bm_cursor.LoadBitmap(BOOK_CURSOR, RGB(50, 255, 0));
		
		_bm_skill_1_description.LoadBitmap(BOOK_SKILL_DES_01, RGB(50, 255, 0));
		_bm_skill_2_description.LoadBitmap(BOOK_SKILL_DES_02, RGB(50, 255, 0));
		_bm_skill_3_description.LoadBitmap(BOOK_SKILL_DES_03, RGB(50, 255, 0));
		_bm_skill_4_description.LoadBitmap(BOOK_SKILL_DES_04, RGB(50, 255, 0));
		
		_bm_background.SetTopLeft(25, 120);
		_bm_cursor.SetTopLeft(44, 80);

		
		_bm_skill_1_description.SetTopLeft(25, 250);
		_bm_skill_2_description.SetTopLeft(25, 250);
		_bm_skill_3_description.SetTopLeft(25, 250);
		_bm_skill_4_description.SetTopLeft(25, 250);
	}

	void Book::OnMove() 
	{
		if(_isOpened)
			_bm_cursor.SetTopLeft(40 + 67 * _type_flag, 128);
	}

	void Book::Open(bool opened)
	{
		_isOpened = opened;
		
		if (!opened)
			Initialize();
	}

	void Book::Left()
	{
		if (_type_flag > 0)
			_type_flag--;
	}

	void Book::Right()
	{
		if (_type_flag < 3)
			_type_flag++;
	}

	void Book::OnShow()
	{
		if (_isOpened)
		{
			_bm_background.ShowBitmap();
			_bm_cursor.ShowBitmap();
			
			
			switch (_type_flag)
			{
			case 0:
				_bm_skill_1_description.ShowBitmap();
				break;
			case 1:
				_bm_skill_2_description.ShowBitmap();
				break;
			case 2:
				_bm_skill_3_description.ShowBitmap();
				break;
			case 3:
				_bm_skill_4_description.ShowBitmap();
				break;
			}

		}
	}
}