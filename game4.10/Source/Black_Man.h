#ifndef BLACK_MAN_H
#define BLACK_MAN_H

#include "Enemy.h"

namespace game_framework {
	class Black_Man : public Enemy {
	public:
		Black_Man(int, int, int);
		~Black_Man();
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();			
		//int Attack(int, int);
	private:
		const int HP = 500;
		const int STEP = 5;
		const int ZONE = 30;
		const int DAMAGE = 20;
	};

}


#endif