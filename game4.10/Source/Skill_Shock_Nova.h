#ifndef SKILL_SHOCK_NOVA_H
#define SKILL_SHOCK_NOVA_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework {

	class Skill_Shock_Nova : public Skill
	{
	public:
		Skill_Shock_Nova(int, int, int*);
		~Skill_Shock_Nova();
		void OnMove(int *, GameMap *);
		void OnShow();
		void LoadBitmap();
		void Initialize(int, int, int*);
	private:
		bool _isInit;
		int _counter;	//用來播角色施放即能時的動畫
	};
}
#endif