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

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{

	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%

	if (CAudio::Instance()->Load(AUDIO_TITLE, "sounds\\TitleBGM.wav"))
		CAudio::Instance()->Play(AUDIO_TITLE, true);

	CAudio::Instance()->Load(AUDIO_BE, "sounds\\be.mp3");

	ani_menu_1.SetDelayCount(2);
	ani_menu_1.AddBitmap(MENU_INIT_02);
	ani_menu_1.AddBitmap(MENU_INIT_04);
	ani_menu_1.AddBitmap(MENU_INIT_06);
	ani_menu_1.AddBitmap(MENU_INIT_08);
	ani_menu_1.AddBitmap(MENU_INIT_10);
	ani_menu_1.AddBitmap(MENU_INIT_12);
	ani_menu_1.AddBitmap(MENU_INIT_14);
	ani_menu_1.AddBitmap(MENU_INIT_16);
	ani_menu_1.AddBitmap(MENU_INIT_18);
	ani_menu_1.AddBitmap(MENU_INIT_20);
	ani_menu_1.AddBitmap(MENU_INIT_22);
	ani_menu_1.AddBitmap(MENU_INIT_24);
	ani_menu_1.AddBitmap(MENU_INIT_26);
	ani_menu_1.AddBitmap(MENU_INIT_28);
	ani_menu_1.AddBitmap(MENU_INIT_30);
	ani_menu_1.AddBitmap(MENU_INIT_32);
	ani_menu_1.AddBitmap(MENU_INIT_34);
	ani_menu_1.AddBitmap(MENU_INIT_36);
	ani_menu_1.AddBitmap(MENU_INIT_38);
	ani_menu_1.AddBitmap(MENU_INIT_40);
	ani_menu_1.AddBitmap(MENU_INIT_42);
	ani_menu_1.AddBitmap(MENU_INIT_44);
	ani_menu_1.AddBitmap(MENU_INIT_46);
	ani_menu_1.AddBitmap(MENU_INIT_48);

	ani_menu_2.SetDelayCount(1);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_01);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_02);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_03);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_04);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_05);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_06);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_07);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_08);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_09);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_10);
	ani_menu_2.AddBitmap(MENU_ENTERMENU_11);

	bm_option.LoadBitmap(MENU_ENTERMENU_OPTIONS);
	bm_quit.LoadBitmap(MENU_ENTERMENU_QUIT);
	bm_single_player.LoadBitmap(MENU_ENTERMENU_SINGLE_PLAYER);

	Sleep(1400);
	ShowInitProgress(65);
}

void CGameStateInit::OnBeginState()
{

	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;

	if (nChar == KEY_ESC)								
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
	else{
		if (flags == 0)
			flags = 1;
	}
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	const char KEY_SPACE = 0x20;
	const char KEY_ENTER = 0xD;
	CAudio::Instance()->Stop(AUDIO_BE);
	CAudio::Instance()->Play(AUDIO_BE, false);

	if (nChar == KEY_UP || nChar == KEY_W)
		flags--;
	if (nChar == KEY_DOWN || nChar == KEY_S)
		flags++;
	if (nChar == KEY_SPACE || nChar == KEY_ENTER) {
		if (ani_menu_2.IsFinalBitmap()) {

			switch (flags) {
			case 1:
				GotoGameState(GAME_STATE_RUN_HOME);
				break;
			case 2:
				GotoGameState(GAME_STATE_RUN_OPTIONS);
				break;
			case 3:
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
				break;
			default:
				break;
			}
		}
	}

	if (flags > 3)
		flags = 3;
	if (flags < 1)
		flags = 1;
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (flags == 0)
		flags = 1;
}

void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
{	
	if(flags == 0)
		flags = 1;
}

