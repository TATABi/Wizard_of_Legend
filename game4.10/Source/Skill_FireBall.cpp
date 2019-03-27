#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill_FireBall.h"
#include <math.h>

namespace game_framework
{
	Skill_FireBall::Skill_FireBall(int x, int y) : Skill(x, y)		//中心往滑鼠位置的向量
	{	
		Initialize();
		LoadBitmap();
	}

	Skill_FireBall::~Skill_FireBall()
	{

	}

	void Skill_FireBall::Initialize()
	{
		damage = 20;
		backDistance = 10;
		hitbox_X = 50;
		hitbox_Y = 30;
		lifeTimer = 180;
		isDelete = false;
		speed = 20;
		dx = 0;
		dy = 0;
		sx = CharacterData::characterX;
		sy = CharacterData::characterY;

	}

	void Skill_FireBall::LoadBitmap()
	{
		bm_skill.LoadBitmap(Skill_Temp, RGB(50, 255, 0));
	}

	void Skill_FireBall::OnMove()
	{
		if (lifeTimer != 0)
		{
			lifeTimer--;
			int tempX = vecX - CHARACTER_SCREEN_X;		//螢幕中心到滑鼠向量
			int tempY = vecY - CHARACTER_SCREEN_Y;
			float unitVec = sqrt(pow(tempX, 2) + pow(tempY, 2));
			float unitX = tempX * speed / unitVec;		//單位向量
			float unitY = tempY * speed / unitVec;
			dx += unitX;		//累積移動距離
			dy += unitY;
			mx = sx + dx;		//更新自身所在地圖位置
			my = sy + dy;

			//螢幕中心 + (角色施放時所在座標-目前所在座標) + 累積移動距離
			bm_skill.SetTopLeft(CHARACTER_SCREEN_X + dx + sx - CharacterData::characterX , CHARACTER_SCREEN_Y  + dy + sy - CharacterData::characterY);		
		}
		else
		{
			isDelete = true;
		}
	} 

	void Skill_FireBall::OnShow()
	{
		if (!isDelete)
		{
			bm_skill.ShowBitmap();
		}
	}
}
