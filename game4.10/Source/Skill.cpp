#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Skill.h"
#include "Enemy.h"

namespace game_framework
{
	Skill::Skill(){}

	Skill::~Skill(){}

	bool Skill::IsDelete()
	{
		return _isDelete;
	}

	void Skill::Init()
	{
		_isDelete = false;
	}

	int* Skill::GetHitbox()
	{
		return _hitbox;
	}

	bool Skill::AttackedThisEnemy(Enemy* enemy)
	{
		bool isExist = false;

		for (int i = 0; i < _enemyList.size(); i++)
		{
			if (_enemyList[i] == enemy)
			{
				isExist = true;
				break;
			}
		}
		
		if (isExist)
		{
			return false;
		}
		else
		{
			_enemyList.push_back(enemy);
			return true;
		}
	}
}