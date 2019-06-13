#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Over_State_Controller.h"
#include "GameData.h"
#include "CharacterData.h"

namespace game_framework {
	
	Over_State_Controller::Over_State_Controller():Controller(), _int_stage(1), _int_gold_found(3), _int_gems_collected(3), _int_enemy_defeated(3) {}

	Over_State_Controller::~Over_State_Controller(){}

	void Over_State_Controller::Begin()
	{
		_isSwitch = false;
		_game_state_num = -1;
		_delay_counter = 15 * 1;		// 0.5 seconds
		_flag = FLAG_NORMAL;
		_mask_counter = 0;
		_isPlayed = false;
		CAudio::Instance()->StopAll();
	}

	void Over_State_Controller::Initialize()
	{
		int ani[6] = { END_PLAY_KEYBOARD_01, END_PLAY_KEYBOARD_02, END_PLAY_KEYBOARD_03, END_PLAY_KEYBOARD_04, END_PLAY_KEYBOARD_05, END_PLAY_KEYBOARD_06 };
		for (int i = 0; i < 6; i++)
			_ani_play_keyboard.AddBitmap(ani[i]);
		_ani_play_keyboard.SetDelayCount(1);

		_bm_result.LoadBitmap(END_BOARD);
		_bm_black_mask.LoadBitmap(END_MASK);
		_int_stage.LoadBitmap();
		_int_gold_found.LoadBitmap();
		_int_gems_collected.LoadBitmap();
		_int_enemy_defeated.LoadBitmap();

		_ani_play_keyboard.SetTopLeft(370, 132);
		_bm_result.SetTopLeft(0, 0);
		_int_stage.SetTopLeft(298, 162);
		_int_gold_found.SetTopLeft(285, 190);
		_int_gems_collected.SetTopLeft(285, 220);
		_int_enemy_defeated.SetTopLeft(285, 249);
	}

	void Over_State_Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (_mask_counter == 100)
		{	
			CAudio::Instance()->Play(AUDIO_BE);

			switch (_flag)
			{
			case FLAG_NORMAL:
				if (nChar == KEY_SPACE)
				{
					_isSwitch = true;
					_game_state_num = GAME_STATE_RUN_HOME;
				}
				else if (nChar == KEY_ESC)
				{
					_isSwitch = true;
					_game_state_num = GAME_STATE_INIT;
				}
				break;
			}
		}
	}

	void Over_State_Controller::OnMove()
	{
		int* game_result = CharacterData::Instance().GetStageResult();
		_int_stage.SetInteger(game_result[0]);
		_int_gold_found.SetInteger(game_result[1]);
		_int_gems_collected.SetInteger(game_result[2]);
		_int_enemy_defeated.SetInteger(game_result[3]);
		
		_delay_counter > 0 ? _delay_counter-- : NULL;

		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));

		if (_delay_counter == 0)
		{
			if (!_isPlayed)
			{
				if (CharacterData::Instance().HP() > 0)
					CAudio::Instance()->Play(AUDIO_GOOD_END);
				else
					CAudio::Instance()->Play(ADUIO_BAD_END);
				_isPlayed = true;
			}
			_mask_counter < 100 ? _mask_counter++ : NULL;
			_ani_play_keyboard.OnMove();
		}
	}

	void Over_State_Controller::OnShow()
	{
		if (_delay_counter == 0)
		{
			_bm_result.ShowBitmap();
			_int_stage.ShowBitmap();
			_int_gold_found.ShowBitmap();
			_int_gems_collected.ShowBitmap();
			_int_enemy_defeated.ShowBitmap();
			_ani_play_keyboard.OnShow();
			
			if (_mask_counter < 20)
			{
				_bm_black_mask.SetTopLeft(62, 125);
				_bm_black_mask.ShowBitmap();
			}
			if (_mask_counter < 40)
			{
				_bm_black_mask.SetTopLeft(62, 154);
				_bm_black_mask.ShowBitmap();
			}
			if (_mask_counter < 60)
			{
				_bm_black_mask.SetTopLeft(62, 183);
				_bm_black_mask.ShowBitmap();
			}
			if (_mask_counter < 80)
			{
				_bm_black_mask.SetTopLeft(62, 212);
				_bm_black_mask.ShowBitmap();
			}
			if (_mask_counter < 100)
			{
				_bm_black_mask.SetTopLeft(62, 241);
				_bm_black_mask.ShowBitmap();
			}
		}
	}
}
