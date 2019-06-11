#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

namespace game_framework {
	class Boss : public Enemy {
	public:
		Boss(int, int, int, GameMap*);			//設定位置、區域、地圖
		void Init();							//初始化
		void LoadEnemyBitmap();					//匯入圖片
		void Move(int, int);					//移動
		void OnShow();							//顯示圖片
		void Attack(float, float);				//攻擊角色
		void CalculateHP();						//計算Enemy血量&顯示
	private:
		CMovingBitmap _bm_hp_bar;
		int _attack_delay_counter;				//角色經過怪物身邊時怪物需要反映時間才能做攻擊動作
		int _sx, _sy;
		int _skill_counter;
		bool _isUsingSkill;
	};
}

#endif