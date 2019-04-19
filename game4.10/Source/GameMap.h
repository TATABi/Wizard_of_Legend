#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Enemy.h"
#include "Layer.h"
#include "Skill.h"

namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // 設定初始中心點
		~GameMap();
		void Initialize(int, int);
		void ParentLoadBitmap();
		void ParentOnMove();
		void OnShowBackground();
		void OnShowWall();
		void OnShowPressF();
		int GetCharacterStatus();
		int* GetCharacterPosition();
		virtual void LoadBitmap()=0;
		virtual void OnMove(vector<Skill*>)=0;
		virtual void OnShow(std::vector<Skill*>*)=0;
		virtual int* SetCharacterXY(int,int)=0;
		virtual int GetMapStatus(int, int)=0;
		
	protected:
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆	
		CAnimation ani_press_f;  //press f 動畫
		int cxy[2] = { 0,0 };	//角色所在Map的座標
		bool isPressF;
		int character_status;
		const int collision_move[4] = { 24, 53, 20 , 7};   //(x,y,l,w) collision_move	碰撞判定範圍
		const int collision_damage[4] = {23, 10, 24, 49};	//受到傷害判定範圍
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		vector<Enemy*> enemies;
		
	};

}
#endif