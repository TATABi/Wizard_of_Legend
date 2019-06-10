#ifndef BLOCKHEAD_H
#define BLOCKHEAD_H

#include "Enemy.h"

namespace game_framework {
	class Blockhead : public Enemy {
	public:
		Blockhead(int, int, int, GameMap*);
		void Init();
		void Reset();
		void LoadEnemyBitmap();
		void Move(int, int);
		void OnShow();
		vector<Reward*> CreateReward();
	};

}


#endif
