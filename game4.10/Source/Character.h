#include "GameMap.h"
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
		void SetRunning(bool);
	protected:
		CAnimation ani_up;		//�V�W�ʵe
		CAnimation ani_down;	//�V�U�ʵe
		CAnimation ani_left;	//�V���ʵe
		CAnimation ani_right;	//�V�k�ʵe
		CAnimation ani_run_up;	//�]�B�ɪ���y
		CAnimation ani_run_down;
		CAnimation ani_run_left;
		CAnimation ani_run_right;
		CMovingBitmap bm_stand_up;		//�V�W�R��
		CMovingBitmap bm_stand_down;	//�V�U�R��
		CMovingBitmap bm_stand_left;	//�V���R��
		CMovingBitmap bm_stand_right;	//�V�k�R��
		int _horizontal, _vertical;	//�W�U���k�P�w(���ʶZ��)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag; // �������⭱�V���� (�k,��,�U,�W) = (0, 1, 2, 3);
		int _x, _y;
		bool isMovingDown;			//�V�U
		bool isMovingLeft;			//�V��
		bool isMovingRight;			//�V�k
		bool isMovingUp;			//�V�W
		bool isRunning = false;		//�]�B
		int SLASH_PIXEL = 1;	//�׽u���ʳt��
		int STR_PIXEL = 1;	//���u���ʳt��
		const int CHARACTER_SCREEN_X = 285; //�ù�����X�y��
		const int CHARACTER_SCREEN_Y = 205;	//�ù�����Y�y��
	};
}
