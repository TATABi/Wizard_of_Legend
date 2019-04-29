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
{}

void CGameStateInit::OnInit()
{
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	_controller.Initialize();

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
	if(_controller.IsSwitchGameState())
		GotoGameState(_controller.GotoGameState());
	_controller.OnShow();
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{}

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
	sprintf(str, "Game Over ! (%d)", _counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}



/////////////////////////////////////////////////////////////////////////////
// Home
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_Home::CGameStateRun_Home(CGame *g)
: CGameState(g)//, _map(740, 918, &Global_Class::g_character)	//����b�a�ϤW����m			
{}

CGameStateRun_Home::~CGameStateRun_Home()
{}

void CGameStateRun_Home::OnBeginState()
{

	/*
	_delayCounter = 30 * 1; // 1 seconds
	_map.Initialize(740, 918);
	Global_Class::g_character.Initialize(_map.GetCharacterPosition());

	//�q��L�����^�Ӥ��ΦA���X�{�[�J���
	if (_ani_light_beam.IsFinalBitmap())
	{
		_ani_light_beam.Reset();
		_flag = FLAG_HOME_NORMAL;
	}
	else 
		_flag = FLAG_JOIN;

	CAudio::Instance()->Stop(AUDIO_TITLE);
	CAudio::Instance()->Play(AUDIO_HOME, true);
	CAudio::Instance()->Stop(AUDIO_TOWN);

	*/

	_controller.Begin();
}

void CGameStateRun_Home::OnMove()					
{
	/*
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if(_delayCounter > -1)
		_delayCounter--;

	_bm_join.SetTopLeft(100, 100);
	_bm_loading.SetTopLeft(0, 0);
	Global_Class::g_character.OnMove(&_map);
	_map.OnMove();
	_box.OnMove();
	_book.OnMove();
	Global_Class::g_bag.OnMove(Global_Class::g_items.GetItemInBag());
	Global_Class::g_ui.OnMove();
	Global_Class::g_items.Effect();
	*/

	_controller.OnMove();


}

void CGameStateRun_Home::OnInit()  
{
	/*
	_bm_join.LoadBitmap(JOIN);
	_bm_loading.LoadBitmap(LOADING);
	_map.LoadBitmap();
	_box.LoadBitmap();
	_book.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_PULL, "sounds\\pull.mp3");
	CAudio::Instance()->Load(AUDIO_PUTTING, "sounds\\putting.mp3");
	CAudio::Instance()->Load(AUDIO_HOME, "sounds\\HomeBGM.wav");	
	CAudio::Instance()->Load(AUDIO_ARRIVAL, "sounds\\arrival.mp3");
	CAudio::Instance()->Load(AUDIO_PULL2, "sounds\\pull2.mp3");
	CAudio::Instance()->Load(AUDIO_DASH, "sounds\\dash.mp3");

	_ani_light_beam.SetDelayCount(1);
	_ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255, 0));
	_ani_light_beam.AddBitmap(LIGHT_BEAM02, RGB(50, 255, 0));
	_ani_light_beam.AddBitmap(LIGHT_BEAM03, RGB(50, 255, 0));
	_ani_light_beam.AddBitmap(LIGHT_BEAM04, RGB(50, 255, 0));
	_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
	_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
	_ani_light_beam.SetTopLeft(0, 0);
	*/

	_controller.Initialize();
}

void CGameStateRun_Home::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*
	if (_delayCounter < 0)
	{
		switch (_flag)
		{
		case FLAG_HOME_NORMAL:
			//�i�J�C���A�S���}�ҥ�����
			if (nChar == KEY_DOWN || nChar == KEY_S)
				Global_Class::g_character.SetMovingDown(true);
			if (nChar == KEY_UP || nChar == KEY_W)
				Global_Class::g_character.SetMovingUp(true);
			if (nChar == KEY_LEFT || nChar == KEY_A)
				Global_Class::g_character.SetMovingLeft(true);
			if (nChar == KEY_RIGHT || nChar == KEY_D)
				Global_Class::g_character.SetMovingRight(true);
			if (nChar == KEY_SPACE)
			{
				Global_Class::g_character.Dash();
			}
			if (nChar == KEY_F && _map.GetCharacterStatus() == 1)
			{
				GotoGameState(GAME_STATE_RUN_TOWN);			//������town
			}
			if (nChar == KEY_F && _map.GetCharacterStatus() == 2)
			{
				_box.Open(true);
				_flag = FLAG_BOX;		//�}�ҹD��c
			}

			if (nChar == KEY_F && _map.GetCharacterStatus() == 3)
			{
				_book.Open(true);		//�}�Ү�
				_flag = FLAG_BOOK;
			}

			if (nChar == KEY_ESC)	//PAUSED���
			{
				Global_Class::g_pauseMenu.Paused(true);
				_flag = FLAG_HOME_PAUSED;
			}

			if (nChar == KEY_TAB)
			{
				Global_Class::g_bag.Open(true);
				_flag = FLAG_HOME_BAG;
			}
			break;

		case FLAG_JOIN:

			if (nChar == KEY_SPACE)		// �[�J�C�����ܿ��
			{
				_flag = FLAG_HOME_NORMAL;				// ����i�J�C��
			}
			break;

		case FLAG_BOX:							//�D��c���
			if (nChar == KEY_ESC)
			{
				_box.Open(false);
				_flag = FLAG_HOME_NORMAL;
			}
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{	
				_box.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				_box.Up();
			}
			if (nChar == KEY_SPACE)
			{
				_box.OpenOpen(true);
				_flag = FLAG_BOX_ITEM;
			}
			break;

		case FLAG_BOX_ITEM:
			
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				_box.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				_box.Up();
			}
			if (nChar == KEY_LEFT || nChar == KEY_A)
			{
				_box.Left();
			}
			if (nChar == KEY_RIGHT || nChar == KEY_D)
			{
				_box.Right();
			}
			if (nChar == KEY_SPACE)
			{
				if (_box.Equip(&Global_Class::g_items)) {
					_box.OpenOpen(false);
					_flag = FLAG_BOX;
				}
				else {
					CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				}
			}
			if (nChar == KEY_ESC)
			{
				_box.OpenOpen(false);
				_flag = FLAG_BOX;
			}
			break;

		case FLAG_HOME_PAUSED:									//�Ȱ����
			if (nChar == KEY_DOWN || nChar == KEY_S)
				Global_Class::g_pauseMenu.NextPausedMenu();
			if (nChar == KEY_UP || nChar == KEY_W)
				Global_Class::g_pauseMenu.PrePausedMenu();
			if (nChar == KEY_ESC)
			{
				_flag = FLAG_HOME_NORMAL;
				Global_Class::g_pauseMenu.Paused(false);
			}
			if (nChar == KEY_SPACE)
			{
				int temp;
				temp = Global_Class::g_pauseMenu.EnterPauseMenu();

				switch (temp)
				{
				case 0:
					_flag = FLAG_HOME_NORMAL;
					break;
				case 1:
					_flag = FLAG_JOIN;
					_ani_light_beam.Reset();
					_map.Initialize(740, 918);
					CAudio::Instance()->Play(AUDIO_TITLE, true);
					CAudio::Instance()->Stop(AUDIO_HOME);
					GotoGameState(GAME_STATE_INIT);
					break;
				case 2:
					_flag = FLAG_HOME_OPTIONS;
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
				Global_Class::g_pauseMenu.PrePausedMenu();
				Global_Class::g_pauseMenu.PrePausedMenu();
				_flag = FLAG_HOME_PAUSED;
			}
			break;
		case FLAG_HOME_BAG:
			if (nChar == KEY_TAB || nChar == KEY_ESC)
			{
				Global_Class::g_bag.Open(false);
				_flag = FLAG_HOME_NORMAL;
			}
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				Global_Class::g_bag.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				Global_Class::g_bag.Up();
			}
			if (nChar == KEY_LEFT || nChar == KEY_A)
			{
				Global_Class::g_bag.Left();
			}
			if (nChar == KEY_RIGHT || nChar == KEY_D)
			{
				Global_Class::g_bag.Right();
			}

			break;

		case FLAG_BOOK:
			
			if (nChar == KEY_ESC)
			{
				_book.Open(false);
				_flag = FLAG_HOME_NORMAL;
			}
			
			if (nChar == KEY_DOWN || nChar == KEY_S)
			{
				_book.Down();
			}
			if (nChar == KEY_UP || nChar == KEY_W)
			{
				_book.Up();
			}
			if (nChar == KEY_LEFT || nChar == KEY_A)
			{
				_book.Left();
			}
			if (nChar == KEY_RIGHT || nChar == KEY_D)
			{
				_book.Right();
			}
			break;
			
		}
	}
	*/

	_controller.OnKeyDown(nChar, nRepCnt, nFlags);
	
}

