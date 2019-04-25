#include "CharacterData.h"
#include "Character.h"
#include "Box.h"
#include "UI.h"
#include "PausedMenu.h"
#include "Items.h"
#include "Bag.h"
#include "Book.h"
#include "Store.h"
#include "Map_Home.h"
#include "Map_Town.h"
#include "Skill_Rebounding_Icicles.h"
#include "Skill_Shock_Nova.h"

namespace game_framework {
	

	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////
	static Items g_items;
	static UI g_ui;
	static Character g_character;
	static PausedMenu g_pauseMenu;
	static Bag g_bag;

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_BE,		
		AUDIO_TITLE,
		AUDIO_HOME,
		AUDIO_DASH,
		AUDIO_TOWN,
		AUDIO_ARRIVAL,
		AUDIO_PULL,
		AUDIO_PUTTING,
		AUDIO_PULL2,
		AUDIO_BUY,
		AUDIO_NOMONEY
	};

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
		CAnimation _ani_menu_1;
		CAnimation _ani_menu_2;
		CMovingBitmap _bm_option;
		CMovingBitmap _bm_quit;
		CMovingBitmap _bm_single_player;
		int _flags = 0;
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
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap _bm_join;							// join�C�������ܿ��
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		CAnimation _ani_light_beam;						// ����b�a���{�����ʵe
		HOME_FLAG _flags;										// �{�b�e�������A 0:��ܥ[�J�C�����ﶵ 1:�i�J�C��(�S�}������) 2:�}�ҹD��c 3:�}�Ү� 4:�ǰe��Town
		int _delay_counter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Home _map;									// �a��
		Box _box;
		Book _book;
		std::vector<Skill*> _skillList;					//�s��Ҧ��ޯ�
		vector<Skill*>::iterator iter;
		
		
	};

	/////////////////////////////////////////////////////////////////////////////
	//Options 
	//
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun_Options : public CGameState {
	public:
		CGameStateRun_Options(CGame *g);
		~CGameStateRun_Options();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap _bm_option;
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
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap _bm_loading;						// loading�r�˪��Ϥ�
		int _flags;										// 
		int _delay_counter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		Map_Town _map;									// �a��
		Store _item_store;								//�D��ө�
		std::vector<Skill*> _skillList;

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
		int counter;	// �˼Ƥ��p�ƾ�

	};

}