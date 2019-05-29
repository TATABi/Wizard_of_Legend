#ifndef REWARD_H
#define REWARD_H

#include "Layer.h"

namespace game_framework {

	class GameMap;

	class Reward : public Layer {

	public:
		Reward(float, float, GameMap*);
		virtual void LoadBitmap() = 0;
		void OnMove();
		void OnShow();
		virtual void Initialize(float, float) = 0;
		virtual void Effect() = 0;
		virtual void MoveTarget(float, float) = 0;
		virtual void SetRandomPosition() = 0;
	protected:

		enum STATE {
			BORN,
			EATEN,
			MOVE,
			IDLE
		};

		int _range_eat, _range_position, _speed, _targetX, _targetY;
		int _value = 1;
		int _hitbox[4] = { 0 };
		CMovingBitmap _bm_reward;
		bool _isShow, _isUp;
		GameMap *_map;
		bool IsEaten();
		bool IsTargetPosition(float, float);
		STATE _state;
	};
}
#endif