void CGameStateRun_Home::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*
	if (nChar == KEY_DOWN || nChar == KEY_S)
		Global_Class::g_character.SetMovingDown(false);
	if (nChar == KEY_UP || nChar == KEY_W)
		Global_Class::g_character.SetMovingUp(false);
	if (nChar == KEY_LEFT || nChar == KEY_A)
		Global_Class::g_character.SetMovingLeft(false);
	if (nChar == KEY_RIGHT || nChar == KEY_D)
		Global_Class::g_character.SetMovingRight(false);
	*/

	_controller.OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGameStateRun_Home::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//_map.CharacterUseSkill(2, point.x, point.y);

	_controller.OnLButtonDown(nFlags, point);
}

void CGameStateRun_Home::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//_map.CharacterUseSkill(3, point.x, point.y);
	_controller.OnRButtonDown(nFlags, point);
}

void CGameStateRun_Home::OnShow()
{
	/*
	if (_delayCounter < 0)
	{
		_map.OnShowBackground();
		if (_flag == 1)
			_bm_join.ShowBitmap();
		else
		{
			if (!_ani_light_beam.IsFinalBitmap())
			{
				CAudio::Instance()->Play(AUDIO_ARRIVAL, false);
				_ani_light_beam.OnMove();
				_ani_light_beam.OnShow();
			}
			else
			{
				_map.OnShow();
				_map.OnShowWall();
				_map.OnShowPressF();
				_box.OnShow(&Global_Class::g_items);
				_book.OnShow();
				Global_Class::g_ui.OnShow();
				Global_Class::g_bag.OnShow();
				Global_Class::g_pauseMenu.OnShow();
			}		
		}
	}
	else
		_bm_loading.ShowBitmap();
		*/
	_controller.OnShow();

	if (_controller.IsSwitchGameState())
	{
		GotoGameState(_controller.GameState());
	}
}


