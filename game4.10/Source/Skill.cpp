#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill.h"


namespace game_framework
{
	Skill::Skill(int mouseX, int mouseY)
	{
		this->vecX = mouseX;
		this->vecY = mouseY;
	}
	Skill::~Skill()
	{
	}

	bool Skill::GetIsDelete()
	{
		return isDelete;
	}
}