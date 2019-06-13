#ifndef SKILL_AIR_SPINNER_H
#define SKILL_AIR_SPINNER_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Air_Spinner : public Skill
	{
	public:
		Skill_Air_Spinner(int, int, float*);				//傳入滑鼠座標、角色座標
		void Initialize(int, int, float*);					//初始化數值
		void LoadBitmap();									//匯入圖片
		void OnMove(float *, GameMap *);					//設定技能座標、延遲等
		int GetDamage(Enemy *);								//偵測怪物與技能碰撞
		void OnShow();										//顯示技能
	};
}
#endif