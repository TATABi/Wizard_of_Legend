#ifndef SKILL_H
#define SKILL_H

namespace game_framework {
	class Skill{
	public :
		Skill() {};
	protected:
		CAnimation ani_character_skill;
		CMovingBitmap bm_skill;
		bool isPerform;				//�O�_���b�I��
		bool isEquip;				//�O�_�˳Ƥ�
		bool isRecover;				//����O�_�ಾ��
		int damage;					//�ˮ`�q
		int recoverTime;			//�w���ɶ�
		double coolDownTime;		//�N�o�ɶ�
	};


}

#endif