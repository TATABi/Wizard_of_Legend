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
		CAnimation _ani_up;		//�V�W�ʵe
		CAnimation _ani_down;	//�V�U�ʵe
		CAnimation _ani_left;	//�V���ʵe
		CAnimation _ani_right;	//�V�k�ʵe
		CAnimation _ani_run_up;	//�]�B�ɪ���y
		CAnimation _ani_run_down;
		CAnimation _ani_run_left;
		CAnimation _ani_run_right;
		CAnimation _ani_dash_up;			//dash�ʵe
		CAnimation _ani_dash_down;
		CAnimation _ani_dash_left;
		CAnimation _ani_dash_right;
		CAnimation _ani_arrival;			//�X���ʵe
		CMovingBitmap _bm_stand_up;		//�V�W�R��
		CMovingBitmap _bm_stand_down;	//�V�U�R��
		CMovingBitmap _bm_stand_left;	//�V���R��
		CMovingBitmap _bm_stand_right;	//�V�k�R��
		int _horizontal, _vertical;	//�W�U���k�P�w(���ʶZ��)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag;			// �������⭱�V���� (�������A�q12�I�}�l�A�`�@8�Ӥ�V) = (0, 1, 2, 3, 4, 5, 6, 7);???��?
		bool _isMovingDown;			//�V�U
		bool _isMovingLeft;			//�V��
		bool _isMovingRight;			//�V�k
		bool _isMovingUp;			//�V�W
		bool _isDash;
		bool _isRunning;				//�]�B
		bool _isDashLock;
		bool _isSlash;
		int _SLASH_PIXEL;			//�׽u���ʳt��
		int _STR_PIXEL;				//���u���ʳt��
		const int DASH_DELAY = 15;
		int _run_counter;			// �p�⨤��O�_�n�b�]
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