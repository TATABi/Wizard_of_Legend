#ifndef REWARD_H
#define REWARD_H

#include "Layer.h"

namespace game_framework {

	class GameMap;

	class Reward : public Layer {

	public:
		Reward(float, float, GameMap*);					//�Ǫ���m�B�a��
		virtual void LoadBitmap() = 0;
		void OnMove();
		void OnShow();
		void MoveTarget(float, float);					//���ʥت��a
		bool IsDelete();								//�P�_�O�_�n�R��
		virtual void Initialize(float, float) = 0;
		virtual void Effect() = 0;						//Ĳ�o�ĪG�A��concrete class override
		void SetRandomPosition();						//�N_targetX�B_targetY�]�w���P��@�w�Z�������y��
	protected:
		enum STATE {
			BORN,
			EATEN,
			MOVE,
			IDLE
		};
		int _range_eat, _range_position, _time, _targetX, _targetY;
		int _value = 1;
		int _move_counter = 30;					//�קK�]�����Ⲿ�ʡA�y��reward�@���S��k���ʨ쨤�⨭�W
		int _hitbox[4] = { 0 };
		CMovingBitmap _bm_reward;
		bool _isShow, _isUp;
		GameMap *_map;
		bool IsEaten();
		bool IsTargetPosition(float, float);
		STATE _state;
		int delay_counter = 20;					//������A���n���������@�X�{�N�i�H�Y
	};
}
#endif