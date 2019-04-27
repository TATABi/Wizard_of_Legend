#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameMap.h"
#include "CharacterData.h"
#include "Layer.h"

namespace game_framework {

	class Character : public Layer{
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
		bool IsSlash();  	
		void Dash();
		bool IsMoving();
		bool CanDash();
		Skill* generateSkill(int, int, int);	//skill num
	protected:
		CAnimation _ani_up;		//向上動畫
		CAnimation _ani_down;	//向下動畫
		CAnimation _ani_left;	//向左動畫
		CAnimation _ani_right;	//向右動畫
		CAnimation _ani_run_up;	//跑步時的氣流
		CAnimation _ani_run_down;
		CAnimation _ani_run_left;
		CAnimation _ani_run_right;
		CAnimation _ani_dash_up;			//dash動畫
		CAnimation _ani_dash_down;
		CAnimation _ani_dash_left;
		CAnimation _ani_dash_right;
		CAnimation _ani_arrival;			//出場動畫
		CMovingBitmap _bm_stand_up;		//向上靜止
		CMovingBitmap _bm_stand_down;	//向下靜止
		CMovingBitmap _bm_stand_left;	//向左靜止
		CMovingBitmap _bm_stand_right;	//向右靜止
		int _horizontal, _vertical;	//上下左右判定(移動距離)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag;			// 紀錄角色面向哪面 (順時鐘，從12點開始，總共8個方向) = (0, 1, 2, 3, 4, 5, 6, 7);???改?
		bool _isMovingDown;			//向下
		bool _isMovingLeft;			//向左
		bool _isMovingRight;			//向右
		bool _isMovingUp;			//向上
		bool _isDash;
		bool _isRunning;				//跑步
		bool _isDashLock;
		bool _isSlash;
		int _SLASH_PIXEL;			//斜線移動速度
		int _STR_PIXEL;				//直線移動速度
		const int DASH_DELAY = 15;
		int _run_counter;			// 計算角色是否要奔跑
		const int NORMAL_SLASH_PIXEL = 5;
		const int NORMAL_STR_PIXEL = 6;
		const int RUN_SLASH_PIXEL = 7;
		const int RUN_STR_PIXEL = 10;
		const int DASH_SLASH_PIXEL = 14;
		const int DASH_STR_PIXEL = 20;
		int _dash_delay_counter;
		int _dash_counter;
		bool _isUseSkill;
		int _useSkillCounter;
	};
}

#endif