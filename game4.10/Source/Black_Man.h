#ifndef BLACK_MAN_H
#define BLACK_MAN_H

#include "Enemy.h"

namespace game_framework {
	class Black_Man : public Enemy {
	public:
		Black_Man(int, int, int, GameMap*);
		~Black_Man();
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();			
		void Attack(int, int);
		void ResetAnimation();
		void CalculateHP();
	private:
		CMovingBitmap _bm_hp_bar;
		const int HP = 30;
		const int STEP = 5;
		const int ZONE = 30;
		const int DAMAGE = 20;
		int _attack_delay_counter = 10; //����g�L�Ǫ�����ɩǪ��ݭn�ϬM�ɶ��~�వ�����ʧ@
		
		int x, y;
	};

}


#endif