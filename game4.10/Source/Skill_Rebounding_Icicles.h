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
		bool isInit[4];
		int ani_1[2], ani_2[2], ani_3[2], ani_4[2];
		
	};
}
#endif