#ifndef REWARD_DIAMOND_H
#define REWARD_DIAMOND_H

#include "Reward.h"

namespace game_framework {

	class GameMap;

	class Reward_Diamond : public Reward {
	public:
		Reward_Diamond(float, float, GameMap*);
		void LoadBitmap();
		void Initialize(float, float);
		void Effect();
	private:
		//_hitbox[4] = {6, 4, 7, 12};
		GameMap *_map;
	};
}
#endif