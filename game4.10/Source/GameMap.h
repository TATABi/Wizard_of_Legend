#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Enemy.h"
#include "Layer.h"
#include "Skill.h"

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
		int* GetCharacterPosition();
		void CharacterUseSkill(int, int, int);
		virtual void LoadBitmap()=0;
		//virtual void OnMove(vector<Skill*>&)=0;
		virtual void OnMove() = 0;
		//virtual void OnShow(std::vector<Skill*>&)=0;
		virtual void OnShow() = 0;
		virtual int* SetCharacterXY(int,int)=0;
		virtual int GetMapStatus(int, int)=0;
		
	protected:
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��	
		CAnimation ani_press_f;  //press f �ʵe
		int cxy[2] = { 0,0 };	//����ҦbMap���y��
		bool isPressF;
		int character_status;
		const int collision_move[4] = { 24, 53, 20 , 7};   //(x,y,l,w) collision_move	�I���P�w�d��
		const int collision_damage[4] = {23, 10, 24, 49};	//����ˮ`�P�w�d��
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		Character* character;
		std::vector<Skill*> _skillList;
	};

}
#endif