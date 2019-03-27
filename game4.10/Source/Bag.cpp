#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Bag.h"

namespace game_framework {
	Bag::Bag() {
		Initialize();
	}

	void Bag::Initialize()
	{
		isOpened =  false;
	}
	void Bag::LoadBitmap()
	{
		bm_bag.LoadBitmap(BAG_BOARD, RGB(50, 255, 0));

		bm_bag.SetTopLeft(50, 70);

	}

	void Bag::OnMove(vector<Item*> item)
	{
		if (isOpened)
		{
			temp_item = item;
		}
	}

	void Bag::OnShow()
	{
		int row = 0;
		int col = 0;

		if (isOpened)
		{
			bm_bag.ShowBitmap();

			for (int i = 0; i < temp_item.size(); i++)
			{
				if (row == 6) {
					row = 0;
					col++;
				}

				temp_item[i]->SetXY(67 + 25 * row, 170 + 25 * col);
				temp_item[i]->OnShow();
				row++;			
				
			}
		}
	}

	void Bag::Open(bool opened)
	{
		isOpened = opened;
	}

	
}