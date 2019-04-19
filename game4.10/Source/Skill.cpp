#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill.h"

namespace game_framework
{
	Skill::Skill()
	{

	}

	Skill::~Skill()
	{

	}

	bool Skill::IsDelete()
	{
		return isDelete;
	}

	void Skill::Init()
	{
		isDelete = false;
	}

	int* Skill::GetHitbox()
	{
		return hitbox;
	}

	int Skill::GetDamage()
	{
		return damage;
	}

	int* Skill::GetPosition()
	{
		return xy;
	}
}