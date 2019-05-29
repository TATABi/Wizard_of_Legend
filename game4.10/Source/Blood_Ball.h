#ifndef BLOOD_BALL_H
#define BLOOD_BALL_H
#include "Reward.h"
namespace game_framework {
	class GameMap;

	class BloodBall : public Reward {
	public:
		BloodBall(float, float, GameMap*);
		void LoadBitmap();
		void Initialize(float, float);
		void Effect();	
		void MoveTarget(float, float);
		void SetRandomPosition();
	private:
		//_hitbox[4] = {3, 3, 13, 13};
		GameMap *_map;
		
	};
}
#endif