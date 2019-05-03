#ifndef HOME_STATE_CONTROLLER_H
#define HOME_STATE_CONTROLLER_H

#include "Map_Home.h"
#include "Box.h"
#include "Book.h"
#include "Global_Class.h"

namespace game_framework {

	class Home_State_Controller {

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
		~Home_State_Controller();
		void Initialize();
		void Begin();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT, CPoint);
		void OnRButtonDown(UINT, CPoint);
		void OnMove();
		void OnShow();
		bool IsSwitchGameState();
		int GameState();

	private:
		CMovingBitmap _bm_join;							// join�C�������ܿ��
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		CAnimation _ani_light_beam;						// ����b�a���{�����ʵe
		FLAG _flag;								
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Home _map;									
		Box _box;
		Book _book;
		
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		Items *_items;
		UI *_ui;
		
		int _game_state_num;
		bool _isSwitch;

	};

}

#endif
