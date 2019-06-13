#ifndef BLOCKHEAD_H
#define BLOCKHEAD_H
#include "Enemy.h"

namespace game_framework {
	class Blockhead : public Enemy {
	public:
		Blockhead(int, int, int, GameMap*);		//�]�w��m�B�ϰ�B�a��
		void Init();							//��l��
		void LoadEnemyBitmap();					//�פJ�Ϥ�
		void Move(int, int);					//����
		void OnShow();							//��ܹϤ�
		vector<Reward*> CreateReward();			//���ͱ�����
	};
}

#endif