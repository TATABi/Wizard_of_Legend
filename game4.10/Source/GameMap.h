#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Enemy.h"
#include "Layer.h"
#include "Skill.h"


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
		int* GetCharacterPosition();
		void CharacterUseSkill(int, int, int);
		void OnShow();
		void SkillOnMove();
		void EnemyOnMove();
		void CleanMemory();
		virtual void LoadBitmap()=0;
		virtual void OnMove() = 0;
		virtual int* SetCharacterXY(int, int, const int*) = 0;
		virtual bool SetEnemyXY(int, int, int*) = 0;
		virtual int GetMapStatus(int, int) = 0;
		
	protected:
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆	
		CAnimation _ani_press_f;  //press f 動畫
		int _cxy[2] = { 0,0 };	//角色所在Map的座標
		bool _isPressF;
		int _character_status;
		Character* _character;
		std::vector<Skill*> _skillList;
		vector<Enemy*> _enemies;
	};

}
#endif