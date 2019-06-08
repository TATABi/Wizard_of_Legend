#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
		enum AREA {
			AREA_1
		};
	public:
		Map_Home(int, int);  // �]�w��l�����I
		~Map_Home();
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);		
		void AddEnemy();
	};
}
#endif