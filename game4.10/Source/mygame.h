#include "Box.h"
#include "Book.h"
#include "Store.h"
#include "Map_Home.h"
#include "Map_Town.h"
#include "Skill_Rebounding_Icicles.h"
#include "Skill_Shock_Nova.h"
#include "Init_State_Controller.h"
#include "Home_State_Controller.h"
#include "Global_Class.h"

namespace game_framework {
	
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////
	/*
	static Items g_items;
	static UI g_ui;
	static Character g_character;
	static PausedMenu g_pauseMenu;
	static Bag g_bag;
	*/
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
	
	
	enum HOME_FLAG {
		FLAG_HOME_NORMAL,
		FLAG_JOIN,
		FLAG_BOX,
		FLAG_BOX_ITEM,
		FLAG_HOME_PAUSED,
		FLAG_HOME_OPTIONS,
		FLAG_HOME_BAG,
		FLAG_BOOK
	};

	enum TOWN_FLAG {
		FLAG_TOWN_NORMAL,
		FLAG_TOWN_PAUSED,
		FLAG_TOWN_OPTIONS,
		FLAG_TOWN_BAG
	};

	

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		Init_State_Controller _controller;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun_Home : public CGameState {
	public:
		CGameStateRun_Home(CGame *g);
		~CGameStateRun_Home();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		/*
		CMovingBitmap _bm_join;							// join�C�������ܿ��
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		CAnimation _ani_light_beam;						// ����b�a���{�����ʵe
		HOME_FLAG _flag;										// �{�b�e�������A 0:��ܥ[�J�C�����ﶵ 1:�i�J�C��(�S�}������) 2:�}�ҹD��c 3:�}�Ү� 4:�ǰe��Town
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Home _map;									// �a��
		Box _box;
		Book _book;
		*/
		Home_State_Controller _controller;
	};

	/////////////////////////////////////////////////////////////////////////////
	//Town
	//
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateRun_Town : public CGameState {
	public:
		CGameStateRun_Town(CGame *g);
		~CGameStateRun_Town();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		int _flag;										// 
		int _delayCounter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Town _map;									// �a��
		Store _item_store;								//�D��ө�
	};
	
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int _counter;	// �˼Ƥ��p�ƾ�

	};

}