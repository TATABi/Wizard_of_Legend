#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"
#include "Layer.h"

namespace game_framework {
	class Enemy : public Layer {
	public:
		Enemy(int, int);
		void Initialize(int, int);
		void LoadBitmap();		
		int Collision(int *, const int *, int, int); // 1 �o�͸I�� 2 �o�͸I���ӥB�Q�I�����鼲���� 3 �S����
		void OnMove(int, int, vector<Skill*>&);		//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		void OnShow();		//�ǤJ����y��
		bool IsLive();
	private:
		CMovingBitmap _bm_stand;
		int _hp;
		const int _collision_damage[4] = { 0, 0, 34, 57 };
		const int _collision_move[4] = { 8, 41, 16, 16 };		//�u���M�a�Ϫ���O�ϥΦ��I����

	};

}

#endif