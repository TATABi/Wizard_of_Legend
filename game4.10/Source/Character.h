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
	protected:
		CAnimation ani_up;		//�V�W�ʵe
		CAnimation ani_down;	//�V�U�ʵe
		CAnimation ani_left;	//�V���ʵe
		CAnimation ani_right;	//�V�k�ʵe
		CAnimation ani_run_up;	//�]�B�ɪ���y
		CAnimation ani_run_down;
		CAnimation ani_run_left;
		CAnimation ani_run_right;
		CAnimation ani_dash_up;			//dash�ʵe
		CAnimation ani_dash_down;
		CAnimation ani_dash_left;
		CAnimation ani_dash_right;
		CAnimation ani_arrival;			//�X���ʵe
		CMovingBitmap bm_stand_up;		//�V�W�R��
		CMovingBitmap bm_stand_down;	//�V�U�R��
		CMovingBitmap bm_stand_left;	//�V���R��
		CMovingBitmap bm_stand_right;	//�V�k�R��
		int _horizontal, _vertical;	//�W�U���k�P�w(���ʶZ��)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag;			// �������⭱�V���� (�������A�q12�I�}�l�A�`�@8�Ӥ�V) = (0, 1, 2, 3, 4, 5, 6, 7);???��?
		bool isMovingDown;			//�V�U
		bool isMovingLeft;			//�V��
		bool isMovingRight;			//�V�k
		bool isMovingUp;			//�V�W
		bool isDash;
		bool isRunning;				//�]�B
		bool isDashLock;
		bool isSlash;
		int SLASH_PIXEL;			//�׽u���ʳt��
		int STR_PIXEL;				//���u���ʳt��
		//const int CHARACTER_SCREEN_X = 285; //�ù�����X�y��
		//const int CHARACTER_SCREEN_Y = 205;	//�ù�����Y�y��
		const int DASH_DELAY = 15;
		int run_counter;			// �p�⨤��O�_�n�b�]
		const int NORMAL_SLASH_PIXEL = 5;
		const int NORMAL_STR_PIXEL = 6;
		const int RUN_SLASH_PIXEL = 7;
		const int RUN_STR_PIXEL = 10;
		const int DASH_SLASH_PIXEL = 14;
		const int DASH_STR_PIXEL = 20;

		int dash_delay_counter;
		int dash_counter;
	};
}

#endif