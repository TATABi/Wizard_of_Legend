#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"

namespace game_framework{
	class Slime : public Enemy {
	public:
		Slime(int, int, int, GameMap*);
		void Init();							//��l��
		void LoadEnemyBitmap();					//���JSlime�Ϥ�
		void Move(int, int);
		void OnShow();
		void Attack(float, float);				//����
		void CalculateHP();						//�p���q
		void PlayDeadAudio();					//���񦺤`�n��		
	private:
		CMovingBitmap _bm_hp_bar;				//���
		int _attack_delay_counter;				//����g�L�Ǫ�����ɩǪ��ݭn�ϬM�ɶ��~�వ�����ʧ@
		int _sx, _sy;							//Slime�ù���m
	};
}

#endif