#ifndef TOWN_STATE_CONTROLLER_H
#define TOWN_STATE_CONTROLLER_H

#include "Map_Town.h"
#include "Store.h"
#include "Controller.h"
#include "Bag.h"
#include "UI.h"
#include "PausedMenu.h"

namespace game_framework {
	class Town_State_Controller : public Controller{
		enum FLAG								
		{
			FLAG_TOWN_NORMAL,
			FLAG_TOWN_PAUSED,
			FLAG_TOWN_OPTIONS,
			FLAG_TOWN_BAG
		};
	public:
		Town_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		FLAG _flag;										//���Aflag
		Map_Town _map;									//Town�a��
		Store _item_store;								//�D��ө�
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
	};
}

#endif