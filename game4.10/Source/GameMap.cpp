#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Character.h"
#include <algorithm>

namespace game_framework {
	
	GameMap::GameMap(int x, int y)
	{
		Initialize(x, y);
	}
	
	GameMap::~GameMap() 
	{
		for each (Skill* skill in _skillList)
			delete skill;

		for each (Enemy* enemy in _enemies)
			delete enemy;
	}

	void GameMap::Initialize(int x, int y) 
	{
		_cxy[0] = x;
		_cxy[1] = y;	
		_ani_press_f.SetDelayCount(2);
		_isPressF = false;
		_character_status = 0;
		
		
		for (int i = 0; i < _enemies.size(); i++)
			_enemies[i]->Reset();	
		
	}

	void GameMap::LoadBitmapPressF()
	{
		int m[6] = { PRESS_F_01, PRESS_F_02, PRESS_F_03 , PRESS_F_04, PRESS_F_05, PRESS_F_06 };
		for (int i = 0; i < 6;i++)
			_ani_press_f.AddBitmap(m[i], RGB(50, 255, 0));

	}
	
	void GameMap::OnMoveBackgroundAndWall()
	{
		_background.SetTopLeft(CHARACTER_SCREEN_X - _cxy[0], CHARACTER_SCREEN_Y - _cxy[1]);
		_wall.SetTopLeft(CHARACTER_SCREEN_X - _cxy[0], CHARACTER_SCREEN_Y - _cxy[1]);
	}
	
	void GameMap::OnShowBackground()
	{
		_background.ShowBitmap();
	}

	void GameMap::OnShowWall()
	{
		_wall.ShowBitmap();
	}

	void GameMap::OnShowPressF()
	{
		if (_isPressF)
			_ani_press_f.OnShow();
	}
	
	int GameMap::GetCharacterStatus() 
	{
		return _character_status;
	}

	int* GameMap::GetCharacterPosition()
	{
		return _cxy;
	}

	void GameMap::CharacterUseSkill(int skillNum, int x, int y)
	{
		if(!_character->IsUsingSkill())
			_skillList.push_back(_character->GenerateSkill(skillNum, x, y));
	}
	
	void GameMap::SkillOnMove()
	{
		for each (Skill* skill in _skillList)
			skill->OnMove(GetCharacterPosition(), &(*this));	
	}
	
	void GameMap::EnemyOnMove()
	{
		for each (Enemy* enemy in _enemies)
			enemy->OnMove(_cxy[0], _cxy[1], _skillList);
	}
	
	void GameMap::OnShow()
	{
		//�ϼh�ĪG

		vector<Layer*> layer;

		layer.insert(layer.end(), _enemies.begin(), _enemies.end());
		layer.insert(layer.end(), _skillList.begin(), _skillList.end());
		layer.push_back(_character);

		sort(layer.begin(), layer.end(), [](Layer* a, Layer* b) {return a->GetY() < b->GetY(); });

		vector<Layer*>::iterator l_it;
		for (l_it = layer.begin(); l_it != layer.end(); l_it++)
			(*l_it)->OnShow();

		CleanMemory();
	}

	void GameMap::CleanMemory()
	{

		vector<Skill*>::iterator s_it;
		for (s_it = _skillList.begin(); s_it != _skillList.end(); s_it++)
		{
			if ((*s_it)->IsDelete() == true)
			{
				delete *s_it;
				s_it = _skillList.erase(s_it);
			}
			if (s_it == _skillList.end())
				break;
		}

		vector<Enemy*>::iterator e_it;
		for (e_it = _enemies.begin(); e_it != _enemies.end(); e_it++)
		{
			if (!(*e_it)->IsLive())
			{
				delete *e_it;
				e_it = _enemies.erase(e_it);
			}
			if (e_it == _enemies.end())
				break;
		}
	}
}


