#ifndef BLACK_MAN_H
#define BLACK_MAN_H

#include "Enemy.h"

namespace game_framework {
	class Black_Man : public Enemy {
	public:
		Black_Man(int, int, int, GameMap*);		//�]�w��m�B�ϰ�B�a��
		void Init();							//��l��
		void LoadEnemyBitmap();					//�פJ�Ϥ�
		void Move(int, int);					//����
		void OnShow();							//��ܹϤ�
		void Attack(float, float);				//��������
		void CalculateHP();						//�p��Enemy��q&���
	private:
		CMovingBitmap _bm_hp_bar;
		int _attack_delay_counter; //����g�L�Ǫ�����ɩǪ��ݭn�ϬM�ɶ��~�వ�����ʧ@
		int _sx, _sy;
	};
}

#endif