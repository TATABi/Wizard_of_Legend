#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "Map_Home_Logic.h"
#include "GameMap.h"
#include "Character.h"


namespace game_framework {
	
	class Map_Home : public GameMap {
	public:
		Map_Home(int , int, Character*);  // 設定初始中心點
		~Map_Home();
		void LoadBitmap();
		void OnMove(std::vector<Skill*>&);
		void OnShow(std::vector<Skill*>&);
		int* SetCharacterXY(int, int);
		int GetMapStatus(int, int);
	private:
		Character* character;
		vector<Enemy*> enemies;
	};

}
#endif