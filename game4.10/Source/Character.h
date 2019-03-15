#include "GameMap.h"
namespace game_framework {

	class Character {
	public:
		Character();
		void Initialize();				
		void LoadBitmap();			
		void OnMove(GameMap *);	
		void SetCharacterXY(int, int);
		void OnShow();				
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag); 
		void SetMovingUp(bool flag);	
		bool isSlash();  	
		void Dash();
		bool isMoving();
		void SetRunning(bool);
	protected:
		CAnimation ani_up;		//向上動畫
		CAnimation ani_down;	//向下動畫
		CAnimation ani_left;	//向左動畫
		CAnimation ani_right;	//向右動畫
		CMovingBitmap bm_stand_up;		//向上靜止
		CMovingBitmap bm_stand_down;	//向下靜止
		CMovingBitmap bm_stand_left;	//向左靜止
		CMovingBitmap bm_stand_right;	//向右靜止
		int _horizontal, _vertical;	//上下左右判定(移動距離) 
		int _directionFlag;			// 紀錄角色面向哪面 (右,左,下,上) = (0, 1, 2, 3);
		bool isMovingDown;			//向下
		bool isMovingLeft;			//向左
		bool isMovingRight;			//向右
		bool isMovingUp;			//向上
		bool isRunning = false;		//跑步
		int SLASH_PIXEL = 3;		//斜線移動速度
		int STR_PIXEL = 2;			//直線移動速度
		const int CHARACTER_SCREEN_X = 285; //螢幕中心X座標
		const int CHARACTER_SCREEN_Y = 205;	//螢幕中心Y座標
		int _cx, _cy;						//角色在地圖的點座標
	};
}
