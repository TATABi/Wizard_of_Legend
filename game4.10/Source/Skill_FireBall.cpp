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
	Skill_FireBall::Skill_FireBall(int x, int y) : Skill(x, y)		//���ߩ��ƹ���m���V�q
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
			int tempX = vecX - CHARACTER_SCREEN_X;		//�ù����ߨ�ƹ��V�q
			int tempY = vecY - CHARACTER_SCREEN_Y;
			float unitVec = sqrt(pow(tempX, 2) + pow(tempY, 2));
			float unitX = tempX * speed / unitVec;		//���V�q
			float unitY = tempY * speed / unitVec;
			dx += unitX;		//�ֿn���ʶZ��
			dy += unitY;
			mx = sx + dx;		//��s�ۨ��Ҧb�a�Ϧ�m
			my = sy + dy;

			//�ù����� + (����I��ɩҦb�y��-�ثe�Ҧb�y��) + �ֿn���ʶZ��
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
