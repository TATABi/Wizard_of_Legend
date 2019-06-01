#ifndef BLACK_MAN_H
#define BLACK_MAN_H

#include "Enemy.h"

namespace game_framework {
	class Black_Man : public Enemy {
	public:
		Black_Man(int, int, int, GameMap*);
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();			
		void Attack(float, float);
		void ResetAnimation();
		void CalculateHP();
	private:
		CMovingBitmap _bm_hp_bar;
		int _attack_delay_counter; //角色經過怪物身邊時怪物需要反映時間才能做攻擊動作
		int _sx, _sy;
	};
}

#endif