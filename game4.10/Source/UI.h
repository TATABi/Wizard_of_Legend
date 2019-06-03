#ifndef UI_H
#define UI_H
#include "CharacterData.h"

namespace game_framework {
	class UI {
	public:
		static UI &Instance();		//Singleton
		void LoadBitmap();			//�פJ�Ϥ�
		void SetXY();				//�]�w��m
		void OnMove();				//�p��
		void OnShow();				//���
		void CalculateHP();			//�p�� & ���HP
		void CalculateMP();			//�p�� & ���MP
	protected:
		UI();
	private:
		CMovingBitmap _bm_status;
		CMovingBitmap _bm_money;
		CMovingBitmap _bm_diamond;
		CMovingBitmap _bm_skill1_background,	//Skill UI �I��
					  _bm_skill2_background,
					  _bm_skill3_background,
					  _bm_skill4_background;
		CMovingBitmap _bm_skill_1,				//Skill UI �ϥ�
					  _bm_skill_2,
					  _bm_skill_3,
					  _bm_skill_4;
		CMovingBitmap _bm_key_q;				//UI Q��
		CMovingBitmap _bm_key_space;			//UI Space��
		CMovingBitmap _bm_right_button;			//UI Right button��
		CMovingBitmap _bm_left_button;			//UI Left button��
		CMovingBitmap _bm_slash;				//UI �׽u
		CAnimation _ani_mp_bar;
		CInteger _int_diamond,					//�򥻼ƭȪ��Ʀr
				 _int_money,
				 _int_maxhp,
			     _int_hp;
		CInteger _skiil_2_cooldown,				//Skill�N�o�p��
				 _skiil_3_cooldown;
	};
}

#endif
