#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Town.h"
#include "algorithm"

namespace game_framework {

	Map_Town::Map_Town(int x, int y, Character* c) : GameMap(x, y)
	{
		_character = c;
	}

	Map_Town::~Map_Town() {
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
			delete *iter;
	}

	void Map_Town::LoadBitmap()
	{
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
			(*iter)->LoadBitmap();

		LoadBitmapPressF();
		_background.LoadBitmap(MAP_TOWN);
		_wall.LoadBitmap(MAP_TOWN_WALL, RGB(50, 255, 0));
	}

	void Map_Town::OnMove()
	{
		OnMoveBackgroundAndWall();
		_character_status = town_map[_cxy[0] + _collision_move[0] + 10][_cxy[1] + _collision_move[1] + 3];
		int temp_x = 0, temp_y = 0;
		if (_character_status == 1 || _character_status == 2 || _character_status == 3 || _character_status == 4 || _character_status == 5)
		{
			switch (_character_status)
			{
			case 1:						//傳送門(往家)
				temp_x = 797;
				temp_y = 1052;
				_ani_press_f.OnMove();
				break;
			case 2:						//傳送門(往關卡)
				temp_x = 797;
				temp_y = 561;
				_ani_press_f.OnMove();
				break;
			case 3:						// 道具1
				temp_x = 530;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			case 4:						// 道具2
				temp_x = 580;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			case 5:						// 道具3
				temp_x = 626;
				temp_y = 970;
				_ani_press_f.OnMove();
				break;
			}
			_isPressF = true;
			_ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - _cxy[0], CHARACTER_SCREEN_Y + temp_y - _cxy[1]);
		}
		else
		{
			_ani_press_f.Reset();
			_isPressF = false;
		}

		/////////////////Skills移動/////////////////////////////

		for each (Skill* skill in _skillList)
		{
			skill->OnMove(GetCharacterPosition(), &(*this));
		}

		/////////////////Enemy移動/////////////////////////////

		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
		{

			if (!(*iter)->IsLive())
			{
				delete *iter;
				iter = _enemies.erase(iter);

			}
			else
			{
				(*iter)->OnMove(_cxy[0], _cxy[1], _skillList);
			}

			if (iter == _enemies.end())
			{
				break;
			}
		}

	}


	void Map_Town::OnShow()
	{
		//圖層效果

		vector<Layer*> layer;

		layer.insert(layer.end(), _enemies.begin(), _enemies.end());
		layer.insert(layer.end(), _skillList.begin(), _skillList.end());
		layer.push_back(_character);

		sort(layer.begin(), layer.end(), [](Layer* a, Layer* b) {return a->GetY() < b->GetY(); });

		vector<Layer*>::iterator iter;
		for (iter = layer.begin(); iter != layer.end(); iter++)
			(*iter)->OnShow();

		vector<Skill*>::iterator it;
		for (it = _skillList.begin(); it != _skillList.end(); it++)
		{
			if ((*it)->IsDelete() == true)
			{
				delete *it;
				it = _skillList.erase(it);
			}
			if (it == _skillList.end())
			{
				break;
			}
		}
	}

	int* Map_Town::SetCharacterXY(int dx, int dy)
	{
		int slow_x = (int)dx / 3;
		int slow_y = (int)dy / 3;

		////////角色移動與怪物碰撞//////
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
		{
			int temp = (*iter)->Collision(_cxy, _collision_move, dx, dy);
			if (temp == 1)
			{
				dx = slow_x;
				dy = slow_y;
				break;
			}
			else if (temp == 2)
			{

				dx = dy = 0;
			}

		}

		//////////與地圖碰撞////////////
		if (town_map[_cxy[0] + _collision_move[0] + dx][_cxy[1] + _collision_move[1] + dy] != -1							//左上
			&& town_map[_cxy[0] + _collision_move[0] + _collision_move[2] + dx][_cxy[1] + _collision_move[1] + dy] != -1				//右上
			&& town_map[_cxy[0] + _collision_move[0] + dx][_cxy[1] + _collision_move[1] + _collision_move[3] + dy] != -1				//左下
			&& town_map[_cxy[0] + _collision_move[0] + _collision_move[2] + dx][_cxy[1] + _collision_move[1] + _collision_move[3] + dy] != -1)		//右下
		{
			_cxy[0] += dx;
			_cxy[1] += dy;
		}

		return _cxy;

	}

	int Map_Town::GetMapStatus(int x, int y)
	{
		return town_map[x][y];
	}


}
