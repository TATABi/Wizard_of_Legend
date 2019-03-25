#ifndef MAP_TOWN_H
#define MAP_TOWN_H
#include "Map_Town_Logic.h"
#include "GameMap.h"
namespace game_framework {
	class Map_Town : public GameMap {
	public:
		Map_Town(int, int);  // �]�w��l�����I
		~Map_Town();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetCharacterXY(int, int);
	};

}
#endif
