#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "CharacterData.h"
#include "Enemy.h"
namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // �]�w��l�����I
		~GameMap();
		void Initialize(int, int);
		void ParentLoadBitmap();
		void ParentOnMove();
		void OnShowBackground();
		void OnShowWall();
		void OnShowPressF();
		int GetCharacterStatus();
		virtual void LoadBitmap()=0;
		virtual void OnMove()=0;
		virtual void OnShow()=0;
		virtual void SetCharacterXY(int,int)=0;

	protected:
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��	
		CAnimation ani_press_f;  //press f �ʵe
		//int paused_flag;
		//bool isPaused;
		int _cx, _cy;  //����ҦbMap���y��
		bool isPressF;
		int character_status;
		const int collision_move[4] = { 24, 53, 20 , 7};   //(x,y,l,w) collision_move	�I���P�w�d��
		const int collision_damage[4] = {0};	//����ˮ`�P�w�d��
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		Enemy *blockhead;///////////////////////
	};

}
#endif