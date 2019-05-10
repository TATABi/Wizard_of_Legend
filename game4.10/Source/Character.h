#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameMap.h"
#include "CharacterData.h"
#include "Layer.h"

#define CHARACTER_SCREEN_CENTER_X 320
#define CHARACTER_SCREEN_CENTER_Y 240

namespace game_framework {

	enum DIRECTION{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Character : public Layer{
	public:
		Character();
		void Initialize(int*);				
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
		bool IsUsingSkill();
		int* GetPosition();
		int* GetHitbox();
		Skill* GenerateSkill(int, int, int);	//skill num
		int CaculateDirection(int, int);
		void Suffer(int);	//承受傷害 temp暫時使用
	protected:
		CAnimation _ani_up, _ani_down, _ani_left, _ani_right;	//走路動畫
		CAnimation _ani_run_up, _ani_run_down, _ani_run_left, _ani_run_right; //跑步時的氣流
		CAnimation _ani_dash_up, _ani_dash_down, _ani_dash_left, _ani_dash_right; //dash動畫
		CAnimation _ani_arrival;			//出場動畫
		CAnimation _ani_useSkill_1;
		CAnimation _ani_useSkill_2_up, _ani_useSkill_2_down, _ani_useSkill_2_left, _ani_useSkill_2_right;
		CAnimation _ani_useSkill_3_down, _ani_useSkill_3_up;
		CAnimation* _ani_useSkill;
		CMovingBitmap _bm_stand_up, _bm_stand_down, _bm_stand_left, _bm_stand_right;	//站立
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;
		int _horizontal, _vertical;	//上下左右判定(移動距離)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag;			// 紀錄角色面向哪面 (順時鐘，從12點開始，總共8個方向) = (0, 1, 2, 3, 4, 5, 6, 7);???改?
		bool _isMovingDown, _isMovingLeft, _isMovingRight, _isMovingUp;		//移動方向
		bool _isDash;
		bool _isRunning;				//跑步
		bool _isDashLock;
		bool _isSlash;
		bool _isUsingSkill;
		bool _isHurt;
		int _useSkillNum;
		int _SLASH_PIXEL;			//斜線移動速度
		int _STR_PIXEL;				//直線移動速度
		const int DASH_DELAY = 15;
		const int NORMAL_SLASH_PIXEL = 4;
		const int NORMAL_STR_PIXEL = 6;
		const int RUN_SLASH_PIXEL = 7;
		const int RUN_STR_PIXEL = 10;
		const int DASH_SLASH_PIXEL = 13;
		const int DASH_STR_PIXEL = 20;
		int _run_counter;			// 計算角色是否要奔跑
		int _dash_delay_counter;  //讓玩家無法一直dash (dash和dash之間有間隔)
		int _dash_counter;	//用來reset dash 動畫
		double _dash_resistance;
		int _hit_recover_counter;

		int _hitbox[4] = { 23, 10, 24, 49 };
	};
}

#endif