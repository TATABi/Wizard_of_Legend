#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameMap.h"
#include "CharacterData.h"
#include "Layer.h"

namespace game_framework {

	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Character : public Layer {
	public:
		Character();
		void Initialize(int*);							//���s����y�СB�ƾ�
		void LoadBitmap();								//���J�ʵe�B�Ϥ�
		void OnMove(GameMap *);							//�ǤJ�a�ϥΥH�P�_�ҳB��m
		void OnShow();									//���
		void SetMovingDown(bool flag);					//���U����
		void SetMovingLeft(bool flag);					//��������
		void SetMovingRight(bool flag);					//���k����
		void SetMovingUp(bool flag);					//���W����
		void Dash();									//Dash �첾
		const int* GetHitbox();							//�I����
		Skill* GenerateSkill(int, float, float);		//�ͦ��ޯ� (skill number, �ͦ��y��)
		bool IsUsingSkill();							//�O�_���b�ϥΧޯ�(���񨤦�ϥΧޯ઺�ʵe)
		bool IsHurt();									//�O�_�Q�ޡA�Q�ޮɤ���Χޯ�
	private:
		bool IsSlash();									//�O�_�ר�
		bool CanDash();									//�O�_�i�HDash
		bool IsMoving();								//�O�_����J����(�W�U���k)���ʫ��O
		int CaculateVector(int, int);					//�p��ƹ��� Vector�A�ΨӧP�w�ޯ�I��ɡA����ӭ��諸��V
		void ResetRun();
		void ResetDash();

		CAnimation _ani_up, _ani_down, _ani_left, _ani_right;												//�����ʵe
		CAnimation _ani_run_up, _ani_run_down, _ani_run_left, _ani_run_right;								//�]�B�ɪ���y
		CAnimation _ani_dash_up, _ani_dash_down, _ani_dash_left, _ani_dash_right;							//dash�ʵe
		//CAnimation _ani_arrival;																			//�X���ʵe
		//CAnimation _ani_dead;																				//���`�ʵe
		CAnimation _ani_useSkill_1;																			//�ϥ�Skill 1 �ʵe
		CAnimation _ani_useSkill_2_up, _ani_useSkill_2_down, _ani_useSkill_2_left, _ani_useSkill_2_right;	//�ϥ�Skill 2 �ʵe
		CAnimation _ani_useSkill_3_down, _ani_useSkill_3_up;												//�ϥ�Skill 3 �ʵe
		CAnimation* _ani_useSkill;																			//�Ȧs�{�b�ϥΪ��ޯ�
		CMovingBitmap _bm_stand_up, _bm_stand_down, _bm_stand_left, _bm_stand_right;						//���߹�
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;														//�Q�޹�

		DIRECTION _direction;												// �������⭱�V��V
		int _dx, _dy;														//���ʶZ��
		bool _isMovingDown, _isMovingLeft, _isMovingRight, _isMovingUp;		//���ʤ�V
		bool _isDash;														//Dash
		bool _isRunning;													//�]�B
		bool _isDashLock;													//Dash��������ܲ��ʤ�V�A������Dash����
		bool _isUsingSkill;													//�O�_���b�ϥΧޯ�
		bool _isHurt;														//�Q��
		int _useSkillNum;
		float _step;
		int _run_counter;			// �p�⨤��O�_�n�b�]
		int _dash_delay_counter;  //�����a�L�k�@��dash (dash�Mdash���������j)
		int _dash_counter;	//�Ψ�reset dash �ʵe
		double _dash_resistance;
		int _hit_recover_counter;
		int _hp;	//�ȦsHP�A�Ψ��ˬd�O�_����
	};
}

#endif