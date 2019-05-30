#ifndef BLOCKHEAD_H
#define BLOCKHEAD_H

#include "Enemy.h"

namespace game_framework {
	class Blockhead : public Enemy {
	public:
		Blockhead(int, int, int, GameMap*);
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();
	};

}


#endif
