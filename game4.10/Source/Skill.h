#ifndef SKILL_H
#define SKILL_H

namespace game_framework {
	//skill template class
	class Skill {				
	public:
		Skill(int, int);
		~Skill() ;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize() = 0;
	protected:
		CMovingBitmap bm_skill;
		int timer;									//存活時間
		int vecX, vecY;								//移動方向座標
		int damage;									//傷害量
		int backDistance;							//擊退距離
		int hitbox_X, hitbox_Y;						//hitBox中心
		const int CHARACTER_SCREEN_X = 285;			//角色螢幕位置要不要拉去全域
		const int CHARACTER_SCREEN_Y = 205;		
		bool isDelete;
	};
}
#endif