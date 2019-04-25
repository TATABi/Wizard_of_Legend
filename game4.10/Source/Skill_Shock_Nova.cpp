#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Shock_Nova.h"


namespace game_framework
{
	Skill_Shock_Nova::Skill_Shock_Nova(int mousreX, int mouseY, int *cxy) 		//中心往滑鼠位置的向量
	{
		LoadBitmap();
		Initialize(mousreX, mouseY, cxy);
		
	}

	Skill_Shock_Nova::~Skill_Shock_Nova()
	{

	}

	void Skill_Shock_Nova::Initialize(int mouseX, int mouseY, int* cxy)
	{
		damage = 0;
		backDistance = 10;
		hitbox[0] = 13;
		hitbox[1] = 13;
		hitbox[2] = 187;
		hitbox[3] = 187;
		lifeTimer = 300;
		map_collision[0] = 0;
		map_collision[1] = 0;
		map_collision[2] = 0;
		map_collision[3] = 0;
		isDelete = false;
		isStock = false;
		speed = 20;
		cast_distance = 30;
		isInit = true;
		xy[0] = cxy[0] + 35 - ani_skill[0].Width() / 2;
		xy[1] = cxy[1] + 35 - ani_skill[0].Height() / 2;

		ani_skill[0].SetDelayCount(1);
		ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[0].Width() / 2, CHARACTER_SCREEN_CENTER_Y - ani_skill[0].Height() / 2);

	}

	void Skill_Shock_Nova::LoadBitmap()
	{
		bm_skill_icon.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));


		int ani[9] = { SKILL_SHOCK_NOVA_01,SKILL_SHOCK_NOVA_02,SKILL_SHOCK_NOVA_03, SKILL_SHOCK_NOVA_04,SKILL_SHOCK_NOVA_05,SKILL_SHOCK_NOVA_06,SKILL_SHOCK_NOVA_07 ,SKILL_SHOCK_NOVA_08 ,SKILL_SHOCK_NOVA_09};

		for (int i = 0; i < 9; i++)
			ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));

	}

	void Skill_Shock_Nova::OnMove(int *cxy, GameMap *map)
	{

		if (lifeTimer == 0 ) //時間到
		{
			isDelete = true;
		}
		
		lifeTimer--;
		if (!isInit)
		{
			damage = 20;
			ani_skill[0].OnMove();
		}
		isInit = false;		


	}

	void Skill_Shock_Nova::OnShow()
	{
		if (!isDelete)
		{
			if (!ani_skill[0].IsFinalBitmap() && ani_skill[0].GetCurrentBitmapNumber()!=0)
				ani_skill[0].OnShow();
			else if(ani_skill[0].GetCurrentBitmapNumber() != 0)
				isDelete = true;

		}
	}


}