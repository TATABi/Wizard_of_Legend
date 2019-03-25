#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "UI.h"

namespace game_framework {

	UI::UI()
	{
		Initialize();
	}
	
	void UI::Initialize()
	{
		
	}

	void UI::LoadBitmap()
	{

		bm_status.LoadBitmap(UI_STATUS, RGB(50, 255, 0));
		bm_money.LoadBitmap(UI_MONEY, RGB(50, 255, 0));
		bm_diamond.LoadBitmap(UI_DIAMOND, RGB(50, 255, 0));
		bm_skill1_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		bm_skill2_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		bm_skill3_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		bm_skill4_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		bm_key_q.LoadBitmap(UI_KEY_Q, RGB(50, 255, 0));
		bm_key_space.LoadBitmap(UI_KEY_SPACE, RGB(50, 255, 0));
		bm_right_button.LoadBitmap(UI_KEY_RIGHT, RGB(50, 255, 0));
		bm_left_button.LoadBitmap(UI_KEY_LEFT, RGB(50, 255, 0));
		bm_slash.LoadBitmap(IDB_SLASH, RGB(0, 0, 0));

		integer.LoadBitmap();

		bm_status.SetTopLeft(25, 30);
		bm_diamond.SetTopLeft(300, 430);
		bm_money.SetTopLeft(300, 450);
		bm_skill1_background.SetTopLeft(27, 440);
		bm_skill2_background.SetTopLeft(54, 440);
		bm_skill3_background.SetTopLeft(81, 440);
		bm_skill4_background.SetTopLeft(108, 440);
		bm_left_button.SetTopLeft(27, 414);
		bm_key_space.SetTopLeft(54, 415);
		bm_right_button.SetTopLeft(81, 414);
		bm_key_q.SetTopLeft(108, 416);
		bm_slash.SetTopLeft(103, 25);
		

	}
	
	void UI::OnMove()
	{
		//將技能放進UI中
	}
	
	void UI::OnShow()
	{
		bm_status.ShowBitmap();
		bm_money.ShowBitmap();
		bm_diamond.ShowBitmap();
		bm_skill1_background.ShowBitmap();
		bm_skill2_background.ShowBitmap();
		bm_skill3_background.ShowBitmap();
		bm_skill4_background.ShowBitmap();
		bm_key_q.ShowBitmap();
		bm_key_space.ShowBitmap();
		bm_right_button.ShowBitmap();
		bm_left_button.ShowBitmap();
		
		CalculateHP();
		CalculateMP();

		integer.SetTopLeft(320, 453);
		integer.SetInteger(CharacterData::Money);
		integer.ShowBitmap();
		integer.SetTopLeft(320, 433);
		integer.SetInteger(CharacterData::Diamond);
		integer.ShowBitmap();
		integer.SetTopLeft(112, 25);
		integer.SetInteger(CharacterData::Max_HP);
		integer.ShowBitmap();
		integer.SetTopLeft(83, 25);
		integer.SetInteger(CharacterData::HP);
		integer.ShowBitmap();
		bm_slash.ShowBitmap();

			
	}

	void UI::CalculateHP()
	{
		const int MAX_HP_X2 = 132;
		const int MAX_HP_Y1 = 34;
		const int MAX_HP_Y2 = 46;
		float temp_hp;
		int x1;
		temp_hp = (float)(CharacterData::Max_HP - CharacterData::HP) / CharacterData::Max_HP ;		//計算血量差值
		x1 = (int)(temp_hp * 81);

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// 畫灰色 (扣血)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(MAX_HP_X2-x1, MAX_HP_Y1, MAX_HP_X2, MAX_HP_Y2);
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	
	}

	void UI::CalculateMP()
	{
		const int Max_MP_X2 = 116;
		const int MAX_MP_Y1 = 47;
		const int MAX_MP_Y2 = 54;
		float temp_mp;
		int x1;
		temp_mp = (float)(CharacterData::Max_MP - CharacterData::MP) / CharacterData::Max_MP;		//計算MP差值
		x1 = (int)(temp_mp * 65);

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// 畫灰色 (扣MP)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(Max_MP_X2 - x1, MAX_MP_Y1, Max_MP_X2, MAX_MP_Y2);
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	
	}
}
