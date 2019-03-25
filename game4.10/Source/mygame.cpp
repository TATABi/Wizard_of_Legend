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

	int m1[23] = { MENU_INIT_02,MENU_INIT_04,MENU_INIT_06,MENU_INIT_08,MENU_INIT_10,MENU_INIT_12,MENU_INIT_16,MENU_INIT_18,MENU_INIT_20,MENU_INIT_22,MENU_INIT_24,
				   MENU_INIT_26, MENU_INIT_28, MENU_INIT_30, MENU_INIT_32, MENU_INIT_34, MENU_INIT_36, MENU_INIT_38, MENU_INIT_40, MENU_INIT_42, MENU_INIT_44,
				   MENU_INIT_46, MENU_INIT_48 };
	for (int i = 0; i < 23; i++)
		ani_menu_1.AddBitmap(m1[i]);

	int m2[11] = { MENU_ENTERMENU_01, MENU_ENTERMENU_02, MENU_ENTERMENU_03, MENU_ENTERMENU_04, MENU_ENTERMENU_05, MENU_ENTERMENU_06, MENU_ENTERMENU_07,
				   MENU_ENTERMENU_08, MENU_ENTERMENU_09, MENU_ENTERMENU_10, MENU_ENTERMENU_11 };
	for (int i = 0; i < 11; i++)
		ani_menu_2.AddBitmap(m2[i]);

	ani_menu_1.SetDelayCount(2);
	ani_menu_2.SetDelayCount(1);

	bm_option.LoadBitmap(MENU_ENTERMENU_OPTIONS);
	bm_quit.LoadBitmap(MENU_ENTERMENU_QUIT);
	bm_single_player.LoadBitmap(MENU_ENTERMENU_SINGLE_PLAYER);

	//Sleep(200);
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
// Home
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_Home::CGameStateRun_Home(CGame *g)
: CGameState(g), map(740, 918)			//����b�a�ϤW����m			
{
	
}

CGameStateRun_Home::~CGameStateRun_Home()
{
	delete ui;
}

void CGameStateRun_Home::OnBeginState()
{
	ui = new UI();
	ui->LoadBitmap();
	delay_counter = 30 * 1; // 1 seconds
	map.Initialize(740, 918);
	character.Initialize();

	//�q��L�����^�Ӥ��ΦA���X�{�[�J���
	if (ani_light_beam.IsFinalBitmap())
	{
		ani_light_beam.Reset();
		flags = FLAG_HOME_NORMAL;
	}
	else 
		flags = FLAG_JOIN;

	CAudio::Instance()->Stop(AUDIO_TITLE);
	CAudio::Instance()->Play(AUDIO_HOME, true);
	CAudio::Instance()->Stop(AUDIO_TOWN);
}

void CGameStateRun_Home::OnMove()					
{
	
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if(delay_counter > -1)
		delay_counter--;

	bm_join.SetTopLeft(100, 100);
	bm_loading.SetTopLeft(0, 0);
	character.OnMove(&map);
	map.OnMove();
	box.OnMove();
	ui->OnMove();

}

