#ifndef BLOCKHEAD_H
#define BLOCKHEAD_H

#include "Enemy.h"

namespace game_framework {
	class Blockhead : public Enemy {
	public:
		Blockhead(int, int, int);
		~Blockhead();
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();
		//int Attack(int, int);
	private:
		const int HP = 10000;
		const int STEP = 0;
		const int ZONE = 0;
		const int DAMAGE = 0;
	};

}


#endif
