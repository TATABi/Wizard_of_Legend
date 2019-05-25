#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g) : CGameState(g) {}

	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%

		_controller.Initialize();

		ShowInitProgress(30);

		//global variable initialize...//

		Global_Class::g_items.LoadBitmap();
		Global_Class::g_pauseMenu.LoadBitmap();
		Global_Class::g_character.LoadBitmap();
		Global_Class::g_ui.LoadBitmap();
		Global_Class::g_bag.LoadBitmap();

		/////////////////////////////////
		ShowInitProgress(65);
	}

	void CGameStateInit::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateInit::OnShow()
	{
		_controller.OnShow();

		if (_controller.IsSwitchGameState())
			GotoGameState(_controller.GameState());
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g) : CGameState(g) {}

	void CGameStateOver::OnMove()
	{
		_counter--;
		if (_counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		_counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit() {}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Game Over ! (%d)", _counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}


	/////////////////////////////////////////////////////////////////////////////
	// Home
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Home::CGameStateRun_Home(CGame *g) : CGameState(g) {}

	CGameStateRun_Home::~CGameStateRun_Home() {}

	void CGameStateRun_Home::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Home::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Home::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Home::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Home::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Home::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Home::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Home::OnShow()
	{
		_controller.OnShow();

		if (_controller.IsSwitchGameState())
		{
			GotoGameState(_controller.GameState());
		}
	}


	/////////////////////////////////////////////////////////////////////////////
	////Town
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Town::CGameStateRun_Town(CGame *g) : CGameState(g) {}

	CGameStateRun_Town::~CGameStateRun_Town() {}

	void CGameStateRun_Town::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Town::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Town::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Town::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Town::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Town::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Town::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Town::OnShow()
	{
		_controller.OnShow();

		if (_controller.IsSwitchGameState())
		{
			GotoGameState(_controller.GameState());
		}
	}



	/////////////////////////////////////////////////////////////////////////////
	////Level 1
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun_Level_1::CGameStateRun_Level_1(CGame *g) : CGameState(g) {}

	CGameStateRun_Level_1::~CGameStateRun_Level_1() {}

	void CGameStateRun_Level_1::OnBeginState()
	{
		_controller.Begin();
	}

	void CGameStateRun_Level_1::OnMove()
	{
		_controller.OnMove();
	}

	void CGameStateRun_Level_1::OnInit()
	{
		_controller.Initialize();
	}

	void CGameStateRun_Level_1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Level_1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		_controller.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun_Level_1::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun_Level_1::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		_controller.OnRButtonDown(nFlags, point);
	}

	void CGameStateRun_Level_1::OnShow()
	{
		_controller.OnShow();

		if (_controller.IsSwitchGameState())
		{
			GotoGameState(_controller.GameState());
		}
	}
}
