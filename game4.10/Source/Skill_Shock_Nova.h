#ifndef SKILL_SHOCK_NOVA_H
#define SKILL_SHOCK_NOVA_H

#include "Skill.h"
#include "GameMap.h"

namespace game_framework
{
	class Skill_Shock_Nova : public Skill
	{
	public:
		Skill_Shock_Nova(int, int, float*);		//傳入滑鼠座標、角色座標	
		void Initialize(int, int, float*);		//初始化數值
		void LoadBitmap();						//匯入圖片
		void OnMove(int *, GameMap *);			//設定技能座標、延遲等
		int GetDamage(Enemy *);					//偵測怪物與技能碰撞
		void OnShow();							//顯示技能
	private:
		bool _isInit;
		int _delay_counter;						//用來播角色施放即能時的動畫
		int _re_attack_counter;					//重複攻擊的counter
		int _time;								//施放技能的長度，時間內技能都有效，重複播放動畫
	};
}

#endif