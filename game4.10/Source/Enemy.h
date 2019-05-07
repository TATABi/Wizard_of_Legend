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
		int Collision(int *, const int *, int, int); // 1 �o�͸I�� 2 �o�͸I���ӥB�Q�I�����鼲���� 3 �S����
		void OnMove(int, int, vector<Skill*>&);		//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		void OnShow();								//�ǤJ����y��
		bool IsLive();
		bool IsAttackZone(int, int);				//�P�_�O�_�i�J��ٰ�
		bool IsMove(int, int);						//�P�_��_����
		void NotifyCharge();
		int Area();
	private:
		void MoveToTarget(int, int);
		CMovingBitmap _bm_stand;
		int _hp, _step, _area, _ori_x, _ori_y, _zone, _target_x, _target_y;
		const int _collision_damage[4] = { 0, 0, 34, 57 };
		const int _collision_move[4] = { 8, 41, 16, 16 };		//�u���M�a�Ϫ���O�ϥΦ��I����
		bool _is_x_arrive;
		bool _is_y_arrive;
		STATE _state;
		bool _is_detour, _is_left, _is_right, _is_up, _is_down;
		bool _neighbor[4];	// �W�U���k
		int _detour_time;
	};
}

#endif