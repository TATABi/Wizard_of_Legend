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
		int Collision(int *, const int *, int, int); // 1 發生碰撞 2 發生碰撞而且被碰撞物體撞到牆 3 沒撞到
		void OnMove(int, int, vector<Skill*>&);		//傳入現在場上所有由主角發出的魔法
		void OnShow();		//傳入角色座標
		bool IsLive();
	private:
		CMovingBitmap _bm_stand;
		int _hp;
		const int _collision_damage[4] = { 0, 0, 34, 57 };
		const int _collision_move[4] = { 8, 41, 16, 16 };		//只有和地圖物件是使用此碰撞窗

	};

}

#endif