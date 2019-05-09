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
		void OnMove(int, int, vector<Skill*>&);		//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		bool IsLive();
		bool CanAchieved(int, int);						//�P�_��_����
		void NotifyCharge();
		int Area();
		void SetXY(int, int);
		int* GetEnemyXY();
		int* GetCollisionMove();
		virtual void Init() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Move(int, int) = 0;
		virtual void OnShow() = 0;
		virtual void Reset() = 0;
	//	virtual void Attack() = 0;
	protected:
		enum STATE {
			ATTACKING,
			CHARGING,
			RESET,
			NOTHING
		};

		enum DIRECTION {
			LEFT,
			RIGHT
		};

		STATE _state;
		DIRECTION _direction;
		void MoveToTarget(int, int);
		int _hp, _step, _zone;
		int _area;
		int _ori_x, _ori_y;
		int _target_x, _target_y;
		int _collision_damage[4] = { 0, 0, 34, 57 };
		int _collision_move[4] = { 8, 41, 16, 16 };		//�u���M�a�Ϫ���O�ϥΦ��I����
		bool _is_x_arrive;
		bool _is_y_arrive;
		bool _is_detour, _is_left, _is_right, _is_up, _is_down;
		bool _neighbor[4];	// �W�U���k
		int _detour_time;
		//CMovingBitmap _bm_stand;
		int _damage;


	};
}

#endif