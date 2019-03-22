#include "Map_Home.h"
namespace game_framework {

	class Character {
	public:
		Character();
		void Initialize();				
		void LoadBitmap();			
		void OnMove(GameMap *);				
		void OnShow();				
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag); 
		void SetMovingUp(bool flag);	
		bool isSlash();  	
		void Dash();
		bool isMoving();
		bool CanDash();
	protected:
		CAnimation ani_up;		//向上動畫
		CAnimation ani_down;	//向下動畫
		CAnimation ani_left;	//向左動畫
		CAnimation ani_right;	//向右動畫
		CAnimation ani_run_up;	//跑步時的氣流
		CAnimation ani_run_down;
		CAnimation ani_run_left;
		CAnimation ani_run_right;
		CAnimation ani_dash_up;		//dash動畫
		CAnimation ani_dash_down;
		CAnimation ani_dash_left;
		CAnimation ani_dash_right;
		CMovingBitmap bm_stand_up;		//向上靜止
		CMovingBitmap bm_stand_down;	//向下靜止
		CMovingBitmap bm_stand_left;	//向左靜止
		CMovingBitmap bm_stand_right;	//向右靜止
		int _horizontal, _vertical;	//上下左右判定(移動距離)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag; // 紀錄角色面向哪面 (順時鐘，從12點開始，總共8個方向) = (0, 1, 2, 3, 4, 5, 6, 7);???改?
		bool isMovingDown;			//向下
		bool isMovingLeft;			//向左
		bool isMovingRight;			//向右
		bool isMovingUp;			//向上
		bool isDash;
		bool isRunning;		//跑步
		int SLASH_PIXEL;	//斜線移動速度
		int STR_PIXEL;		//直線移動速度
		const int CHARACTER_SCREEN_X = 285; //螢幕中心X座標
		const int CHARACTER_SCREEN_Y = 205;	//螢幕中心Y座標
		const int DASH_DELAY = 15;
		int run_counter;	// 計算角色是否要奔跑
		bool dash_lock;
		int dash_delay_counter;
	};
}
