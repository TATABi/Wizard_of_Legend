#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
		enum AREA {
			AREA_1,
			AREA_2
		};
	public:
		Map_Home(int, int, Character*);  // 設定初始中心點
		~Map_Home();
		void LoadBitmap();
		void OnMove();
	    int* SetCharacterXY(int, int,const int*);
		bool SetEnemyXY(int, int, int*);
		int GetMapStatus(int, int);		
		void AddEnemy();
	};
}
#endif