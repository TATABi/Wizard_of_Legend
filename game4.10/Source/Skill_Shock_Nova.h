#ifndef SKILL_SHOCK_NOVA_H
#define SKILL_SHOCK_NOVA_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework {

	class Skill_Shock_Nova : public Skill
	{
	public:
		Skill_Shock_Nova(int, int, float*);
		~Skill_Shock_Nova();
		void OnMove(int *, GameMap *);
		int GetDamage(Enemy *);
		void OnShow();
		void LoadBitmap();
		void Initialize(int, int, float*);
		int* GetHitbox();
	private:
		bool _isInit;
		int _delay_counter;	//用來播角色施放即能時的動畫
		int _re_attack_counter;	//重複攻擊的counter
		int _time;		//施放技能的長度，時間內技能都有效，重複播放動畫
		int RE = 6;
	};
}
#endif