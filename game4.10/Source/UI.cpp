#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "UI.h"
#include "GameData.h"
#include "Character.h"

namespace game_framework {

	UI& UI::Instance()
	{
		static UI instance;
		return instance;
	}

	UI::UI():_skiil_2_cooldown(1), _skiil_3_cooldown(1) 
	{
		Initialize();
	}

	void UI::Initialize()
	{
		_isOpenMap = false;
		_x = -180;
		_end_counter = 0;
		_isEnd = false;
		ResetMapMask();
	}

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
		_int_diamond.LoadBitmap();
		_int_money.LoadBitmap();
		_int_maxhp.LoadBitmap();
		_int_hp.LoadBitmap();
		_skiil_2_cooldown.LoadBitmap();
		_skiil_3_cooldown.LoadBitmap();
		_bm_skill_1.LoadBitmap(SKILL_ICON_AIR_SPINNER, RGB(50, 255, 0));
		_bm_skill_2.LoadBitmap(SKILL_ICON_AIR_BURST, RGB(50, 255, 0));
		_bm_skill_3.LoadBitmap(SKILL_ICON_REBOUNDING_ICICLES, RGB(50, 255, 0));
		_bm_skill_4.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));	
		_bm_map_1.LoadBitmap(MAP_LEVEL_01_SIMPLE);
		_bm_map_mask.LoadBitmap(MAP_MASK);
		_bm_character_head.LoadBitmap(UI_CHARACTER_HEAD, RGB(50, 255, 0));
		_bm_map_board.LoadBitmap(UI_MAP_BOARD);
		_bm_key_m.LoadBitmap(UI_KEY_M, RGB(50, 255, 0));
		_bm_key_tab.LoadBitmap(UI_KEY_TAB, RGB(50, 255, 0));
		_bm_map.LoadBitmap(UI_MAP, RGB(50, 255, 0));
		_bm_info.LoadBitmap(UI_INFO, RGB(50, 255, 0));
		_bm_attack_buff.LoadBitmap(UI_ATTACK_BUFF, RGB(50, 255, 0));
		_bm_speed_buff.LoadBitmap(UI_SPEED_BUFF, RGB(50, 255, 0));
		_bm_cooldown_buff.LoadBitmap(UI_COOLDOWN_BUFF, RGB(50, 255, 0));
		_bm_stage_cleared.LoadBitmap(UI_STAGE_CLEARED, RGB(50, 255, 0));
		_bm_line.LoadBitmap(UI_STAGE_CLEARED_LINE);

		int a[9] = { UI_MP_BAR_SHINE_01, UI_MP_BAR_SHINE_02, UI_MP_BAR_SHINE_03, UI_MP_BAR_SHINE_04, UI_MP_BAR_SHINE_05,
					 UI_MP_BAR_SHINE_06, UI_MP_BAR_SHINE_07, UI_MP_BAR_SHINE_08, UI_MP_BAR_SHINE_09 };
		
		for (int i = 0; i < 9; i++)
			_ani_mp_bar.AddBitmap(a[i]);
		_ani_mp_bar.SetDelayCount(3);

		SetXY();
	}
	
	void UI::SetXY()
	{
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
		_bm_info.SetTopLeft(155, 440);
		_bm_map.SetTopLeft(182, 440);
		_bm_left_button.SetTopLeft(27, 414);
		_bm_key_space.SetTopLeft(54, 415);
		_bm_right_button.SetTopLeft(81, 414);
		_bm_key_q.SetTopLeft(108, 416);
		_bm_key_tab.SetTopLeft(155, 416);
		_bm_key_m.SetTopLeft(182, 416);
		_bm_slash.SetTopLeft(103, 25);
		_int_money.SetTopLeft(320, 453);
		_int_diamond.SetTopLeft(320, 433);
		_int_maxhp.SetTopLeft(112, 25);
		_int_hp.SetTopLeft(83, 25);
		_skiil_2_cooldown.SetTopLeft(90, 445);
		_skiil_3_cooldown.SetTopLeft(117, 445);
		_bm_map_1.SetTopLeft(120, 40);
		_bm_map_board.SetTopLeft(107, 27);
		_bm_attack_buff.SetTopLeft(55, 55);
		_bm_speed_buff.SetTopLeft(80, 55);
		_bm_cooldown_buff.SetTopLeft(105, 55);
	}

	void UI::OnMove()
	{
		//集滿MP時發光效果
		if (CharacterData::Instance().ISMAGICBUFF())		
			_ani_mp_bar.OnMove();

		//設定UI顯示
		_int_hp.SetInteger(CharacterData::Instance().HP());
		_int_maxhp.SetInteger(CharacterData::Instance().MAX_HP());
		_int_diamond.SetInteger(CharacterData::Instance().DIAMOND());
		_int_money.SetInteger(CharacterData::Instance().MONEY());
		_skiil_2_cooldown.SetInteger(Character::Instance().GetSkillCooldown(2) / 30 + 1);
		_skiil_3_cooldown.SetInteger(Character::Instance().GetSkillCooldown(3) / 30 + 1);
		_bm_character_head.SetTopLeft(int(Character::Instance().GetPosition()[0] / 10) + 120, int(Character::Instance().GetPosition()[1] / 10) + 40);
		_map_mask[int(Character::Instance().GetPosition()[0] / 400)][int(Character::Instance().GetPosition()[1] / 400)] = true;

		if (_isEnd)
		{
			_bm_stage_cleared.SetTopLeft(640 - _end_counter, 210);
			_bm_line.SetTopLeft(_x + _end_counter, 230);
			_end_counter > 900 ? _isEnd = false :  _end_counter += 4;
		}
	}
	
	void UI::OnShow()
	{
		//顯示圖片
		_bm_status.ShowBitmap();
		_bm_money.ShowBitmap();
		_bm_diamond.ShowBitmap();
		_bm_skill1_background.ShowBitmap();
		_bm_skill2_background.ShowBitmap();
		_bm_skill3_background.ShowBitmap();
		_bm_skill4_background.ShowBitmap();
		_bm_key_q.ShowBitmap();
		_bm_key_tab.ShowBitmap();
		_bm_key_m.ShowBitmap();
		_bm_key_space.ShowBitmap();
		_bm_right_button.ShowBitmap();
		_bm_left_button.ShowBitmap();
		_bm_skill_1.ShowBitmap();
		_bm_skill_2.ShowBitmap();
		_bm_map.ShowBitmap();
		_bm_info.ShowBitmap();
		_int_money.ShowBitmap();
		_int_diamond.ShowBitmap();
		
		//判斷技能是否處於冷卻狀態，若正在冷卻，則倒數冷卻時間
		Character::Instance().GetSkillCooldown(2) != 0 ? _skiil_2_cooldown.ShowBitmap() : _bm_skill_3.ShowBitmap();;
		Character::Instance().GetSkillCooldown(3) != 0 ? _skiil_3_cooldown.ShowBitmap() : _bm_skill_4.ShowBitmap();;
		
		//判斷MP集滿動畫
		if (CharacterData::Instance().ISMAGICBUFF())
			_ani_mp_bar.OnShow();	

		//計算HP, MP
		CalculateHP();
		CalculateMP();
		_int_maxhp.ShowBitmap();
		_int_hp.ShowBitmap();
		_bm_slash.ShowBitmap();
		CharacterData::Instance().ISATTACKBUFF() ? _bm_attack_buff.ShowBitmap() : NULL;
		CharacterData::Instance().ISSPEEDBUFF() ? _bm_speed_buff.ShowBitmap() : NULL;
		CharacterData::Instance().ISCOOLDOWNBUFF() ? _bm_cooldown_buff.ShowBitmap() : NULL;
		
		if (_isOpenMap)
		{
			_bm_map_board.ShowBitmap();

			switch (_map_num)
			{
			case 1:
				_bm_map_1.ShowBitmap();
				break;
			case 2:
				break;
			case 3:
				break;
			}
				
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (_map_mask[i][j] == false)
					{
						_bm_map_mask.SetTopLeft(120 + 40 * i, 40 + 40 * j);
						_bm_map_mask.ShowBitmap();
					}
				}
			}
			_bm_character_head.ShowBitmap();
		}

		if (_isEnd && _end_counter > 0)
		{
			_bm_stage_cleared.ShowBitmap();
			_bm_line.ShowBitmap();
		}
	}

	void UI::CalculateHP()
	{
		const int MAX_HP_X2 = 132;
		const int MAX_HP_Y1 = 34;
		const int MAX_HP_Y2 = 46;
		float temp_hp;
		int x1;

		//繪製HP
		temp_hp = (float)(CharacterData::Instance().MAX_HP() - CharacterData::Instance().HP()) / CharacterData::Instance().MAX_HP();		//計算血量差值
		x1 = (int)(temp_hp * 81);
		CDC *pDC = CDDraw::GetBackCDC();								// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));									// 畫灰色 (扣血)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(MAX_HP_X2 - x1, MAX_HP_Y1, MAX_HP_X2, MAX_HP_Y2);
		pDC->SelectObject(pb);											// 釋放 brush
		CDDraw::ReleaseBackCDC();										// 放掉 Back Plain 的 CDC
	}

	void UI::CalculateMP()
	{
		const int MAX_MP_X2 = 116;
		const int MAX_MP_Y1 = 47;
		const int MAX_MP_Y2 = 54;
		float temp_mp;
		int x1;

		//繪製MP
		temp_mp = (float)(CharacterData::Instance().MAX_MP() - CharacterData::Instance().MP()) / CharacterData::Instance().MAX_MP();		//計算MP差值
		x1 = (int)(temp_mp * 65);
		CDC *pDC = CDDraw::GetBackCDC();							// 取得 Back Plain 的 CDC 
		CBrush *pb, b(RGB(28, 35, 34));								// 畫灰色 (扣MP)
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(MAX_MP_X2 - x1, MAX_MP_Y1, MAX_MP_X2, MAX_MP_Y2);
		pDC->SelectObject(pb);										// 釋放 brush
		CDDraw::ReleaseBackCDC();									// 放掉 Back Plain 的 CDC
	}

	void UI::OpenMap(bool Opened, int i)
	{
		_map_num = i;
		_isOpenMap = Opened;
	}

	void UI::ResetMapMask()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				_map_mask[i][j] = false;
	}

	void UI::StageCleared()
	{
		CAudio::Instance()->Play(AUDIO_STAGE_CLEANED);
		_isEnd = true;	
	}
}
