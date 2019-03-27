#ifndef SKILL_FIREBALL_H
#define SKILL_FIREBALL_H
#include "Skill.h"
namespace game_framework {
	//skill template class
	class Skill_FireBall : public Skill
	{
	public:
		Skill_FireBall(int, int);
		void OnMove() override;
		void OnShow() override;
		void LoadBitmap() override;
		void Initialize() override;
	};
}
#endif