#ifndef SKILL_H
#define SKILL_H

namespace game_framework {
	class Skill{
	public :
		Skill() {};
	protected:
		CAnimation ani_character_skill;
		CMovingBitmap bm_skill;
		bool isPerform;				//是否正在施放
		bool isEquip;				//是否裝備中
		bool isRecover;				//角色是否能移動
		int damage;					//傷害量
		int recoverTime;			//硬直時間
		double coolDownTime;		//冷卻時間
	};


}

#endif