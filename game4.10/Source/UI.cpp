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
		bm_status.SetTopLeft(statusX, statusY);	//設定UI_Status位置
		maxHp = 500;							//血量初始化
		currentHp = 500;					
		//currentHp = CharacterData::HP;			
		RGB_hp = RGB(152, 0, 14);				//血條的RGB	
		brush_hp.CreateSolidBrush(RGB_hp);		//設定brush顏色
	}


	void UI::OnMove()
	{
		//currentHp = CharacterData::HP;
		change = (maxHp - currentHp) / 6;
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
		CBrush *pOldBrush = pDC->SelectObject(&brush_hp);
		pDC->Rectangle(statusX + hp_array[0], statusY + hp_array[1], statusX + hp_array[2] - change , statusY + hp_array[3]);		//設定位置
		pDC->SelectObject(pOldBrush);
		CDDraw::ReleaseBackCDC();				//清除
	}
}