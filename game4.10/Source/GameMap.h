#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Enemy.h"
#include "Layer.h"
#include "Skill.h"
#include "Reward.h"
#include "GameData.h"

namespace game_framework {
	class Character;

	class GameMap {
	public:
		GameMap(int, int);  // 設定初始中心點
		~GameMap();
		void Initialize(int, int);
		void LoadBitmapPressF();
		void OnMoveBackgroundAndWall();
		void OnShowBackground();
		void OnShowWall();
		void OnShowPressF();
		int GetCharacterStatus();
		float* GetCharacterPosition();
		void CharacterUseSkill(int, int, int);
		void OnShow();
		void SkillOnMove();
		void EnemyOnMove();
		void RewardsOnMove();
		void CleanMemory();
		void SetCharacterXY(int, int);
		bool CheckEnemyPosition(int, int, int*);
		virtual void LoadBitmap() = 0;
		virtual void OnMove() = 0;
		virtual int GetMapStatus(float, float) = 0;
	protected:
		bool CheckMapStatus(int, int, const int*, int = -1, char = '!');				//檢測角色狀態	x, y, hitbox, 檢測值
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆	
		CAnimation _ani_press_f;  //press f 動畫
		float _cxy[2] = { 0,0 };	//角色所在Map的座標
		bool _isPressF;
		int _character_status;
		vector<Skill*> _skillList;
		vector<Enemy*> _enemies;
		vector<Reward*> _rewards;
		float _dx = 0;
		float _dy = 0;
		int _drop_counter = DROP_COUNTER_TIME;
	};
}
#endif