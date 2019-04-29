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
		void LoadBitmap();
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
		FLAG _flag;										// �{�b�e�������A 0:��ܥ[�J�C�����ﶵ 1:�i�J�C��(�S�}������) 2:�}�ҹD��c 3:�}�Ү� 4:�ǰe��Town
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Home _map;									// �a��
		Box _box;
		Book _book;
		
		Character *_character;
		PausedMenu *_pauseMenu;
		Bag *_bag;
		Items *_items;
		UI *_ui;
		
		int _game_state_num;
		bool _isSwitch;
		
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_W = 0x57;
		const char KEY_S = 0x53;
		const char KEY_A = 0x41;
		const char KEY_D = 0x44;
		const char KEY_F = 0x46;
		const char KEY_ESC = 27;
		const char KEY_SPACE = 0x20;
		const char KEY_TAB = 0x09;

	};

}

#endif
