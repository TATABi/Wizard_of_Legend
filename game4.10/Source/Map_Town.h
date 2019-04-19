#ifndef MAP_TOWN_H
#define MAP_TOWN_H
#include "Map_Town_Logic.h"
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Town : public GameMap {
	public:
		Map_Town(int, int);  // 設定初始中心點
		~Map_Town();
		void LoadBitmap();
		void OnMove(std::vector<Skill*>);
		void OnShow(std::vector<Skill*>*);
		int* SetCharacterXY(int, int);
		int GetMapStatus(int, int);
	};

}
#endif
