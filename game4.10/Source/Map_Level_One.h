#ifndef MAP_LEVEL_ONE_H
#define MAP_LEVEL_ONE_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Level_One : public GameMap {
	public:
		Map_Level_One(int, int, Character*);  // �]�w��l�����I
		~Map_Level_One();
		void LoadBitmap();
		void OnMove();
		int* SetCharacterXY(int, int);
		int GetMapStatus(int, int);
	};

}
#endif