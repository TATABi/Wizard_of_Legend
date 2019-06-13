#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
		enum AREA {
			AREA_1						//�Ǫ��ͦ��ϰ�
		};
	public:
		Map_Home(int, int);				// �]�w��l�����I
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);	//�z�LMap_Home_Logic.h���o�a�ϸ��
		void AddEnemy();				//�ͦ��Ǫ�(�o�̥ͦ����Y�H)
	};
}
#endif