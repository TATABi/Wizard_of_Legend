#ifndef REWARD_H
#define REWARD_H

#include "Layer.h"

namespace game_framework {

	class GameMap;

	class Reward : public Layer {

	public:
		Reward(float, float, GameMap*);					//怪物位置、地圖
		virtual void LoadBitmap() = 0;
		void OnMove();
		void OnShow();
		void MoveTarget(float, float);					//移動目的地
		bool IsDelete();								//判斷是否要刪除
		virtual void Initialize(float, float) = 0;
		virtual void Effect() = 0;						//觸發效果，由concrete class override
		void SetRandomPosition();						//將_targetX、_targetY設定為周圍一定距離內的座標
	protected:
		enum STATE {
			BORN,
			EATEN,
			MOVE,
			IDLE
		};
		int _range_eat, _range_position, _time, _targetX, _targetY;
		int _value = 1;
		int _move_counter = 30;					//避免因為角色移動，造成reward一直沒辦法移動到角色身上
		int _hitbox[4] = { 0 };
		CMovingBitmap _bm_reward;
		bool _isShow, _isUp;
		GameMap *_map;
		bool IsEaten();
		bool IsTargetPosition(float, float);
		STATE _state;
		int delay_counter = 20;					//做延遲，不要讓掉落物一出現就可以吃
	};
}
#endif