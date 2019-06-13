#ifndef SKILL_AIR_SPINNER_H
#define SKILL_AIR_SPINNER_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Air_Spinner : public Skill
	{
	public:
		Skill_Air_Spinner(int, int, float*);				//�ǤJ�ƹ��y�СB����y��
		void Initialize(int, int, float*);					//��l�Ƽƭ�
		void LoadBitmap();									//�פJ�Ϥ�
		void OnMove(float *, GameMap *);					//�]�w�ޯ�y�СB����
		int GetDamage(Enemy *);								//�����Ǫ��P�ޯ�I��
		void OnShow();										//��ܧޯ�
	};
}
#endif