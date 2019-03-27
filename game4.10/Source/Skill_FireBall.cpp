#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill_FireBall.h"

namespace game_framework
{
	Skill_FireBall::Skill_FireBall(int x, int y) : Skill(x, y) 
	{	
		Initialize();
	}

	void Skill_FireBall::LoadBitmap()
	{
		bm_skill.LoadBitmap(Skill_FireBall_Temp, RGB(50, 255, 0));
	}

	void Skill_FireBall::OnMove()
	{
		bm_skill.SetTopLeft(vecX,vecY);		//計算atan取得角度，再用角度去移動
	}

	void Skill_FireBall::OnShow()
	{
		bm_skill.ShowBitmap();
	}

	void Skill_FireBall::Initialize()
	{
		damage = 20;
		backDistance = 10;
		hitbox_X = 50;
		hitbox_Y = 30; 
		timer = 180;
		isDelete = false;
	}
}
