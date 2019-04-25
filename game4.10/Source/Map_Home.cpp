#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Home.h"
#include "algorithm"

namespace game_framework {

	Map_Home::Map_Home(int x, int y, Character* c) : GameMap(x, y){
		enemies.push_back(new Enemy(650, 918));
		character = c;
	}

	Map_Home::~Map_Home() {
		
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			delete *iter;
		
	}

	void Map_Home::LoadBitmap()
	{
		
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
			(*iter)->LoadBitmap();
		
		LoadBitmapPressF();
		_background.LoadBitmap(MAP_HOME);
		_wall.LoadBitmap(MAP_HOME_WALL, RGB(50, 255, 0));
	}

	void Map_Home::OnMove(std::vector<Skill*> &skills)
	{
		OnMoveBackgroundAndWall();
		character_status = home_map[cxy[0] + collision_move[0] + 10][cxy[1] + collision_move[1] + 3];
		int temp_x = 0, temp_y = 0;
		if (character_status == 1 || character_status == 2 || character_status == 3)
		{
			switch (character_status)
			{
			case 1:						//傳送門
				temp_x = 768;
				temp_y = 360;
				ani_press_f.OnMove();
				break;
			case 2:						//道具箱
				temp_x = 865;
				temp_y = 1137;
				ani_press_f.OnMove();
				break;
			case 3:						// 書
				temp_x = 1235;
				temp_y = 840;
				ani_press_f.OnMove();
				break;
			}
			isPressF = true;
			ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - cxy[0], CHARACTER_SCREEN_Y + temp_y - cxy[1]);
		}
		else
		{
			ani_press_f.Reset();
			isPressF = false;
		}


		/////////////////Enemy移動/////////////////////////////
	   
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
		{

			if (!(*iter)->IsLive())
			{
				delete *iter;
				iter = enemies.erase(iter);

			}
			else
			{
				(*iter)->OnMove(cxy[0], cxy[1], skills);
			}

			if (iter == enemies.end())
			{
				break;
			}
		}
		

	}

	void Map_Home::OnShow(std::vector<Skill*> &skills)
	{
		//圖層效果

		vector<Layer*> layer;
		
		layer.insert(layer.end(), enemies.begin(), enemies.end());	
		layer.insert(layer.end(), skills.begin(), skills.end());
		layer.push_back(character);

		sort(layer.begin(), layer.end(), [](Layer* a, Layer* b) {return a->GetY() < b->GetY(); });

		vector<Layer*>::iterator iter;
		for (iter = layer.begin(); iter != layer.end(); iter++)
			(*iter)->OnShow();
	}
	
	int* Map_Home::SetCharacterXY(int dx, int dy)
	{
		int slow_x = (int)dx/3;
		int slow_y = (int)dy/3;

		////////角色移動與怪物碰撞//////
		vector<Enemy*>::iterator iter;
		for (iter = enemies.begin(); iter != enemies.end(); iter++)
		{
			int temp = (*iter)->Collision(cxy, collision_move, dx, dy);
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
		if (home_map[cxy[0] + collision_move[0] + dx][cxy[1] + collision_move[1] + dy] != -1							//左上
			&& home_map[cxy[0] + collision_move[0] + collision_move[2] + dx][cxy[1] + collision_move[1] + dy] != -1				//右上
			&& home_map[cxy[0] + collision_move[0] + dx][cxy[1] + collision_move[1] + collision_move[3] + dy] != -1				//左下
			&& home_map[cxy[0] + collision_move[0] + collision_move[2] + dx][cxy[1] + collision_move[1] + collision_move[3] + dy] != -1)		//右下
		{
			cxy[0] += dx;
			cxy[1] += dy;
		}

		return cxy;
	}

	int Map_Home::GetMapStatus(int x, int y)
	{
		return home_map[x][y];
	}


}
