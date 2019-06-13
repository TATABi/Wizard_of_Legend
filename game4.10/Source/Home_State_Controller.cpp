#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Home_State_Controller.h"
#include "GameData.h"
#include "CharacterData.h"

namespace game_framework {
	Home_State_Controller::Home_State_Controller():Controller(), _map(HOME_CHARACTER_XY[0], HOME_CHARACTER_XY[1]){}

	void Home_State_Controller::Begin()
	{
		LoadMemento(Town_Or_Home);
		SaveMemento(Town_Or_Home);
		_game_state_num = -1;
		_isSwitch = false;
		_delayCounter = 30 * 1; // 1 seconds
		_map.Initialize(HOME_CHARACTER_XY[0], HOME_CHARACTER_XY[1]);	
		Character::Instance().Initialize(_map.GetCharacterPosition());
		CharacterData::Instance().ResetStatus();
		UI::Instance().Initialize();
		_map.AddEnemy();
		//�q��L�����^�Ӥ��ΦA���X�{�[�J���
		if (_ani_light_beam.IsFinalBitmap())
		{
			_ani_light_beam.Reset();
			_flag = FLAG_HOME_NORMAL;
		}
		else
			_flag = FLAG_JOIN;
		CAudio::Instance()->StopAll();
		CAudio::Instance()->Play(AUDIO_HOME, true);
	}

