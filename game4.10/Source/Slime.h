#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"

namespace game_framework{
	class Slime : public Enemy {
	public:
		Slime(int, int, int, GameMap*);
		void Init();							//初始化
		void LoadEnemyBitmap();					//載入Slime圖片
		void Move(int, int);
		void OnShow();
		void Attack(float, float);				//攻擊
		void CalculateHP();						//計算血量
		void PlayDeadAudio();					//播放死亡聲音		
	private:
		CMovingBitmap _bm_hp_bar;				//血條
		int _attack_delay_counter;				//角色經過怪物身邊時怪物需要反映時間才能做攻擊動作
		int _sx, _sy;							//Slime螢幕位置
	};
}

#endif