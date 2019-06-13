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
	Skill::Skill() { Init(); }

	void Skill::Init()
	{
		_isDelete = false;
	}

	bool Skill::IsDelete()
	{
		return _isDelete;
	}

	bool Skill::AttackedThisEnemy(Enemy* enemy)
	{
		bool isExist = false;
		//將怪物加入已攻擊列表
		for (int i = 0; i < _enemyList.size(); i++)
		{
			if (_enemyList[i] == enemy)
			{
				isExist = true;
				break;
			}
		}
		if (isExist)
			return false;
		else
		{
			_enemyList.push_back(enemy);
			return true;
		}
	}

	void Skill::RefreshEnemyList()
	{
		_enemyList.clear();
	}
}