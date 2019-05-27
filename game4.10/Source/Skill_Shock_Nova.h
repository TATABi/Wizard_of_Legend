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
		int _delay_counter;	//�ΨӼ�����I��Y��ɪ��ʵe
		int _re_attack_counter;	//���Ƨ�����counter
		int _time;		//�I��ޯ઺���סA�ɶ����ޯೣ���ġA���Ƽ���ʵe
		int RE = 6;
	};
}
#endif