	void Home_State_Controller::Initialize()
	{
		_bm_join.LoadBitmap(JOIN);
		_bm_loading.LoadBitmap(LOADING);
		_box.LoadBitmap();
		_book.LoadBitmap();
		_map.LoadBitmap();
		_ani_light_beam.SetDelayCount(1);
		_ani_light_beam.AddBitmap(LIGHT_BEAM01, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM02, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM03, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM04, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
		_ani_light_beam.AddBitmap(LIGHT_BEAM05, RGB(50, 255, 0));
		_ani_light_beam.SetTopLeft(0, 0);
	}

	void Home_State_Controller::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
	{
		if (nChar == KEY_DOWN || nChar == KEY_S)
			Character::Instance().SetMovingDown(false);
		if (nChar == KEY_UP || nChar == KEY_W)
			Character::Instance().SetMovingUp(false);
		if (nChar == KEY_LEFT || nChar == KEY_A)
			Character::Instance().SetMovingLeft(false);
		if (nChar == KEY_RIGHT || nChar == KEY_D)
			Character::Instance().SetMovingRight(false);
	}

	void Home_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_delayCounter < 0)
		{
			Cheater(nChar);
			switch (_flag)
			{
			case FLAG_HOME_NORMAL:		//�i�J�C���A�S���}�ҥ�����
				if (nChar == KEY_DOWN || nChar == KEY_S)
					Character::Instance().SetMovingDown(true);
				if (nChar == KEY_UP || nChar == KEY_W)
					Character::Instance().SetMovingUp(true);
				if (nChar == KEY_LEFT || nChar == KEY_A)
					Character::Instance().SetMovingLeft(true);
				if (nChar == KEY_RIGHT || nChar == KEY_D)
					Character::Instance().SetMovingRight(true);
				if (nChar == KEY_SPACE)
					Character::Instance().Dash();
				if (nChar == KEY_Q)
					_map.CharacterUseSkill(3, 0, 0);
				if (nChar == KEY_F && _map.GetCharacterStatus() == 1)
				{
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_TOWN;	//������town
				}
				if (nChar == KEY_F && _map.GetCharacterStatus() == 2)
				{
					_box.Open(true);
					_flag = FLAG_BOX;	//�}�ҹD��c
				}
				if (nChar == KEY_F && _map.GetCharacterStatus() == 3)
				{
					CAudio::Instance()->Play(AUDIO_FLIP_BOOK);
					_book.Open(true);	//�}�Ү�
					_flag = FLAG_BOOK;
				}
				if (nChar == KEY_ESC)	//PAUSED���
				{
					CAudio::Instance()->Play(AUDIO_BE, false);
					PausedMenu::Instance().Paused(true);
					_flag = FLAG_HOME_PAUSED;
				}
				if (nChar == KEY_TAB)	//�˳Ƹ�T
				{	
					CAudio::Instance()->Play(AUDIO_TAB);
					Bag::Instance().Open(true);
					_flag = FLAG_HOME_BAG;
				}
				break;
			case FLAG_JOIN:
				if (nChar == KEY_SPACE)		// �[�J�C�������ܿ��
					_flag = FLAG_HOME_NORMAL;	// ����i�J�C��
				break;
			case FLAG_BOX:	//�D��c���
				if (nChar == KEY_ESC)
				{
					_box.Open(false);
					_flag = FLAG_HOME_NORMAL;
				}
				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					CAudio::Instance()->Play(AUDIO_PULL2, false);
					_box.Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					CAudio::Instance()->Play(AUDIO_PULL2, false);
					_box.Up();
				}
				if (nChar == KEY_SPACE)
				{
					CAudio::Instance()->Play(AUDIO_PULL, false);
					_box.OpenOpen(true);
					_flag = FLAG_BOX_ITEM;
				}
				break;
			case FLAG_BOX_ITEM:		//Box���
				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					_box.Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					_box.Up();
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					_box.Left();
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					_box.Right();
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
				}
				if (nChar == KEY_SPACE)
				{
					if (_box.Equip(&Items::Instance())) 
					{
						SaveMemento(Town_Or_Home);
						_box.OpenOpen(false);
						_flag = FLAG_BOX;
					}
					else
					{
						CAudio::Instance()->Play(AUDIO_NOMONEY, false);
					}
				}
				if (nChar == KEY_ESC)
				{
					_box.OpenOpen(false);
					_flag = FLAG_BOX;
				}
				break;
			case FLAG_HOME_PAUSED:		//�Ȱ����
				CAudio::Instance()->Play(AUDIO_BE, false);
				if (nChar == KEY_DOWN || nChar == KEY_S)
					PausedMenu::Instance().NextPausedMenu();
				else if (nChar == KEY_UP || nChar == KEY_W)
					PausedMenu::Instance().PrePausedMenu();
				else if (nChar == KEY_ESC)
				{
					_flag = FLAG_HOME_NORMAL;
					PausedMenu::Instance().Paused(false);
				}
				else if (nChar == KEY_SPACE)
				{
					int temp;
					temp = PausedMenu::Instance().EnterPauseMenu();
					switch (temp)
					{
					case 0:
						_flag = FLAG_HOME_NORMAL;
						break;
					case 1:
						_flag = FLAG_JOIN;
						_isSwitch = true;
						_game_state_num = GAME_STATE_INIT;
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
				if (nChar == KEY_ESC)
				{
					CAudio::Instance()->Play(AUDIO_BE);
					PausedMenu::Instance().PrePausedMenu();
					PausedMenu::Instance().PrePausedMenu();
					_flag = FLAG_HOME_PAUSED;
				}
				if (nChar == KEY_SPACE)
				{
					CAudio::Instance()->Play(AUDIO_SAVE_DATA);
					PausedMenu::Instance().PrePausedMenu();
					PausedMenu::Instance().PrePausedMenu();
					SaveData();
					_flag = FLAG_HOME_PAUSED;
				}
				break;

			case FLAG_HOME_BAG:		//�}�ҭI�]
				if (nChar == KEY_TAB || nChar == KEY_ESC)
				{
					Bag::Instance().Open(false);
					_flag = FLAG_HOME_NORMAL;
				}
				if (nChar == KEY_DOWN || nChar == KEY_S)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					Bag::Instance().Down();
				}
				if (nChar == KEY_UP || nChar == KEY_W)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					Bag::Instance().Up();
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					Bag::Instance().Left();
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					CAudio::Instance()->Play(AUDIO_PUTTING, false);
					Bag::Instance().Right();
				}
				break;
			case FLAG_BOOK:		//���}�]�k��
				if (nChar == KEY_ESC)
				{
					CAudio::Instance()->Play(AUDIO_FLIP_BOOK);
					_book.Open(false);
					_flag = FLAG_HOME_NORMAL;
				}
				if (nChar == KEY_LEFT || nChar == KEY_A)
				{
					CAudio::Instance()->Play(AUDIO_FLIP_BOOK);
					_book.Left();
				}
				if (nChar == KEY_RIGHT || nChar == KEY_D)
				{
					CAudio::Instance()->Play(AUDIO_FLIP_BOOK);
					_book.Right();
				}
				break;
			}
		}
	}

	void Home_State_Controller::OnLButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(1, point.x, point.y);
	}

	void Home_State_Controller::OnRButtonDown(UINT nFlags, CPoint point)
	{
		_map.CharacterUseSkill(2, point.x, point.y);
	}

	void Home_State_Controller::OnMove() 
	{
		CharacterDead();	//�P�_�}�⦺�`�B��������ʧ@
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
		if (_delayCounter > -1)
			_delayCounter--;
		_bm_join.SetTopLeft(100, 100);
		_bm_loading.SetTopLeft(0, 0);
		_map.OnMove();
		_box.OnMove();
		_book.OnMove();
		Character::Instance().OnMove(&_map);
		Bag::Instance().OnMove();
		UI::Instance().OnMove();
		Items::Instance().Effect();
	}

	void Home_State_Controller::OnShow()
	{
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
					_box.OnShow(&Items::Instance());
					_book.OnShow();
					UI::Instance().OnShow();
					Bag::Instance().OnShow();
					PausedMenu::Instance().OnShow();
				}
			}
		}
		else
			_bm_loading.ShowBitmap();
	}
}
