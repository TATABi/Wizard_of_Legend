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
		void OpenMap(bool ,int);				//�}�Ҧa��
		void ResetMapMask();		//���m�a�ϾB�n
	protected:
		UI();
	private:
		CMovingBitmap _bm_status;				//�����T
		CMovingBitmap _bm_money;				//money icon
		CMovingBitmap _bm_diamond;				//diamond icon
		CMovingBitmap _bm_skill1_background,	//Skill UI �I��
					  _bm_skill2_background,
					  _bm_skill3_background,
					  _bm_skill4_background;
		CMovingBitmap _bm_skill_1,				//Skill UI �ϥ�
					  _bm_skill_2,
					  _bm_skill_3,
					  _bm_skill_4;
		CMovingBitmap _bm_key_q;				//UI Q��
		CMovingBitmap _bm_key_m;				//UI M��
		CMovingBitmap _bm_key_tab;				//UI Tab��
		CMovingBitmap _bm_map;					//UI Map�ϥ�
		CMovingBitmap _bm_info;					//UI Info�ϥ�
		CMovingBitmap _bm_key_space;			//UI Space��
		CMovingBitmap _bm_right_button;			//UI Right button��
		CMovingBitmap _bm_left_button;			//UI Left button��
		CMovingBitmap _bm_slash;				//UI �׽u
		CMovingBitmap _bm_map_1;				//Level 1���p�a��
		CMovingBitmap _bm_map_mask;				//Map�B�n
		CMovingBitmap _bm_character_head;		//Map�W�����Y��
		CMovingBitmap _bm_map_board;			//Map Board
		CAnimation _ani_mp_bar;					//Mp�{�{�ʵe
		CInteger _int_diamond,					//�򥻼ƭȪ��Ʀr
				 _int_money,
				 _int_maxhp,
			     _int_hp;
		CInteger _skiil_2_cooldown,				//Skill�N�o�p��
				 _skiil_3_cooldown;
		bool _isOpenMap = false;				//�O�_�}�Ҧa��
		bool _map_mask[10][10];					//����Map Mask��
		int _map_num;							//�����}��Map���s��
	};
}

#endif
