#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"
#include "Layer.h"

namespace game_framework {
	class Enemy : public Layer {
		
	public:
		Enemy(int, int, int, int);
		~Enemy();
		void Initialize(int, int);	
		void OnMove(int, int, vector<Skill*>&);		//傳入現在場上所有由主角發出的魔法
		bool IsLive();
		bool CanAchieved(int, int);						//判斷能否移動
		void NotifyCharge();
		int Area();
		void SetXY(int, int);
		int* GetPosition();
		int* GetCollisionMove();
		int* GetHitbox();
		void LoadBitmap();
		bool IsInAttackZone(int, int);

		virtual void Init() = 0;
		virtual void LoadBitmap_2() = 0;
		virtual void Move(int, int) = 0;
		virtual void OnShow() = 0;
		virtual void Reset() = 0;
		

	//	virtual void Attack() = 0;
	protected:
		enum STATE {
			ATTACKING,
			CHARGING,
			RESET,
			NOTHING,
			HIT_RECOVER
		};

		enum DIRECTION {
			LEFT,
			RIGHT
		};

		STATE _state;
		STATE _pre_state;
		DIRECTION _direction;
		void MoveToTarget(int, int);
		int _hp, _step, _zone;
		int _area;
		int _ori_x, _ori_y;
		int _target_x, _target_y;
		int _hitbox[4] = { 0 }; // { 0, 0, 34, 57 };
		int _collision_move[4] = { 0 }; // { 8, 41, 16, 16 };		//只有和地圖物件是使用此碰撞窗
		bool _is_x_arrive;
		bool _is_y_arrive;
		bool _is_detour, _is_left, _is_right, _is_up, _is_down;
		bool _neighbor[4];	// 上下左右
		int _detour_time;
		int _damage;
		int _attack_counter;
		int _hit_recover_counter;
		bool _hit_recover_flag;
		CMovingBitmap _bm_stand_left, _bm_stand_right;
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;
		CAnimation _ani_hurt;
		CAnimation _ani_left, _ani_right;
		CAnimation _ani_attack_left, _ani_attack_right;
	};
}

#endif