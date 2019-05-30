#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework 
{
	class Enemy;
	class GameMap;

	class Skill:public Layer{
	public :
		Skill();
		void Init();								//初始化
		bool IsDelete();							//得知是否該刪除
		bool AttackedThisEnemy(Enemy*);				//將怪物加入已攻擊列表中
		void RefreshEnemyList();					//重製怪物表單 (讓怪物可以被重複攻擊)
		virtual int GetDamage(Enemy *) = 0;
		virtual void OnMove(float *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, float*) = 0;	
	protected:
		CAnimation _ani_skill[8];					//技能動畫
		float _dx, _dy;								//技能的移動向量
		int _cast_distance;							//技能施放時與角色的距離
		float _rx, _ry;								//技能實際飛行位置(用來修正float int 轉換出現的抖動)
		int _speed;									//移動速度
		int _lifeTime;								//存活時間
		int _damage;								//傷害量
		int _backDistance;							//擊退距離
		int _hitbox[4];						        //hitBox 左上角座標 and l,w
		int _map_collision[4];						//跟地圖的碰撞判定
		bool _isDelete;								//是否該刪除
		bool _isStock;								//卡到牆
		vector<Layer *> _enemyList;					//存放已經攻擊過的怪物
	};
}

#endif