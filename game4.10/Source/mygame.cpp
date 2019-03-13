#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{

	ShowInitProgress(0);	// 一開始的loading進度為0%

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
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
	else{
		if (flags == 0)
			flags = 1;
	}
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
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
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
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
// 這個class為遊戲的結束狀態(Game Over)
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
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_Home::CGameStateRun_Home(CGame *g)
: CGameState(g), Map_Home(74, 91)		//角色在地圖上的位置			///初始化地圖座標 Map_Home(755,928)	
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
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
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
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	

	if (flags == 0) {		//按space 加入選單
		if (nChar == KEY_SPACE)
			flags = 1;		//角色進入遊戲
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
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
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

void CGameStateRun_Home::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun_Home::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun_Home::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun_Home::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun_Home::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
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
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
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