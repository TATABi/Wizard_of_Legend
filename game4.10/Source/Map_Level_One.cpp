#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map_Level_One.h"
#include "Map_Level_One_Logic.h"
#include "Black_Man.h"
#include "Slime.h"
#include "Boss.h"


namespace game_framework {

	Map_Level_One::Map_Level_One(int x, int y) : GameMap(x, y) { }

	void Map_Level_One::AddEnemy()
	{
		vector<Enemy*>::iterator e_it;
		for (e_it = _enemies.begin(); e_it != _enemies.end(); e_it++)
			(*e_it)->Dead();

		//Area 1
		_enemies.push_back(new Black_Man(2963, 3202, AREA_1, this));
		_enemies.push_back(new Black_Man(2947, 3210, AREA_1, this));
		//Area 2
		_enemies.push_back(new Black_Man(3545, 2761, AREA_2, this));
		_enemies.push_back(new Slime(3751, 2770, AREA_2, this));
		_enemies.push_back(new Slime(3703, 2804, AREA_2, this));
		_enemies.push_back(new Slime(3770, 2830, AREA_2, this));
		//Area 3
		_enemies.push_back(new Black_Man(2017, 2510, AREA_3, this));
		_enemies.push_back(new Black_Man(2123, 2509, AREA_3, this));
		_enemies.push_back(new Black_Man(2124, 2650, AREA_3, this));
		_enemies.push_back(new Slime(1856, 2591, AREA_3, this));
		//Area 4
		_enemies.push_back(new Slime(1367, 2515, AREA_4, this));
		_enemies.push_back(new Slime(1380, 2635, AREA_4, this));
		_enemies.push_back(new Slime(1400, 2539, AREA_4, this));
		_enemies.push_back(new Slime(1430, 2506, AREA_4, this));
		//Area 5
		_enemies.push_back(new Black_Man(840, 2720, AREA_5, this));
		_enemies.push_back(new Black_Man(840, 2824, AREA_5, this));
		_enemies.push_back(new Black_Man(840, 2960, AREA_5, this));
		//Area 6
		_enemies.push_back(new Slime(154, 2529, AREA_6, this));
		_enemies.push_back(new Slime(146, 2586, AREA_6, this));
		_enemies.push_back(new Slime(202, 2555, AREA_6, this));
		_enemies.push_back(new Slime(223, 2603, AREA_6, this));
		_enemies.push_back(new Slime(261, 2531, AREA_2, this));
		//Area 7
		_enemies.push_back(new Black_Man(767, 2148, AREA_7, this));
		//Area 8
		_enemies.push_back(new Slime(1459, 1740, AREA_8, this));
		_enemies.push_back(new Slime(1484, 1795, AREA_8, this));
		_enemies.push_back(new Slime(1667, 1929, AREA_8, this));
		//Area 9
		_enemies.push_back(new Black_Man(1958, 1736, AREA_9, this));
		_enemies.push_back(new Black_Man(2152, 1806, AREA_9, this));
		_enemies.push_back(new Black_Man(2304, 1733, AREA_9, this));
		//Area 10
		_enemies.push_back(new Slime(2059, 1239, AREA_10, this));
		_enemies.push_back(new Slime(2069, 1289, AREA_10, this));
		//Area 11
		_enemies.push_back(new Slime(2734, 1427, AREA_11, this));
		_enemies.push_back(new Slime(2890, 1568, AREA_11, this));

		for each (Enemy* enemy in _enemies)
			enemy->LoadBitmap();
	}

	void Map_Level_One::LoadBitmap()
	{
		LoadBitmapPressF();
		_background.LoadBitmap(MAP_LEVEL_01);
		_wall.LoadBitmap(MAP_LEVEL_01_WALL, RGB(50, 255, 0));
		_bm_hp_potion.LoadBitmap(INLEVEL_HP_POTION, RGB(50, 255, 0));
		_bm_attack_info.LoadBitmap(INLEVEL_ATTACK_INFO, RGB(50, 255, 0));
		_bm_speed_info.LoadBitmap(INLEVEL_SPEED_INFO, RGB(50, 255, 0));
		_bm_cd_info.LoadBitmap(INLEVEL_CD_INFO, RGB(50, 255, 0));
	}

