#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
		enum AREA {
			AREA_1						//怪物生成區域
		};
	public:
		Map_Home(int, int);				// 設定初始中心點
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);	//透過Map_Home_Logic.h取得地圖資料
		void AddEnemy();				//生成怪物(這裡生成木頭人)
	};
}
#endif