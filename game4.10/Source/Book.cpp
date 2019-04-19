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
		class_flag = 0;
		type_flag = 0;
		isOpened = false;
	}

	void Book::LoadBitmap() {
		bm_background.LoadBitmap(BOOK_BOARD, RGB(50, 255, 0));
		bm_cursor.LoadBitmap(BOOK_CURSOR, RGB(50, 255, 0));

		bm_background.SetTopLeft(25, 120);
		bm_cursor.SetTopLeft(44, 80);
	}

	void Book::OnMove() 
	{
		if(isOpened)
			bm_cursor.SetTopLeft(40 + 67 * type_flag, 128);
	}

	void Book::Open(bool opened)
	{
		isOpened = opened;
		
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
		if (type_flag > 0)
			type_flag--;
	}

	void Book::Right()
	{
		if (type_flag < 3)
			type_flag++;
	}

	void Book::OnShow()
	{
		if (isOpened)
		{
			bm_background.ShowBitmap();
			bm_cursor.ShowBitmap();
		}
	}
}