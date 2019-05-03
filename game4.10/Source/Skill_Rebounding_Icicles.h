#ifndef SKILL_REBOUNDING_ICICLES_H
#define SKILL_REBOUNDING_ICICLES_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework {

	class Skill_Rebounding_Icicles : public Skill
	{
	public:
		Skill_Rebounding_Icicles(int, int, int*);
		~Skill_Rebounding_Icicles();
		void OnMove(int *, GameMap *);
		void OnShow();
		void LoadBitmap();
		void Initialize(int, int, int*);
	private:
		bool _isInit[4];		//是否第一張動畫
		int _ani_1[2], _ani_2[2], _ani_3[2], _ani_4[2];		//技能的位置
		
	};
}
#endif