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
		void Suffer(int);	//�Ө��ˮ` temp�Ȯɨϥ�
	protected:
		CAnimation _ani_up, _ani_down, _ani_left, _ani_right;	//�����ʵe
		CAnimation _ani_run_up, _ani_run_down, _ani_run_left, _ani_run_right; //�]�B�ɪ���y
		CAnimation _ani_dash_up, _ani_dash_down, _ani_dash_left, _ani_dash_right; //dash�ʵe
		CAnimation _ani_arrival;			//�X���ʵe
		CAnimation _ani_useSkill_1;
		CAnimation _ani_useSkill_2_up, _ani_useSkill_2_down, _ani_useSkill_2_left, _ani_useSkill_2_right;
		CAnimation _ani_useSkill_3_down, _ani_useSkill_3_up;
		CAnimation* _ani_useSkill;
		CMovingBitmap _bm_stand_up, _bm_stand_down, _bm_stand_left, _bm_stand_right;	//����
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;
		int _horizontal, _vertical;	//�W�U���k�P�w(���ʶZ��)  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _directionFlag;			// �������⭱�V���� (�������A�q12�I�}�l�A�`�@8�Ӥ�V) = (0, 1, 2, 3, 4, 5, 6, 7);???��?
		bool _isMovingDown, _isMovingLeft, _isMovingRight, _isMovingUp;		//���ʤ�V
		bool _isDash;
		bool _isRunning;				//�]�B
		bool _isDashLock;
		bool _isSlash;
		bool _isUsingSkill;
		bool _isHurt;
		int _useSkillNum;
		int _SLASH_PIXEL;			//�׽u���ʳt��
		int _STR_PIXEL;				//���u���ʳt��
		const int DASH_DELAY = 15;
		const int NORMAL_SLASH_PIXEL = 4;
		const int NORMAL_STR_PIXEL = 6;
		const int RUN_SLASH_PIXEL = 7;
		const int RUN_STR_PIXEL = 10;
		const int DASH_SLASH_PIXEL = 13;
		const int DASH_STR_PIXEL = 20;
		int _run_counter;			// �p�⨤��O�_�n�b�]
		int _dash_delay_counter;  //�����a�L�k�@��dash (dash�Mdash���������j)
		int _dash_counter;	//�Ψ�reset dash �ʵe
		double _dash_resistance;
		int _hit_recover_counter;

		int _hitbox[4] = { 23, 10, 24, 49 };
	};
}

#endif