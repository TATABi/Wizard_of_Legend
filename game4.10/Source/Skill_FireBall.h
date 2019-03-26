#ifndef SKILL_FIREBALL_H
#define SKILL_FIREBALL_H
#include "Skill.h"
namespace game_framework {
	//skill template class
	class Skill_FireBall : public Skill
	{
	public:
		Skill_FireBall(int, int);
		~Skill_FireBall();
		void OnMove();
		void OnShow();
		void LoadBitmap();
		void Initialize();
	};
}
#endif