void CGameStateInit::OnShow()
{
	switch (flags) {
	case 0:
		ani_menu_1.OnMove();
		ani_menu_1.SetTopLeft(0, 0);
		ani_menu_1.OnShow();
		break;
	case 1:
		if (!ani_menu_2.IsFinalBitmap()) {
			ani_menu_2.OnMove();
			ani_menu_2.SetTopLeft(0, 0);
			ani_menu_2.OnShow();
		}
		else {
			bm_single_player.SetTopLeft(0, 0);
			bm_single_player.ShowBitmap();
		}
		break;
	case 2:
		bm_option.SetTopLeft(0, 0);
		bm_option.ShowBitmap();
		break;
	case 3:
		bm_quit.SetTopLeft(0, 0);
		bm_quit.ShowBitmap();
		break;
	default:
		break;
	}

}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{

}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_Home::CGameStateRun_Home(CGame *g)
: CGameState(g), Map_Home(74, 91)		//����b�a�ϤW����m			///��l�Ʀa�Ϯy�� Map_Home(755,928)	
{

}

CGameStateRun_Home::~CGameStateRun_Home()
{

}

void CGameStateRun_Home::OnBeginState()
{
	counter = 30 * 1; // 1 seconds
	character.Initialize();

	CAudio::Instance()->Stop(AUDIO_TITLE);
	CAudio::Instance()->Play(AUDIO_HOME, true);
}

void CGameStateRun_Home::OnMove()					
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if(counter > -1)
		counter--;

	bm_join.SetTopLeft(100, 100);
	bm_loading.SetTopLeft(0, 0);

	character.OnMove(&Map_Home);

	Map_Home.OnMove();

	
}

void CGameStateRun_Home::OnInit()  
{

	bm_join.LoadBitmap(INGAME_JOIN);
	bm_loading.LoadBitmap(LOADING);
	character.LoadBitmap();
	Map_Home.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");	

	ani_light_beam.SetDelayCount(1);
	ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255,0));
	ani_light_beam.AddBitmap(LIGHT_BEAM02, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM03, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM04, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));

	ani_light_beam.SetTopLeft(0, 0);
}

void CGameStateRun_Home::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = 0x20;
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	

	if (flags == 0) {		//��space �[�J���
		if (nChar == KEY_SPACE)
			flags = 1;		//����i�J�C��
	}
	else {
		
		if (nChar == KEY_DOWN || nChar == KEY_S)
			character.SetMovingDown(true);
		if (nChar == KEY_UP || nChar == KEY_W)
			character.SetMovingUp(true);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			character.SetMovingLeft(true);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			character.SetMovingRight(true);
		/*
		if (nChar == KEY_SPACE)
			character.Dash();
		*/
	}
		

}

void CGameStateRun_Home::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = 0x20;
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	
	if (nChar == KEY_DOWN || nChar == KEY_S)
		character.SetMovingDown(false);
	if (nChar == KEY_UP || nChar == KEY_W)
		character.SetMovingUp(false);
	if (nChar == KEY_LEFT || nChar == KEY_A)
		character.SetMovingLeft(false);
	if (nChar == KEY_RIGHT || nChar == KEY_D)
		character.SetMovingRight(false);

}

void CGameStateRun_Home::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Home::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Home::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun_Home::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Home::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Home::OnShow()
{
	if (counter < 0) {
		Map_Home.OnShowBackground();
		
		if (flags == 0)
			bm_join.ShowBitmap();
		else
		{

			if (!ani_light_beam.IsFinalBitmap())
			{
				ani_light_beam.OnMove();
				ani_light_beam.OnShow();

			}
			else
			{
				character.OnShow();
				Map_Home.OnShowWall();
			}
		}
	}
	else
		bm_loading.ShowBitmap();
	
}

////////////////////////////////////////////////////////////////////////////////////


CGameStateRun_Options::CGameStateRun_Options(CGame *g)
	: CGameState(g)
{

}

CGameStateRun_Options::~CGameStateRun_Options()
{

}

void CGameStateRun_Options::OnBeginState()
{

}

void CGameStateRun_Options::OnMove()							
{
	bm_option.SetTopLeft(0, 0);
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

}

void CGameStateRun_Options::OnInit()  								
{
	bm_option.LoadBitmap(MENU_OPTIONS);
}

void CGameStateRun_Options::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	const char KEY_ENTER = 0xD;
	const char KEY_SPACE = 0x20;
	const char KEY_BACKSPACE = 0X08;

	CAudio::Instance()->Play(AUDIO_BE);

	if (nChar == KEY_SPACE || nChar == KEY_BACKSPACE)
			GotoGameState(GAME_STATE_INIT);

}

void CGameStateRun_Options::OnShow()
{
	bm_option.ShowBitmap();

}
}