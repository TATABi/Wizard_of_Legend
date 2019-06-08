#ifndef SKILL_REBOUNDING_ICICLES_H
#define SKILL_REBOUNDING_ICICLES_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Rebounding_Icicles : public Skill
	{
	public:
		Skill_Rebounding_Icicles(int, int, float*);			//傳入滑鼠座標、角色座標
		void Initialize(int, int, float*);					//初始化數值
		void LoadBitmap();									//匯入圖片
		void OnMove(float *, GameMap *);					//設定技能座標、延遲等
		int GetDamage(Enemy *);								//偵測怪物與技能碰撞
		void OnShow();										//顯示技能
	private:
		bool _isInit[4];									//是否第一張動畫
		int _ani_1[2], _ani_2[2], _ani_3[2], _ani_4[2];		//技能的位置
	};
}

#endif