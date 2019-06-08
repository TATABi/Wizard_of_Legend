#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Enemy.h"
#include "Layer.h"
#include "Skill.h"
#include "Reward.h"

namespace game_framework {
	class Character;

	class GameMap {
	public:
		GameMap(int, int);  // �]�w��l�����I
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
		float* SetCharacterXY(int, int, const int*);
		bool SetEnemyXY(int, int, int*);
		virtual void LoadBitmap() = 0;
		virtual void OnMove() = 0;
		virtual void AddEnemy() = 0;
		virtual int GetMapStatus(float, float) = 0;
		
	protected:
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��	
		CAnimation _ani_press_f;  //press f �ʵe
		float _cxy[2] = { 0,0 };	//����ҦbMap���y��
		bool _isPressF;
		int _character_status;
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		vector<Skill*> _skillList;
		vector<Enemy*> _enemies;
		vector<Reward*> _rewards;
	};
}
#endif