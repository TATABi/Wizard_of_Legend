#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "UI.h"
#include "GameData.h"

namespace game_framework {

	UI& UI::Instance()
	{
		static UI instance;
		return instance;
	}

	UI::UI(){}

	void UI::LoadBitmap()
	{
		_bm_status.LoadBitmap(UI_STATUS, RGB(50, 255, 0));
		_bm_money.LoadBitmap(UI_MONEY, RGB(50, 255, 0));
		_bm_diamond.LoadBitmap(UI_DIAMOND, RGB(50, 255, 0));
		_bm_skill1_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		_bm_skill2_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		_bm_skill3_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		_bm_skill4_background.LoadBitmap(UI_SKILL_BACKGROUND, RGB(50, 255, 0));
		_bm_key_q.LoadBitmap(UI_KEY_Q, RGB(50, 255, 0));
		_bm_key_space.LoadBitmap(UI_KEY_SPACE, RGB(50, 255, 0));
		_bm_right_button.LoadBitmap(UI_KEY_RIGHT, RGB(50, 255, 0));
		_bm_left_button.LoadBitmap(UI_KEY_LEFT, RGB(50, 255, 0));
		_bm_slash.LoadBitmap(IDB_SLASH, RGB(0, 0, 0));
		_integer.LoadBitmap();

		_bm_skill_1.LoadBitmap(SKILL_ICON_AIR_SPINNER, RGB(50, 255, 0));
		_bm_skill_2.LoadBitmap(SKILL_ICON_AIR_BURST, RGB(50, 255, 0));
		_bm_skill_3.LoadBitmap(SKILL_ICON_REBOUNDING_ICICLES, RGB(50, 255, 0));
		_bm_skill_4.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));

		int a[9] = { UI_MP_BAR_SHINE_01, UI_MP_BAR_SHINE_02, UI_MP_BAR_SHINE_03, UI_MP_BAR_SHINE_04, UI_MP_BAR_SHINE_05,
					 UI_MP_BAR_SHINE_06, UI_MP_BAR_SHINE_07, UI_MP_BAR_SHINE_08, UI_MP_BAR_SHINE_09 };
		for (int i = 0; i < 9; i++)
			_ani_mp_bar.AddBitmap(a[i]);

		_ani_mp_bar.SetDelayCount(3);
	
		_bm_skill_1.SetTopLeft(27, 440);
		_bm_skill_2.SetTopLeft(54, 440);
		_bm_skill_3.SetTopLeft(81, 440);
		_bm_skill_4.SetTopLeft(108, 440);
		_ani_mp_bar.SetTopLeft(51, 47);
		_bm_status.SetTopLeft(25, 30);
		_bm_diamond.SetTopLeft(300, 430);
		_bm_money.SetTopLeft(300, 450);
		_bm_skill1_background.SetTopLeft(27, 440);
		_bm_skill2_background.SetTopLeft(54, 440);
		_bm_skill3_background.SetTopLeft(81, 440);
		_bm_skill4_background.SetTopLeft(108, 440);
		_bm_left_button.SetTopLeft(27, 414);
		_bm_key_space.SetTopLeft(54, 415);
		_bm_right_button.SetTopLeft(81, 414);
		_bm_key_q.SetTopLeft(108, 416);
		_bm_slash.SetTopLeft(103, 25);
		
	}
	
	void UI::OnMove()
	{
		if (CharacterData::Instance()->ISMAGICBUFF())
			_ani_mp_bar.OnMove();
	}
	
	void UI::OnShow()
	{
		_bm_status.ShowBitmap();
		_bm_money.ShowBitmap();
		_bm_diamond.ShowBitmap();
		_bm_skill1_background.ShowBitmap();
		_bm_skill2_background.ShowBitmap();
		_bm_skill3_background.ShowBitmap();
		_bm_skill4_background.ShowBitmap();
		_bm_key_q.ShowBitmap();
		_bm_key_space.ShowBitmap();
		_bm_right_button.ShowBitmap();
		_bm_left_button.ShowBitmap();

		_bm_skill_1.ShowBitmap();
		_bm_skill_2.ShowBitmap();
		_bm_skill_3.ShowBitmap();
		_bm_skill_4.ShowBitmap();
		
		if (CharacterData::Instance()->ISMAGICBUFF())
			_ani_mp_bar.OnShow();

		CalculateHP();
		CalculateMP();

		_integer.SetTopLeft(320, 453);
		_integer.SetInteger(CharacterData::Instance()->MONEY());
		_integer.ShowBitmap();
		_integer.SetTopLeft(320, 433);
		_integer.SetInteger(CharacterData::Instance()->DIAMOND());
		_integer.ShowBitmap();
		_integer.SetTopLeft(112, 25);
		_integer.SetInteger(CharacterData::Instance()->MAX_HP());
		_integer.ShowBitmap();
		_integer.SetTopLeft(83, 25);
		_integer.SetInteger(CharacterData::Instance()->HP());
		_integer.ShowBitmap();
		_bm_slash.ShowBitmap();		
	}

	void UI::CalculateHP()
	{
		const int MAX_HP_X2 = 132;
		const int MAX_HP_Y1 = 34;
		const int MAX_HP_Y2 = 46;
		float temp_hp;
		int x1;

		temp_hp = (float)(CharacterData::Instance()->MAX_HP() - CharacterData::Instance()->HP()) / CharacterData::Instance()->MAX_HP();		//�p���q�t��
		x1 = (int)(temp_hp * 81);
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// �e�Ǧ� (����)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(MAX_HP_X2-x1, MAX_HP_Y1, MAX_HP_X2, MAX_HP_Y2);
		pDC->SelectObject(pb);						// ���� brush
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	void UI::CalculateMP()
	{
		const int Max_MP_X2 = 116;
		const int MAX_MP_Y1 = 47;
		const int MAX_MP_Y2 = 54;
		float temp_mp;
		int x1;

		temp_mp = (float)(CharacterData::Instance()->MAX_MP() - CharacterData::Instance()->MP()) / CharacterData::Instance()->MAX_MP();		//�p��MP�t��
		x1 = (int)(temp_mp * 65);
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CBrush *pb, b(RGB(28, 35, 34));				// �e�Ǧ� (��MP)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(Max_MP_X2 - x1, MAX_MP_Y1, Max_MP_X2, MAX_MP_Y2);
		pDC->SelectObject(pb);						// ���� brush
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
}
