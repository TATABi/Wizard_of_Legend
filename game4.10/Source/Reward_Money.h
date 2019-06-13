#ifndef REWARD_MONEY_H
#define REWARD_MONEY_H

#include "reward.h"

namespace game_framework {

	class GameMap;

	class Reward_Money : public Reward{
	public:
		Reward_Money(float, float, GameMap*);	//生成位置、地圖
		void LoadBitmap();		
		void Initialize(float, float);
		void Effect();							//觸發效果
	private:
		//_hitbox[4] = {5, 5, 9, 9};
		GameMap *_map;
	};


}

#endif