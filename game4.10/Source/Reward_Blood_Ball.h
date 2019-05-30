#ifndef REWARD_BLOOD_BALL_H
#define REWARD_BLOOD_BALL_H

#include "Reward.h"

namespace game_framework {

	class GameMap;

	class Reward_Blood_Ball : public Reward {
	public:
		Reward_Blood_Ball(float, float, GameMap*);
		void LoadBitmap();
		void Initialize(float, float);
		void Effect();
	private:
		//_hitbox[4] = {3, 3, 13, 13};
		GameMap *_map;
	};
}
#endif