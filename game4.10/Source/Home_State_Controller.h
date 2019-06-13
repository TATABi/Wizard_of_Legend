#ifndef HOME_STATE_CONTROLLER_H
#define HOME_STATE_CONTROLLER_H
#include "Map_Home.h"
#include "Box.h"
#include "Book.h"
#include "Bag.h"
#include "UI.h"
#include "Controller.h"
#include "PausedMenu.h"

namespace game_framework {
	class Home_State_Controller :public Controller {
		enum FLAG {
			FLAG_HOME_NORMAL,
			FLAG_JOIN,
			FLAG_BOX,
			FLAG_BOX_ITEM,
			FLAG_HOME_PAUSED,
			FLAG_HOME_OPTIONS,
			FLAG_HOME_BAG,
			FLAG_BOOK
		};
	public:
		Home_State_Controller();						
		void Initialize();								//��l��
		void Begin();									//���m�ƾ�
		void OnKeyUp(UINT, UINT, UINT);					//��}����	
		void OnKeyDown(UINT, UINT, UINT);				//���U����
		void OnLButtonDown(UINT, CPoint);				//���U����
		void OnRButtonDown(UINT, CPoint);				//���U�k��
		void OnMove();									//�޿�B��
		void OnShow();									//���
	private:
		CMovingBitmap _bm_join;							//join�C�������ܿ��
		CMovingBitmap _bm_loading;						//loading�r�˪��Ϥ�
		CAnimation _ani_light_beam;						//����b�a���{�����ʵe
		FLAG _flag;										//�����{�b�ҳB���q
		int _delayCounter;								//�i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Home _map;									//�C���a��
		Box _box;										//�D��c
		Book _book;										//��
	};
}

#endif
