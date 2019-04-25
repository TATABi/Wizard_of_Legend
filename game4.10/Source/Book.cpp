#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Book.h"

namespace game_framework {
	Book::Book() {
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

		_bm_background.SetTopLeft(25, 120);
		_bm_cursor.SetTopLeft(44, 80);
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

	void Book::Up()
	{
		//if(class_flag)
	}

	void Book::Down()
	{

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
		}
	}
}