/////////////////////////////////////////////////////////////////////////////
////Town
/////////////////////////////////////////////////////////////////////////////
CGameStateRun_Town::CGameStateRun_Town(CGame *g)
: CGameState(g), _map(770, 1065, &Global_Class::g_character)//_map(770, 1065. &g_character)			//����b�a�ϤW����m			
{}

CGameStateRun_Town::~CGameStateRun_Town()
{}

void CGameStateRun_Town::OnBeginState()
{
	_delayCounter = 30 * 1; // 1 seconds
	_flag = 0;
	Global_Class::g_character.Initialize(_map.GetCharacterPosition());
	_map.Initialize(770, 1065);
	CAudio::Instance()->Stop(AUDIO_HOME);
	CAudio::Instance()->Play(AUDIO_TOWN, true);
	
	//////�����H���D��/////

	_item_store.Shelf(&Global_Class::g_items);
	
}

void CGameStateRun_Town::OnMove()
{
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

	if (_delayCounter > -1)
		_delayCounter--;

	_bm_loading.SetTopLeft(0, 0);
	Global_Class::g_character.OnMove(&_map);
	_map.OnMove();
	Global_Class::g_bag.OnMove(Global_Class::g_items.GetItemInBag());
	Global_Class::g_ui.OnMove();
	Global_Class::g_items.Effect();
	_item_store.SetXY(_map.GetCharacterPosition());

}

void CGameStateRun_Town::OnInit()
{
	
	_bm_loading.LoadBitmap(LOADING);
	_map.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_TOWN, "sounds\\TownBGM.wav");
	CAudio::Instance()->Load(AUDIO_BUY, "sounds\\buy.mp3");
	CAudio::Instance()->Load(AUDIO_NOMONEY, "sounds\\nomoney.mp3");

	_item_store.LoadBitmap();
}

