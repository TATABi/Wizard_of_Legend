#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"

namespace game_framework {
	class Enemy {
	public:
		Enemy(int, int);
		void Initialize(int, int);
		void LoadBitmap();
		//void OnMove(int, int, vector<Skill>);		//傳入現在場上所有由主角發出的魔法
		void OnMove(int, int);		//傳入現在場上所有由主角發出的魔法
		void OnShow();		//傳入角色座標
	private:
		CMovingBitmap bm_stand;
		int map_x;	//x座標
		int map_y;	//y座標
		const int collision_damage[4] = { 0, 0, 34, 57 };
		const int collision_move[4] = { 8, 41, 16, 16 };		//只有和地圖物件是使用此碰撞窗
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;

	};

}

#endif