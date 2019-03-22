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
		bm_status.SetTopLeft(statusX, statusY);	//�]�wUI_Status��m
		maxHp = 500;							//��q��l��
		currentHp = 500;					
		//currentHp = CharacterData::HP;			
		RGB_hp = RGB(152, 0, 14);				//�����RGB	
		brush_hp.CreateSolidBrush(RGB_hp);		//�]�wbrush�C��
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
		pDC->Rectangle(statusX + hp_array[0], statusY + hp_array[1], statusX + hp_array[2] - change , statusY + hp_array[3]);		//�]�w��m
		pDC->SelectObject(pOldBrush);
		CDDraw::ReleaseBackCDC();				//�M��
	}
}