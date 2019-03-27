#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"

namespace game_framework {
	class Enemy {
	public:
		Enemy(int, int);
		void Initialize(int, int);
		void LoadBitmap();
		//void OnMove(int, int, vector<Skill>);		//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		void OnMove(int, int);		//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		void OnShow();		//�ǤJ����y��
	private:
		CMovingBitmap bm_stand;
		int map_x;	//x�y��
		int map_y;	//y�y��
		const int collision_damage[4] = { 0, 0, 34, 57 };
		const int collision_move[4] = { 8, 41, 16, 16 };		//�u���M�a�Ϫ���O�ϥΦ��I����
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;

	};

}

#endif