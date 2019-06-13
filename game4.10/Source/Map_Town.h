#ifndef MAP_TOWN_H
#define MAP_TOWN_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Town : public GameMap {
	public:
		Map_Town(int, int);				// �]�w��l�����I
		void AddEnemy();				//�ͦ��Ǫ�
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);	//�z�LMap_Town_logic.���o�a�ϸ�T
	};
}

#endif