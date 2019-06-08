#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"

namespace game_framework{
	class Slime : public Enemy {
	public:
		Slime(int, int, int, GameMap*);
		void Init();
		void Reset();
		void LoadEnemyBitmap();
		void Move(int, int);
		void OnShow();
		void Attack(float, float);
		void ResetAnimation();
		void CalculateHP();
	private:
		CMovingBitmap _bm_hp_bar;
		int _attack_delay_counter; //����g�L�Ǫ�����ɩǪ��ݭn�ϬM�ɶ��~�వ�����ʧ@
		int _sx, _sy;
	};
}

#endif