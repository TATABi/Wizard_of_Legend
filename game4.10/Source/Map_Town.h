#ifndef MAP_TOWN_H
#define MAP_TOWN_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Town : public GameMap {
	public:
		Map_Town(int, int, Character*);  // 設定初始中心點
		~Map_Town();
		void LoadBitmap();
		void OnMove();
		int* SetCharacterXY(int, int);
		int GetMapStatus(int, int);
	};

}
#endif