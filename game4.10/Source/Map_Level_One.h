#ifndef MAP_LEVEL_ONE_H
#define MAP_LEVEL_ONE_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Level_One : public GameMap {
		enum AREA {
			AREA_1,
			AREA_2,
			AREA_3,
			AREA_4,
			AREA_5,
			AREA_6,
			AREA_7,
			AREA_8,
			AREA_9,
			AREA_10,
			AREA_11,
			AREA_BOSS
		};
	public:
		Map_Level_One(int, int);  // 設定初始中心點
		void AddEnemy();
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);
	private:
		void NotifyAnemy(AREA, const int*);
	};
}
#endif