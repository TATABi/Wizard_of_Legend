#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "Map_Home_Logic.h"
#include "GameMap.h"
namespace game_framework {
	class Map_Home : public GameMap {
	public:
		Map_Home(int , int);  // �]�w��l�����I
		~Map_Home();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetCharacterXY(int, int);
	};

}
#endif