void CGameStateRun_Home::OnInit()  
{
	bm_join.LoadBitmap(JOIN);
	bm_loading.LoadBitmap(LOADING);
	character.LoadBitmap();
	map.LoadBitmap();
	box.LoadBitmap();
	
	pauseMenu.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_PULL, "sounds\\pull.mp3");
	CAudio::Instance()->Load(AUDIO_PUTTING, "sounds\\putting.mp3");
	CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");	
	CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");
	CAudio::Instance()->Load(AUDIO_ARRIVAL, "sounds\\arrival.mp3");
	CAudio::Instance()->Load(AUDIO_PULL2, "sounds\\pull2.mp3");

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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_W = 0x57;
	const char KEY_S = 0x53;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	const char KEY_F = 0x46;
	
	if (delay_counter < 0)
	{
		switch (flags)
		{
		case FLAG_HOME_NORMAL:
			//�i�J�C���A�S���}�ҥ�����
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
			if (nChar == KEY_F && map.GetCharacterStatus() == 1)
			{
				//delete ui;
				GotoGameState(GAME_STATE_RUN_TOWN);			//������town
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 2)
			{
				box.Open(true);
				flags = FLAG_BOX;		//�}�ҹD��c
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 3)
			{
				//�}�Ү�		
			}

			if (nChar == KEY_ESC)	//PAUSED���
			{
				pauseMenu.Paused(true);
				flags = FLAG_HOME_PAUSED;
			}
			break;


		case FLAG_JOIN:

			if (nChar == KEY_SPACE)		// �[�J�C�����ܿ��
			{
				flags = FLAG_HOME_NORMAL;				// ����i�J�C��
			}
			break;

		case FLAG_BOX:							//�D��c���
			if (nChar == KEY_ESC)
			{
				box.Open(false);
				flags = FLAG_HOME_NORMAL;
			}
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{	
				CAudio::Instance()->Play(AUDIO_PULL2, false);
				box.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				CAudio::Instance()->Play(AUDIO_PULL2, false);
				box.Up();
			}
			if (nChar == KEY_SPACE)
			{
				CAudio::Instance()->Play(AUDIO_PULL, false);
				box.OpenOpen(true);
				flags = FLAG_BOX_ITEM;
			}
			break;

		case FLAG_BOX_ITEM:
			
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				box.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
				box.Up();		
			}
			if (nChar == KEY_LEFT || nChar == KEY_A)
			{
				box.Left();
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
			}
			if (nChar == KEY_RIGHT || nChar == KEY_D)
			{
				box.Right();
				CAudio::Instance()->Play(AUDIO_PUTTING, false);
			}
			//if (nChar == KEY_SPACE)
			
			if (nChar == KEY_ESC)
			{
				box.OpenOpen(false);
				flags = FLAG_BOX;
			}
			break;

		case FLAG_HOME_PAUSED:									//�Ȱ����
			if (nChar == KEY_DOWN || nChar == KEY_S)
				pauseMenu.NextPausedMenu();
			if (nChar == KEY_UP || nChar == KEY_W)
				pauseMenu.PrePausedMenu();
			if (nChar == KEY_ESC)
			{
				flags = FLAG_HOME_NORMAL;
				pauseMenu.Paused(false);
			}
			if (nChar == KEY_SPACE)
			{
				int temp;
				temp = pauseMenu.EnterPauseMenu();

				switch (temp)
				{
				case 0:
					flags = FLAG_HOME_NORMAL;
					break;
				case 1:
					flags = FLAG_JOIN;
					ani_light_beam.Reset();
					map.Initialize(740, 918);
					CAudio::Instance()->Play(AUDIO_TITLE, true);
					CAudio::Instance()->Stop(AUDIO_HOME);
					GotoGameState(GAME_STATE_INIT);
				case 2:
					flags = FLAG_HOME_OPTIONS;
					break;
				case 3:
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
					break;
				}
			}
			break;

		case FLAG_HOME_OPTIONS:		//�I�ioptions
			if (nChar == KEY_ESC || nChar == KEY_SPACE)
			{
				pauseMenu.PrePausedMenu();
				pauseMenu.PrePausedMenu();
				flags = FLAG_HOME_PAUSED;
			}
		}
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
	if (delay_counter < 0)
	{
		map.OnShowBackground();
		
		if (flags == 1)
			bm_join.ShowBitmap();
		else
		{
			if (!ani_light_beam.IsFinalBitmap())
			{
				CAudio::Instance()->Play(AUDIO_ARRIVAL, false);
				ani_light_beam.OnMove();
				ani_light_beam.OnShow();
			}
			else
			{
				character.OnShow();
				map.OnShowWall();
				map.OnShowPressF();
				box.OnShow();
				ui->OnShow();
				pauseMenu.OnShow();
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


/////////////////////////////////////////////////////////////////////////////
////Town
/////////////////////////////////////////////////////////////////////////////
CGameStateRun_Town::CGameStateRun_Town(CGame *g)
	: CGameState(g), map(770, 1065)			//����b�a�ϤW����m			
{
	
}

CGameStateRun_Town::~CGameStateRun_Town()
{
	//delete ui;
}

void CGameStateRun_Town::OnBeginState()
{
	ui = new UI();
	ui->LoadBitmap();
	delay_counter = 30 * 1; // 1 seconds
	flags = 0;
	character.Initialize();
	map.Initialize(770, 1065);
	CAudio::Instance()->Stop(AUDIO_HOME);
	CAudio::Instance()->Play(AUDIO_TOWN, true);
}

void CGameStateRun_Town::OnMove()
{

	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if (delay_counter > -1)
		delay_counter--;

	bm_loading.SetTopLeft(0, 0);
	character.OnMove(&map);
	map.OnMove();
	ui->OnMove();

}

void CGameStateRun_Town::OnInit()
{
	bm_loading.LoadBitmap(LOADING);
	character.LoadBitmap();
	map.LoadBitmap();
	
	pauseMenu.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_TOWN, "sounds\\TownBGM.wav");

}

void CGameStateRun_Town::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
	const char KEY_F = 0x46;
	if (delay_counter < 0)
	{
		switch (flags)
		{
		case 0:			//�@�몬�A�A�S���}�ҥ�����A�i�H�ʶR�F��A�����A�i�ǰe��
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
			if (nChar == KEY_F && map.GetCharacterStatus() == 1)
			{
				//delete ui;
				GotoGameState(GAME_STATE_RUN_HOME);		//����������Home
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 2)
			{
				//�i���d
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 3)
			{
				//�ʶR�D��1
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 4)
			{
				//�ʶR�D��2
			}

			if (nChar == KEY_F && map.GetCharacterStatus() == 5)
			{
				//�ʶR�D��3
			}

			if (nChar == KEY_ESC)	//PAUSED���
			{
				pauseMenu.Paused(true);
				flags = FLAG_TOWN_PAUSED;
			}

			break;

		case FLAG_TOWN_PAUSED:									//�Ȱ����
			if (nChar == KEY_DOWN || nChar == KEY_S)
				pauseMenu.NextPausedMenu();
			if (nChar == KEY_UP || nChar == KEY_W)
				pauseMenu.PrePausedMenu();
			if (nChar == KEY_ESC)
			{
				flags = FLAG_TOWN_NORMAL;
				pauseMenu.Paused(false);
			}
			if (nChar == KEY_SPACE)
			{
				int temp;
				temp = pauseMenu.EnterPauseMenu();

				switch (temp)
				{
				case 0:
					flags = FLAG_TOWN_NORMAL;
					break;
				case 1:
					flags = FLAG_JOIN;
					CAudio::Instance()->Play(AUDIO_TITLE, true);
					CAudio::Instance()->Stop(AUDIO_TOWN);
					GotoGameState(GAME_STATE_INIT);
				case 2:
					flags = FLAG_TOWN_OPTIONS;
					break;
				case 3:
					PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
					break;
				}
			}
			break;

		case FLAG_TOWN_OPTIONS:		//�I�ioptions
			if (nChar == KEY_ESC || nChar == KEY_SPACE)
			{
				pauseMenu.PrePausedMenu();
				pauseMenu.PrePausedMenu();
				flags = FLAG_TOWN_PAUSED;
			}
		
		}
		
	}

}

void CGameStateRun_Town::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CGameStateRun_Town::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Town::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Town::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun_Town::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Town::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun_Town::OnShow()
{
	if (delay_counter < 0)
	{
		map.OnShowBackground();
		character.OnShow();
		map.OnShowWall();
		map.OnShowPressF();
		ui->OnShow();
		pauseMenu.OnShow();
	}
	else
		bm_loading.ShowBitmap();
}

}
