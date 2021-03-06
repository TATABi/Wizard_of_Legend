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
		void PlayDeadAudio();					//播放死亡音效
	private:
		CMovingBitmap _bm_hp_bar;				//HP條
		CMovingBitmap _bm_shadow;				//隱身
		int _attack_delay_counter;				//角色經過怪物身邊時怪物需要反映時間才能做攻擊動作
		int _sx, _sy;							//螢幕座標，用於及時運算HP條用
		int _skill_counter;						//使用技能間的間隔
		bool _isInvisible;						//是否隱身
	};
}

#endif