#ifndef SKILL_REBOUNDING_ICICLES_H
#define SKILL_REBOUNDING_ICICLES_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Rebounding_Icicles : public Skill
	{
	public:
		Skill_Rebounding_Icicles(int, int, float*);			//�ǤJ�ƹ��y�СB����y��
		void Initialize(int, int, float*);					//��l�Ƽƭ�
		void LoadBitmap();									//�פJ�Ϥ�
		void OnMove(float *, GameMap *);					//�]�w�ޯ�y�СB����
		int GetDamage(Enemy *);								//�����Ǫ��P�ޯ�I��
		void OnShow();										//��ܧޯ�
	private:
		bool _isInit[4];									//�O�_�Ĥ@�i�ʵe
		int _ani_1[2], _ani_2[2], _ani_3[2], _ani_4[2];		//�ޯ઺��m
	};
}

#endif