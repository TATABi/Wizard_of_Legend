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
		void MoveTarget(float, float);
		bool IsDelete();
		virtual void Initialize(float, float) = 0;
		virtual void Effect() = 0;
		void SetRandomPosition();
	protected:

		enum STATE {
			BORN,
			EATEN,
			MOVE,
			IDLE
		};

		int _range_eat, _range_position, _time, _targetX, _targetY;
		int _value = 1;
		int _move_counter = 30;
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