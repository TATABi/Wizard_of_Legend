#ifndef SKILL_H
#define SKILL_H
#include "CharacterData.h"
namespace game_framework {
	//skill template class
	class Skill {				
	public:
		Skill(int, int );
		~Skill() ;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize() = 0;
		bool GetIsDelete();
	protected:
		CMovingBitmap bm_skill;
		float dx,dy, sx, sy, mx, my;				//累積移動距離、角色施放技能時地圖座標、每個frame技能所在地圖位置				
		int speed;									//移動速度
		int lifeTimer;								//存活時間
		int vecX, vecY;								//滑鼠位置
		int damage;									//傷害量
		int backDistance;							//擊退距離
		int hitbox_X, hitbox_Y;						//hitBox中心
		const int CHARACTER_SCREEN_X = 285;			//角色螢幕位置要不要拉去全域
		const int CHARACTER_SCREEN_Y = 205;		
		bool isDelete;
	};
}
#endif