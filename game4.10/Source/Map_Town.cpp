#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Town.h"
#include "Map_Town_Logic.h"
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
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);
	
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

		OnMoveBackgroundAndWall();

		SkillOnMove();

		EnemyOnMove();


	}
	
	int* Map_Town::SetCharacterXY(int dx, int dy, const int* collision_move)
	{
		int slow_x = (int)dx / 3;
		int slow_y = (int)dy / 3;

		////////角色移動與怪物碰撞//////
		vector<Enemy*>::iterator iter;
		for (iter = _enemies.begin(); iter != _enemies.end(); iter++)
		{
			float *e_xy = (*iter)->GetPosition();
			int *e_collision_move = (*iter)->GetCollisionMove();

			int x1 = _cxy[0] + collision_move[0] + dx;
			int y1 = _cxy[1] + collision_move[1] + dy;
			int x2 = e_xy[0] + e_collision_move[0];
			int y2 = e_xy[1] + e_collision_move[1];
			int l1 = collision_move[2];
			int w1 = collision_move[3];
			int l2 = e_collision_move[2];
			int w2 = e_collision_move[3];
			
			int e_dx = 0, e_dy = 0;

			if (abs((x1 + l1 / 2) - (x2 + l2 / 2)) < abs((l1 + l2) / 2) && abs((y1 + w1 / 2) - (y2 + w2 / 2)) < abs((w1 + w2) / 2))	//發生碰撞
			{
				e_dx = (int)(dx / 3);
				e_dy = (int)(dy / 3);

				if (GetMapStatus(e_xy[0] + e_collision_move[0] + e_dx, e_xy[1] + e_collision_move[1] + e_dy) != -1							//左上
					&& GetMapStatus(e_xy[0] + e_collision_move[0] + e_collision_move[2] + e_dx, e_xy[1] + e_collision_move[1] + e_dy) != -1				//右上
					&& GetMapStatus(e_xy[0] + e_collision_move[0] + e_dx, e_xy[1] + e_collision_move[1] + e_collision_move[3] + e_dy) != -1				//左下
					&& GetMapStatus(e_xy[0] + e_collision_move[0] + e_collision_move[2] + e_dx, e_xy[1] + e_collision_move[1] + e_collision_move[3] + e_dy) != -1)		//右下
				{
					e_xy[0] += e_dx;
					e_xy[1] += e_dy;
					//被推到撞牆
					dx = slow_x;
					dy = slow_y;
					break;

				}
    			//被推
				dx = dy = 0;
			}
			//沒撞到
		}

		//////////與地圖碰撞////////////
		if (GetMapStatus(_cxy[0] + collision_move[0] + dx, _cxy[1] + collision_move[1] + dy) != -1							//左上
			&& GetMapStatus(_cxy[0] + collision_move[0] + collision_move[2] + dx, _cxy[1] + collision_move[1] + dy) != -1				//右上
			&& GetMapStatus(_cxy[0] + collision_move[0] + dx, _cxy[1] + collision_move[1] + collision_move[3] + dy) != -1				//左下
			&& GetMapStatus(_cxy[0] + collision_move[0] + collision_move[2] + dx, _cxy[1] + collision_move[1] + collision_move[3] + dy) != -1)		//右下
		{
			_cxy[0] += dx;
			_cxy[1] += dy;
		}
		return _cxy;
	}


	bool Map_Town::SetEnemyXY(int x, int y, int* collision_move)
	{
		int ex = x + collision_move[0];
		int ey = y + collision_move[1];
		int l = collision_move[2];
		int w = collision_move[3];

		//////////與地圖碰撞////////////
		if (GetMapStatus(ex, ey) != -1
			&& GetMapStatus(ex + l, ey) != -1
			&& GetMapStatus(ex + l, ey + w) != -1
			&& GetMapStatus(ex, ey + w) != -1)
		{
			return true;
		}

		return false;
	}

	
	int Map_Town::GetMapStatus(int x, int y)
	{
		return TOWN_LOGIC[int(x/10)][int(y/10)];
	}
	

}
