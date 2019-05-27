#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework {
	class Enemy;
	class GameMap;
	class Skill:public Layer{
	public :
		Skill();
		~Skill();
		bool IsDelete();
		void Init();
		int* GetHitbox();	
		bool AttackedThisEnemy(Enemy*);			//之後改virtual
		virtual int GetDamage(Enemy *) = 0;
		virtual void OnMove(int *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, float*) = 0;	
	protected:
		CMovingBitmap _bm_skill_icon;
		float _dx, _dy;								//技能的移動向量
		int _cast_distance;							//技能施放時與角色的距離
		float _rx, _ry;								//技能實際飛行位置(用來修正float int 轉換出現的抖動)
		int _speed;									//移動速度
		int _lifeTimer;								//存活時間
		int _damage;									//傷害量
		int _backDistance;							//擊退距離
		int _hitbox[4];						        //hitBox 左上角座標 and l,w
		int _map_collision[4];						//跟地圖的碰撞判定
		const int CHARACTER_SCREEN_CENTER_X = 320;	
		const int CHARACTER_SCREEN_CENTER_Y = 240;
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		bool _isDelete;
		bool _isStock;								//卡到牆
		CAnimation _ani_skill[8];					//技能動畫
		vector<Layer *> _enemyList;					//存放已經攻擊過的怪物
	};


}

#endif