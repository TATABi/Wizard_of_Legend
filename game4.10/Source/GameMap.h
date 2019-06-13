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
		GameMap(int, int);								//�]�w��l�����I
		~GameMap();										//�Ѻc
		void Initialize(int, int);						//��l�ƨ����m
		void LoadBitmapPressF();						//�פJPress F���s
		void OnMoveBackgroundAndWall();					//�I��&�������
		void OnShowBackground();						//�I�����
		void OnShowWall();								//������
		void OnShowPressF();							//Press F���
		int GetCharacterStatus();						//���oCharacter�{�b�Ҧb�ϰ쪺Logic��T
		float* GetCharacterPosition();					//���oCharacter��m
		void CharacterUseSkill(int, int, int);			//�ϥΧޯश��
		void OnShow();									//���Skill, Enemy, Character�öi��ϼh��ܱƧ�
		void SkillOnMove();								//Skill���B��
		void EnemyOnMove();								//Enemy���B��
		void RewardsOnMove();							//Reward���B��
		void CleanMemory();								//�M�z�����n���Ŷ�
		void SetCharacterXY(int, int);					//Charater���ʡA�P�_�O�_�i�H����orĲ�o����
		bool CheckEnemyPosition(int, int, const int*);	//�ˬdEnemy���ʪ���m�O�_�i����
		bool IsEnd();									//�����C��
		virtual void Init();							//�ӧOMap��l��
		virtual void Show();							//�ӧOMap���
		virtual void LoadBitmap() = 0;					//�פJMap�Ϥ�
		virtual void OnMove() = 0;						//Map���ʵ��B��
		virtual int GetMapStatus(float, float) = 0;		//�����a�Ϥ����I��Logic��T
	protected:
		bool CheckMapStatus(int, int, const int*, int = -1, char = '!'); //�˴����⪬�A	x, y, hitbox, �˴���
		CMovingBitmap _background;						//�I����
		CMovingBitmap _wall;							//��	
		CAnimation _ani_press_f;						//press f �ʵe
		float _cxy[2] = { 0,0 };						//����ҦbMap���y��
		bool _isPressF;									//�O�_�b�i���ʰϰ�
		int _character_status;							//���⪬�A
		vector<Skill*> _skillList;						//�x�s�Ҧ����WSkill
		vector<Enemy*> _enemies;						//�x�s�Ҧ����WEnemy
		vector<Reward*> _rewards;						//�x�s�Ҧ����W_rewards
		bool _isSummonBoss;
		bool _isEnd;
	};
}
#endif