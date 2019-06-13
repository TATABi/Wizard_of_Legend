#ifndef BLOCKHEAD_H
#define BLOCKHEAD_H
#include "Enemy.h"

namespace game_framework {
	class Blockhead : public Enemy {
	public:
		Blockhead(int, int, int, GameMap*);		//設定位置、區域、地圖
		void Init();							//初始化
		void LoadEnemyBitmap();					//匯入圖片
		void Move(int, int);					//移動
		void OnShow();							//顯示圖片
		vector<Reward*> CreateReward();			//產生掉落物
	};
}

#endif