void CGameStateRun_Town::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (_delayCounter < 0)
	{
		switch (_flag)
		{
		case FLAG_TOWN_NORMAL:			//�@�몬�A�A�S���}�ҥ�����A�i�H�ʶR�F��A�����A�i�ǰe��
			
			if (nChar == KEY_DOWN || nChar == KEY_S)
				Global_Class::g_character.SetMovingDown(true);
			if (nChar == KEY_UP || nChar == KEY_W)
				Global_Class::g_character.SetMovingUp(true);
			if (nChar == KEY_LEFT || nChar == KEY_A)
				Global_Class::g_character.SetMovingLeft(true);
			if (nChar == KEY_RIGHT || nChar == KEY_D)
				Global_Class::g_character.SetMovingRight(true);
			if (nChar == KEY_SPACE)
			{
				if (Global_Class::g_character.CanDash())
				{
					Global_Class::g_character.Dash();
					CAudio::Instance()->Play(AUDIO_DASH, false);
				}
			}
			if (nChar == KEY_F && _map.GetCharacterStatus() == 1)
			{
				GotoGameState(GAME_STATE_RUN_HOME);		//����������Home
			}

			if (nChar == KEY_F && _map.GetCharacterStatus() == 2)
			{
				//�i���d
			}

			if (nChar == KEY_F && _map.GetCharacterStatus() == 3)	//�R�D��1
			{
				
				if(_item_store.Buy(0, &Global_Class::g_items))
					CAudio::Instance()->Play(AUDIO_BUY, false);
				else
					CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				
			}

			if (nChar == KEY_F && _map.GetCharacterStatus() == 4)	//�R�D��2
			{
				
				if (_item_store.Buy(1, &Global_Class::g_items))
					CAudio::Instance()->Play(AUDIO_BUY, false);
				else
					CAudio::Instance()->Play(AUDIO_NOMONEY, false);
			}
			

			if (nChar == KEY_F && _map.GetCharacterStatus() == 5)	//�R�D��3
			{
				if (_item_store.Buy(2, &Global_Class::g_items))
					CAudio::Instance()->Play(AUDIO_BUY, false);
				else
					CAudio::Instance()->Play(AUDIO_NOMONEY, false);
				
			}

			if (nChar == KEY_ESC)	//PAUSED���
			{
				Global_Class::g_pauseMenu.Paused(true);
				_flag = FLAG_TOWN_PAUSED;
			}

			if (nChar == KEY_TAB)
			{
				Global_Class::g_bag.Open(true);
				_flag = FLAG_TOWN_BAG;
			}
			break;

		case FLAG_TOWN_PAUSED:									//�Ȱ����
			if (nChar == KEY_DOWN || nChar == KEY_S)
				Global_Class::g_pauseMenu.NextPausedMenu();
			if (nChar == KEY_UP || nChar == KEY_W)
				Global_Class::g_pauseMenu.PrePausedMenu();
			if (nChar == KEY_ESC)
			{
				_flag = FLAG_TOWN_NORMAL;
				Global_Class::g_pauseMenu.Paused(false);
			}
			if (nChar == KEY_SPACE)
			{
				int temp;
				temp = Global_Class::g_pauseMenu.EnterPauseMenu();

				switch (temp)
				{
				case 0:
					_flag = FLAG_TOWN_NORMAL;
					break;
				case 1:
					CAudio::Instance()->Play(AUDIO_TITLE, true);
					CAudio::Instance()->Stop(AUDIO_TOWN);
					GotoGameState(GAME_STATE_INIT);
					break;
				case 2:
					_flag = FLAG_TOWN_OPTIONS;
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
				Global_Class::g_pauseMenu.PrePausedMenu();
				Global_Class::g_pauseMenu.PrePausedMenu();
				_flag = FLAG_TOWN_PAUSED;
			}
			break;

		case FLAG_TOWN_BAG:
			if (nChar == KEY_TAB || nChar == KEY_ESC)
			{
				Global_Class::g_bag.Open(false);
				_flag = FLAG_TOWN_NORMAL;
			}
			break;
		}	
	}
}

void CGameStateRun_Town::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == KEY_DOWN || nChar == KEY_S)
		Global_Class::g_character.SetMovingDown(false);
	if (nChar == KEY_UP || nChar == KEY_W)
		Global_Class::g_character.SetMovingUp(false);
	if (nChar == KEY_LEFT || nChar == KEY_A)
		Global_Class::g_character.SetMovingLeft(false);
	if (nChar == KEY_RIGHT || nChar == KEY_D)
		Global_Class::g_character.SetMovingRight(false);
}

void CGameStateRun_Town::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	_map.CharacterUseSkill(2, point.x, point.y);
}

void CGameStateRun_Town::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	_map.CharacterUseSkill(3, point.x, point.y);
}

void CGameStateRun_Town::OnShow()
{
	if (_delayCounter < 0)
	{
		_map.OnShowBackground();
		_item_store.OnShow(_map.GetCharacterPosition());
		_map.OnShow();
		_map.OnShowWall();
		_map.OnShowPressF();
		Global_Class::g_ui.OnShow();
		Global_Class::g_bag.OnShow();
		Global_Class::g_pauseMenu.OnShow();
	}
	else
		_bm_loading.ShowBitmap();
}

}
