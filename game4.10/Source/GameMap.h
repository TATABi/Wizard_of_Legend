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
		GameMap(int, int);								//設定初始中心點
		~GameMap();										//解構
		void Initialize(int, int);						//初始化角色位置
		void LoadBitmapPressF();						//匯入Press F按鈕
		void OnMoveBackgroundAndWall();					//背景&牆壁移動
		void OnShowBackground();						//背景顯示
		void OnShowWall();								//牆壁顯示
		void OnShowPressF();							//Press F顯示
		int GetCharacterStatus();						//取得Character現在所在區域的Logic資訊
		float* GetCharacterPosition();					//取得Character位置
		void CharacterUseSkill(int, int, int);			//使用技能介面
		void OnShow();									//顯示Skill, Enemy, Character並進行圖層顯示排序
		void SkillOnMove();								//Skill的運算
		void EnemyOnMove();								//Enemy的運算
		void RewardsOnMove();							//Reward的運算
		void CleanMemory();								//清理不必要的空間
		void SetCharacterXY(int, int);					//Charater移動，判斷是否可以移動or觸發陷阱
		bool CheckEnemyPosition(int, int, const int*);	//檢查Enemy移動的位置是否可移動
		bool IsEnd();									//結束遊戲
		virtual void Init();							//個別Map初始化
		virtual void Show();							//個別Map顯示
		virtual void LoadBitmap() = 0;					//匯入Map圖片
		virtual void OnMove() = 0;						//Map移動等運算
		virtual int GetMapStatus(float, float) = 0;		//取的地圖中該點的Logic資訊
	protected:
		bool CheckMapStatus(int, int, const int*, int = -1, char = '!'); //檢測角色狀態	x, y, hitbox, 檢測值
		CMovingBitmap _background;						//背景圖
		CMovingBitmap _wall;							//牆	
		CAnimation _ani_press_f;						//press f 動畫
		float _cxy[2] = { 0,0 };						//角色所在Map的座標
		bool _isPressF;									//是否在可互動區域
		int _character_status;							//角色狀態
		vector<Skill*> _skillList;						//儲存所有場上Skill
		vector<Enemy*> _enemies;						//儲存所有場上Enemy
		vector<Reward*> _rewards;						//儲存所有場上_rewards
		bool _isSummonBoss;
		bool _isEnd;
	};
}
#endif