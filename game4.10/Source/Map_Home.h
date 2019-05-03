#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "Map_Home_Logic.h"
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
	public:
		Map_Home(int, int, Character*);  // 設定初始中心點
		~Map_Home();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		int* SetCharacterXY(int, int);
		int GetMapStatus(int, int);
	private:
		vector<Enemy*> _enemies;
	};

}
#endif