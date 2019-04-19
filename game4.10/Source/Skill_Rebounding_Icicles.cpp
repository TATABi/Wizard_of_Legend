#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Rebounding_Icicles.h"


namespace game_framework
{
	Skill_Rebounding_Icicles::Skill_Rebounding_Icicles(int mousreX, int mouseY, int *cxy) 		//中心往滑鼠位置的向量
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();
		

	}

	Skill_Rebounding_Icicles::~Skill_Rebounding_Icicles()
	{
	
	}

	void Skill_Rebounding_Icicles::Initialize(int mouseX, int mouseY, int* cxy)
	{
		damage = 20;
		backDistance = 10;
		hitbox[0] = 32;
		hitbox[1] = 10;
		hitbox[2] = 36;
		hitbox[3] = 77;
		lifeTimer = 180;
		map_collision[0] = 35;
		map_collision[1] = 45;
		map_collision[2] = 6;
		map_collision[3] = 5;
		isDelete = false;
		isStock = false;
		speed = 20;
		cast_distance = 30;
		
		isInit[0] = isInit[1] = isInit[2] = isInit[3] = true;
		ani_skill[0].SetDelayCount(1);
		ani_skill[1].SetDelayCount(1);
		ani_skill[2].SetDelayCount(1);
		ani_skill[3].SetDelayCount(1);

		int tempX = mouseX - CHARACTER_SCREEN_CENTER_X;		//螢幕中心到滑鼠向量
		int tempY = mouseY - CHARACTER_SCREEN_CENTER_Y;

		float unitVec = (float)(sqrt(pow(tempX, 2) + pow(tempY, 2)));

		dx = (mouseX - CHARACTER_SCREEN_CENTER_X) * speed / unitVec;
		dy = (mouseY - CHARACTER_SCREEN_CENTER_Y) * speed / unitVec;

		xy[0] = cxy[0] + (mouseX - CHARACTER_SCREEN_CENTER_X) * cast_distance / unitVec;
		xy[1] = cxy[1] + (mouseY - CHARACTER_SCREEN_CENTER_Y) * cast_distance / unitVec;

		rx = cxy[0] + (mouseX - CHARACTER_SCREEN_CENTER_X) * cast_distance / unitVec;
		ry = cxy[1] + (mouseY - CHARACTER_SCREEN_CENTER_Y) * cast_distance / unitVec;

	}

	void Skill_Rebounding_Icicles::LoadBitmap()
	{
		bm_skill_icon.LoadBitmap(SKILL_ICON_REBOUNDING_ICICLES, RGB(50, 255, 0));

		
		int ani[10] = { SKILL_REBOUNDING_ICICLES_01,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_02,SKILL_REBOUNDING_ICICLES_03,
					   SKILL_REBOUNDING_ICICLES_03,SKILL_REBOUNDING_ICICLES_03,SKILL_REBOUNDING_ICICLES_04, SKILL_REBOUNDING_ICICLES_04, SKILL_REBOUNDING_ICICLES_04 };
		
		for (int i = 0; i < 10; i++)
			ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));
	
		for (int i = 0; i < 10; i++)
			ani_skill[1].AddBitmap(ani[i], RGB(50, 255, 0));

		for (int i = 0; i < 10; i++)
			ani_skill[2].AddBitmap(ani[i], RGB(50, 255, 0));

		for (int i = 0; i < 10; i++)
			ani_skill[3].AddBitmap(ani[i], RGB(50, 255, 0));

		
	}

	void Skill_Rebounding_Icicles::OnMove(int *cxy, GameMap *map)
	{
		
		if (map->GetMapStatus(xy[0] + map_collision[0], xy[1] + map_collision[1]) == -1 ||
			map->GetMapStatus(xy[0] + map_collision[0] + map_collision[2], xy[1] + map_collision[1]) == -1 ||
			map->GetMapStatus(xy[0] + map_collision[0], xy[1] + map_collision[1] + map_collision[3]) == -1 ||
			map->GetMapStatus(xy[0] + map_collision[0] + map_collision[2], xy[1] + map_collision[1] + map_collision[3]) == -1 )
		{
			isStock = true;
		}


		if (lifeTimer == 0 ) //時間到 or 碰到牆
		{
			isDelete = true;
		}
		else
		{
			lifeTimer--;

			if (ani_skill[3].GetCurrentBitmapNumber() < 2 && !isStock)
			{
				rx += dx;
				ry += dy;
				xy[0] = (int)rx;
				xy[1] = (int)ry;
			}

			///////////////////////////////////  1
			if (isInit[0])
			{
				ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[0].Width() / 2 + xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[0].Height() / 2 + xy[1] - cxy[1]);
				ani_skill[0].OnMove();
				isInit[0] = false;
				ani_1[0] = xy[0];
				ani_1[1] = xy[1];
			}
			else if (isInit[0] == false && !ani_skill[0].IsFinalBitmap())
			{
				ani_skill[0].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[0].Width() / 2 + ani_1[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[0].Height() / 2 + ani_1[1] - cxy[1]);
				ani_skill[0].OnMove();
			}

			/////////////////////////////////   2

			if (ani_skill[0].GetCurrentBitmapNumber() == 4)
			{
				ani_skill[1].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[1].Width() / 2 + xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[1].Height() / 2 + xy[1] - cxy[1]);
				ani_skill[1].OnMove();
				isInit[1] = false;
				ani_2[0] = xy[0];
				ani_2[1] = xy[1];
			}
			else if (isInit[1] == false && !ani_skill[1].IsFinalBitmap())
			{
				ani_skill[1].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[1].Width() / 2 + ani_2[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[1].Height() / 2 + ani_2[1] - cxy[1]);
				ani_skill[1].OnMove();
			}

			//////////////////////////////////  3
			if (ani_skill[1].GetCurrentBitmapNumber() == 4)
			{
				ani_skill[2].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[2].Width() / 2 + xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[2].Height() / 2 + xy[1] - cxy[1]);
				ani_skill[2].OnMove();
				isInit[2] = false;
				ani_3[0] = xy[0];
				ani_3[1] = xy[1];
			}
			else if (isInit[2] == false && !ani_skill[2].IsFinalBitmap())
			{
				ani_skill[2].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[2].Width() / 2 + ani_3[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[2].Height() / 2 + ani_3[1] - cxy[1]);
				ani_skill[2].OnMove();
			}

			/////////////////////////////////  4

			if (ani_skill[2].GetCurrentBitmapNumber() == 4)
			{
				ani_skill[3].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[3].Width() / 2 + xy[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[3].Height() / 2 + xy[1] - cxy[1]);
				ani_skill[3].OnMove();
				isInit[3] = false;
				ani_4[0] = xy[0];
				ani_4[1] = xy[1];
			}
			else if (isInit[3] == false && !ani_skill[3].IsFinalBitmap())
			{
				ani_skill[3].SetTopLeft(CHARACTER_SCREEN_CENTER_X - ani_skill[3].Width() / 2 + ani_4[0] - cxy[0], CHARACTER_SCREEN_CENTER_Y - ani_skill[3].Height() / 2 + ani_4[1] - cxy[1]);
				ani_skill[3].OnMove();

			}

		}
		
	}

	void Skill_Rebounding_Icicles::OnShow()
	{
		if (!isDelete)
		{
			if(!ani_skill[0].IsFinalBitmap())
				ani_skill[0].OnShow();
			
			if (!ani_skill[1].IsFinalBitmap() && !isInit[1])
				ani_skill[1].OnShow();
			
			if (!ani_skill[2].IsFinalBitmap() && !isInit[2])
				ani_skill[2].OnShow();

			if (!ani_skill[3].IsFinalBitmap() && !isInit[3])
				ani_skill[3].OnShow();
			
		}
	}

	
}