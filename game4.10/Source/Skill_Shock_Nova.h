#ifndef SKILL_SHOCK_NOVA_H
#define SKILL_SHOCK_NOVA_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Shock_Nova : public Skill
	{
	public:
		Skill_Shock_Nova(int, int, float*);		//�ǤJ�ƹ��y�СB����y��	
		void Initialize(int, int, float*);		//��l�Ƽƭ�
		void LoadBitmap();						//�פJ�Ϥ�
		void OnMove(int *, GameMap *);			//�]�w�ޯ�y�СB����
		int GetDamage(Enemy *);					//�����Ǫ��P�ޯ�I��
		void OnShow();							//��ܧޯ�
	private:
		bool _isInit;
		int _delay_counter;						//�ΨӼ�����I��Y��ɪ��ʵe
		int _re_attack_counter;					//���Ƨ�����counter
		int _time;								//�I��ޯ઺���סA�ɶ����ޯೣ���ġA���Ƽ���ʵe
	};
}

#endif