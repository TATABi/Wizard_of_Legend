#ifndef OVER_STATE_CONTROLLER_H
#define OVER_STATE_CONTROLLER_H

#include "Controller.h"

namespace game_framework {
	class Over_State_Controller :public Controller {
		enum FLAG {
			FLAG_NORMAL
		};
	public:
		Over_State_Controller();
		~Over_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyDown(UINT, UINT, UINT);
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap _bm_result;							
		CMovingBitmap _bm_black_mask;				//�p�a�ϾB�n
		CAnimation	_ani_play_keyboard;
		CInteger _int_stage;						//��F�����d
		CInteger _int_gold_found;					//��쪺money�ƶq
		CInteger _int_gems_collected;				//��쪺diamond�ƶq
		CInteger _int_enemy_defeated;				//���Ѫ��ĤH�ƶq
		FLAG _flag;
		int _delay_counter;							//�i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		int _mask_counter;							//���Ʀr�C�C�X�{�Ϊ�counter
		bool _isPlayed;								//�P�_�O�_�}��
		int result[4];								//�s4��CInteger���ƭ�
	};
}

#endif
