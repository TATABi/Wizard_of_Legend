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
		void SetCharacterXY(int, int);
		bool CheckEnemyPosition(int, int, int*);
		virtual void LoadBitmap() = 0;
		virtual void OnMove() = 0;
		virtual int GetMapStatus(float, float) = 0;
	protected:
		bool CheckMapStatus(int, int, const int*, int = -1, char = '!');				//�˴����⪬�A	x, y, hitbox, �˴���
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��	
		CAnimation _ani_press_f;  //press f �ʵe
		float _cxy[2] = { 0,0 };	//����ҦbMap���y��
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