#ifndef MAP_TOWN_H
#define MAP_TOWN_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Town : public GameMap {
	public:
		Map_Town(int, int);				// 設定初始中心點
		void AddEnemy();				//生成怪物
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);	//透過Map_Town_logic.取得地圖資訊
	};
}

#endif