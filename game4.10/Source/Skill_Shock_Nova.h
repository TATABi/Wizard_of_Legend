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
		int GetDamage(Enemy *);
		void OnShow();
		void LoadBitmap();
		void Initialize(int, int, int*);
	private:
		bool _isInit;
		int _counter;	//用來播角色施放即能時的動畫
		int _time;		//施放技能的長度，時間內技能都有效，重複播放動畫
	};
}
#endif