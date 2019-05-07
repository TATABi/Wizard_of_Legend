#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"
#include "Layer.h"
#include "A_Star.h"

namespace game_framework {
	class Enemy : public Layer {
		enum STATE {
			ATTACKING,
			CHARGING,
			RESET
		};
	public:
		Enemy(int, int, int, int);
		~Enemy();
		void Initialize(int, int);
		void LoadBitmap();		
		int Collision(int *, const int *, int, int); // 1 發生碰撞 2 發生碰撞而且被碰撞物體撞到牆 3 沒撞到
		void OnMove(int, int, vector<Skill*>&);		//傳入現在場上所有由主角發出的魔法
		void OnShow();								//傳入角色座標
		bool IsLive();
		bool IsAttackZone(int, int);				//判斷是否進入緊戒區
		bool IsMove(int, int);						//判斷能否移動
		void NotifyCharge();
		int Area();
	private:
		void MoveToTarget(int, int);
		CMovingBitmap _bm_stand;
		int _hp, _step, _area, _ori_x, _ori_y, _zone, _target_x, _target_y;
		const int _collision_damage[4] = { 0, 0, 34, 57 };
		const int _collision_move[4] = { 8, 41, 16, 16 };		//只有和地圖物件是使用此碰撞窗
		bool _is_x_arrive;
		bool _is_y_arrive;
		STATE _state;
		bool _is_detour, _is_left, _is_right, _is_up, _is_down;
		bool _neighbor[4];	// 上下左右
		int _detour_time;
	};
}

#endif