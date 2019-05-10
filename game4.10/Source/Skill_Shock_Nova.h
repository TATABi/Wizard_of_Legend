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
		//int GetDamage(Layer *);
		void OnShow();
		void LoadBitmap();
		void Initialize(int, int, int*);
		int* GetPosition();
		int* GetHitbox();
	private:
		bool _isInit;
		int _counter;	//�ΨӼ�����I��Y��ɪ��ʵe
		int _time;		//�I��ޯ઺���סA�ɶ����ޯೣ���ġA���Ƽ���ʵe
	};
}
#endif