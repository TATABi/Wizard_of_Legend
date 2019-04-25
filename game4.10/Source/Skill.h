#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework {
	class GameMap;
	class Skill:public Layer{
	public :
		Skill();
		~Skill();
		bool IsDelete();
		void Init();
		int* GetHitbox();
		int GetDamage();
		int* GetPosition();
		virtual void OnMove(int *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, int*) = 0;
	protected:
		CMovingBitmap bm_skill_icon;
		float dx, dy;								//技能的移動向量
		int cast_distance;							//技能施放時與角色的距離
		float rx, ry;								//技能實際飛行位置(用來修正float int 轉換出現的抖動)
		int speed;									//移動速度
		int lifeTimer;								//存活時間
		int damage;									//傷害量
		int backDistance;							//擊退距離
		int hitbox[4];						        //hitBox 左上角座標 and l,w
		int map_collision[4];						//跟地圖的碰撞判定
		const int CHARACTER_SCREEN_CENTER_X = 320;	
		const int CHARACTER_SCREEN_CENTER_Y = 240;
		bool isDelete;
		bool isStock;								//卡到牆
		CAnimation ani_skill[8];
	};


}

#endif