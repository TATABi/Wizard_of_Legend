#include "Character.h"
#include "Box.h"
//#include "GameMap.h" new


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_BE,		
		AUDIO_TITLE,
		AUDIO_HOME
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
		CAnimation ani_menu_1;
		CAnimation ani_menu_2;
		CMovingBitmap bm_option;
		CMovingBitmap bm_quit;
		CMovingBitmap bm_single_player;
		int flags = 0;
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
		CMovingBitmap bm_join;							// join�C�������ܿ��
		CMovingBitmap bm_loading;						// loading�r�˪��Ϥ�
		Character character;							// ����
		CAnimation ani_light_beam;						// ����b�a���{�����ʵe
		int flags;										// �{�b�e�������A 0:��ܥ[�J�C�����ﶵ 1:�i�J�C��(�S�}������) 2:�}�ҹD��c 3:�}�Ү� 4:�ǰe��Town
		int delay_counter;								// �i�J�C�����w�ġA�קK�e���X�{�����֡B�Ϥ����٥��ǳƦn
		GameMap Map_Home;								// �a��
		Box box;
		CInteger testInt;
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
		CMovingBitmap bm_option;
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