	void Map_Level_One::OnMove()
	{
		NotifyAnemy(AREA_1, LEVEL_AREA_1);
		NotifyAnemy(AREA_2, LEVEL_AREA_2);
		NotifyAnemy(AREA_3, LEVEL_AREA_3);
		NotifyAnemy(AREA_4, LEVEL_AREA_4);
		NotifyAnemy(AREA_5, LEVEL_AREA_5);
		NotifyAnemy(AREA_6, LEVEL_AREA_6);
		NotifyAnemy(AREA_7, LEVEL_AREA_7);
		NotifyAnemy(AREA_8, LEVEL_AREA_8);
		NotifyAnemy(AREA_9, LEVEL_AREA_9);
		NotifyAnemy(AREA_10, LEVEL_AREA_10);
		NotifyAnemy(AREA_11, LEVEL_AREA_11);
		NotifyAnemy(AREA_BOSS, LEVEL_AREA_BOSS);
		_character_status = GetMapStatus(_cxy[0] + 35, _cxy[1] + 56);
		int temp_x = 0, temp_y = 0;
		if (_character_status >= 1 && _character_status <= 8)
		{
			_isPressF = true;

			switch (_character_status)
			{
			case 1:						//Boss				
				temp_x = 3509;
				temp_y = 668;
				_isSummonBoss && !_isEnd ? _isPressF = false : _ani_press_f.OnMove();
				break;
			case 2:						//上道具1
				temp_x = 2545;
				temp_y = 280;
				_ani_press_f.OnMove();
				break;
			case 3:						//上道具2
				temp_x = 2622;
				temp_y = 280;
				_ani_press_f.OnMove();
				break;
			case 4:						//上道具3
				temp_x = 2705;
				temp_y = 280;
				_ani_press_f.OnMove();
				break;
			case 5:						//中道具1
				temp_x = 1093;
				temp_y = 1445;
				_ani_press_f.OnMove();
				break;
			case 6:						//中道具2
				temp_x = 1170;
				temp_y = 1445;
				_ani_press_f.OnMove();
				break;
			case 7:						//中道具3
				temp_x = 1253;
				temp_y = 1445;
				_ani_press_f.OnMove();
				break;
			case 8:						//下道具
				temp_x = 1274;
				temp_y = 3635;
				_ani_press_f.OnMove();
				break;
			}
			_ani_press_f.SetTopLeft(CHARACTER_SCREEN_X + temp_x - _cxy[0], CHARACTER_SCREEN_Y + temp_y - _cxy[1]);
		}
		else
		{
			_ani_press_f.Reset();
			_isPressF = false;
		}
		if (_isEnd)
			_bm_exit.SetTopLeft(CHARACTER_SCREEN_X + 3502 - _cxy[0], CHARACTER_SCREEN_Y + 671 - _cxy[1]);

		_bm_hp_potion.SetTopLeft(CHARACTER_SCREEN_X + 1275 - _cxy[0], CHARACTER_SCREEN_Y + 3666 - _cxy[1]);
		_bm_attack_info.SetTopLeft(CHARACTER_SCREEN_X + 1080 - _cxy[0], CHARACTER_SCREEN_Y + 1465 - _cxy[1]);
		_bm_speed_info.SetTopLeft(CHARACTER_SCREEN_X + 1155 - _cxy[0], CHARACTER_SCREEN_Y + 1465 - _cxy[1]);
		_bm_cd_info.SetTopLeft(CHARACTER_SCREEN_X + 1230 - _cxy[0], CHARACTER_SCREEN_Y + 1465 - _cxy[1]);

		int t = 0;
		for each(Item* i in _store_items)
		{
			i->SetXY(CHARACTER_SCREEN_X + 2552 - _cxy[0] + 49 * t, CHARACTER_SCREEN_Y + 323 - _cxy[1]);
			t++;
		}
		OnMoveBackgroundAndWall();
		SkillOnMove();
		EnemyOnMove();
		RewardsOnMove();
	}

	int Map_Level_One::GetMapStatus(float x, float y)
	{
		return LEVEL_ONE_LOGIC[int(x / 10)][int(y / 10)];
	}

	void Map_Level_One::NotifyAnemy(AREA name, const int* area)
	{
		if ((_cxy[0] >= area[0]) && (_cxy[1] >= area[1]) && (_cxy[0] <= area[2]) && (_cxy[1]) <= area[3])
		{
			for (int i = 0; i < _enemies.size(); i++)
				if (_enemies[i]->Area() == name)
					_enemies[i]->NotifyCharge();
		}
	}

	void Map_Level_One::SummonBoss()
	{
		if (!_isSummonBoss)
		{
			_enemies.push_back(new Boss(3480, 520, AREA_BOSS, this));
			_enemies.back()->LoadBitmap();
			_isSummonBoss = true;
		}
	}

	void Map_Level_One::Show()
	{
		_bm_hp_potion.ShowBitmap();
		_bm_attack_info.ShowBitmap();
		_bm_speed_info.ShowBitmap();
		_bm_cd_info.ShowBitmap();
		for each(Item* i in _store_items)
			if (!i->IsEquiped())
				i->OnShow();
	}

	void Map_Level_One::Init()
	{
		Item* now_equip = Items::Instance().GetEquipAndOwnedItem();
		vector<Item*> all = Items::Instance().GetAllItem();
		int num = 0;
		for (int i = 0; i < all.size(), num < 3; i++)
		{
			if (all[i] != now_equip)
			{
				_store_items.push_back(all[i]);
				num++;
			}
		}
	}

	bool Map_Level_One::BuyByMoney(int num)
	{
		if (num >= 0 && num < 3)
			return _store_items[num]->BuyAndEquip();
		else
			return false;
	}
}
