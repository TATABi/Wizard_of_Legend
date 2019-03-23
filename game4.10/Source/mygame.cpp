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
// Home
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_Home::CGameStateRun_Home(CGame *g)
: CGameState(g), map_home(740, 918)			//角色在地圖上的位置			
{
	
}

CGameStateRun_Home::~CGameStateRun_Home()
{

}

void CGameStateRun_Home::OnBeginState()
{
	delay_counter = 30 * 1; // 1 seconds
	flags = 0;
	character.Initialize();
	myUI.Initialize();
	CAudio::Instance()->Stop(AUDIO_TITLE);
	CAudio::Instance()->Play(AUDIO_HOME, true);
}

void CGameStateRun_Home::OnMove()					
{

	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if(delay_counter > -1)
		delay_counter--;

	bm_join.SetTopLeft(100, 100);
	bm_loading.SetTopLeft(0, 0);
	character.OnMove(&map_home);
	map_home.OnMove();
	box.OnMove();
	testInt.SetTopLeft(320, 450);
	myUI.OnMove();
}

void CGameStateRun_Home::OnInit()  
{
	bm_join.LoadBitmap(JOIN);
	bm_loading.LoadBitmap(LOADING);
	character.LoadBitmap();
	map_home.LoadBitmap();
	box.LoadBitmap();
	testInt.LoadBitmap();
	testInt.SetInteger(100);
	myUI.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");	
	CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");
	
	ani_light_beam.SetDelayCount(1);
	ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255, 0));
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
	const char KEY_F = 0x46;
	
	switch (flags) 
	{
	case 0:
		if (nChar == KEY_SPACE)		// 加入遊戲提示選單
			flags = 1;				// 角色進入遊戲
		break;
	
	case 1:							//進入遊戲，沒有開啟任何選單
		if (nChar == KEY_DOWN || nChar == KEY_S)
			character.SetMovingDown(true);
		if (nChar == KEY_UP || nChar == KEY_W)
			character.SetMovingUp(true);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			character.SetMovingLeft(true);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			character.SetMovingRight(true);
		if (nChar == KEY_SPACE)
		{
			if (character.CanDash())
			{
				character.Dash();
				CAudio::Instance()->Play(AUDIO_DASH, false);
			}
		}
		if (nChar == KEY_F && map_home.GetCharacterStatus() == 1)
		{
			GotoGameState(GAME_STATE_RUN_TOWN);
		}

		if (nChar == KEY_F && map_home.GetCharacterStatus() == 2)
		{
			box.Open(true);
			flags = 2;		//開啟道具箱
		}

		if (nChar == KEY_F && map_home.GetCharacterStatus() == 3)
		{
			//開啟書		flags = 3;
		}
		break;

	case 2:							//道具箱選單
		if (nChar == KEY_ESC)
		{
			box.Open(false);
			flags = 1;
		}
		if (nChar == KEY_DOWN || nChar == KEY_S)
			box.Next();
		if (nChar == KEY_UP || nChar == KEY_W)
			box.Previous();
		break;

	case 3:
		break;

	case 4 :
		/*
		if (nChar == KEY_DOWN || nChar == KEY_S)
			testInt.SetInteger(CharacterData::money);
		if (nChar == KEY_UP || nChar == KEY_W)
			testInt.Add(1);
			*/
		break;
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
	if (delay_counter < 0)
	{
		map_home.OnShowBackground();
	
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
				map_home.OnShowWall();
				map_home.OnShowPressF();
				box.OnShow();
				testInt.ShowBitmap();
				myUI.OnShow();
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


/////////////////////////////////////////////////////////////////////////////
////Town
/////////////////////////////////////////////////////////////////////////////
CGameStateRun_Town::CGameStateRun_Town(CGame *g)
	: CGameState(g), map_town(794, 1094)			//角色在地圖上的位置			
{

}

CGameStateRun_Town::~CGameStateRun_Town()
{

}

void CGameStateRun_Town::OnBeginState()
{
	delay_counter = 30 * 1; // 1 seconds
	flags = 0;
	character.Initialize();

	//CAudio::Instance()->Stop(AUDIO_TITLE);
	//CAudio::Instance()->Play(AUDIO_HOME, true);
}

void CGameStateRun_Town::OnMove()
{

	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if (delay_counter > -1)
		delay_counter--;

	bm_loading.SetTopLeft(0, 0);
	character.OnMove(&map_town);
	map_town.OnMove();

}

void CGameStateRun_Town::OnInit()
{
	bm_loading.LoadBitmap(LOADING);
	character.LoadBitmap();
	map_town.LoadBitmap();
	
	//CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");
	//CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");

	ani_light_beam.SetDelayCount(1);
	ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM02, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM03, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM04, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
	ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
	ani_light_beam.SetTopLeft(0, 0);

}

void CGameStateRun_Town::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
	const char KEY_F = 0x46;

	switch (flags)
	{
	case 0:			//一般狀態，沒有開啟任何選單，可以購買東西，走路，進傳送門
		if (nChar == KEY_DOWN || nChar == KEY_S)
			character.SetMovingDown(true);
		if (nChar == KEY_UP || nChar == KEY_W)
			character.SetMovingUp(true);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			character.SetMovingLeft(true);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			character.SetMovingRight(true);
		if (nChar == KEY_SPACE)
		{
			if (character.CanDash())
			{
				character.Dash();
				CAudio::Instance()->Play(AUDIO_DASH, false);
			}
		}
		if (nChar == KEY_F && map_town.GetCharacterStatus() == 1)
		{
			GotoGameState(GAME_STATE_RUN_HOME);		//切換場景到Home
		}

		if (nChar == KEY_F && map_town.GetCharacterStatus() == 2)
		{
			//進關卡
		}

		if (nChar == KEY_F && map_town.GetCharacterStatus() == 3)
		{
			//購買道具1
		}

		if (nChar == KEY_F && map_town.GetCharacterStatus() == 4)
		{
			//購買道具2
		}

		if (nChar == KEY_F && map_town.GetCharacterStatus() == 5)
		{
			//購買道具3
		}
		break;
	}

}

void CGameStateRun_Town::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CGameStateRun_Town::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun_Town::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun_Town::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun_Town::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun_Town::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun_Town::OnShow()
{
	if (delay_counter < 0)
	{
		map_town.OnShowBackground();

		if (!ani_light_beam.IsFinalBitmap())		//進場動畫
		{
			ani_light_beam.OnMove();
			ani_light_beam.OnShow();
		}
		else
		{
			character.OnShow();
			map_town.OnShowWall();
			map_town.OnShowPressF();
		}

	}
	else
		bm_loading.ShowBitmap();
}

}
