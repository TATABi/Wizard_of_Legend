#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "UI.h"


namespace game_framework {
	UI::UI() {}

	void UI::Initialize()
	{
		//設定UI_Status位置
		UI_status_x = 30;
		UI_status_y = 20;
		UI_hp_x = 40;
		UI_hp_y = 150;
		bm_status.SetTopLeft(UI_status_x, UI_status_y);
		
		//血條的RGB 內:(212,92,104), 中:(181,21,35), 外(104,19,32)
		RGB_hp_1 = RGB(212, 92, 104);
		RGB_hp_2 = RGB(181, 21, 35);
		RGB_hp_3 = RGB(104, 19, 32);
		//設定brush顏色
		brush_hp_1.CreateSolidBrush(RGB_hp_1);
		brush_hp_2.CreateSolidBrush(RGB_hp_2);
		brush_hp_3.CreateSolidBrush(RGB_hp_3);
	}


	void UI::OnMove()
	{
		//hp = 500;
	}
	
	void UI::LoadBitmap()
	{
		bm_status.LoadBitmap(UI_Status, RGB(50, 255, 0));
	}

	void UI::OnShow()
	{
		bm_status.ShowBitmap();
		StatusOnShow();
		
	}

	void UI::StatusOnShow()
	{
		pDC = CDDraw::GetBackCDC();
		CBrush *pOldBrush = pDC->SelectObject(&brush_hp_1);
		pDC->Rectangle(50, 10, 60, 15);		//設定位置
		pDC->SelectObject(pOldBrush);
		CDDraw::ReleaseBackCDC();
	}
}