#ifndef MAP_LEVEL_ONE_H
#define MAP_LEVEL_ONE_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Level_One : public GameMap {
	public:
		Map_Level_One(int, int, Character*);  // 設定初始中心點
		~Map_Level_One();
		void LoadBitmap();
		void OnMove();
		float* SetCharacterXY(int, int, const int*);
		bool SetEnemyXY(int, int, int*);
		int GetMapStatus(float, float);
	};

}
#endif