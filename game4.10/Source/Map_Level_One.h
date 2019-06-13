#ifndef MAP_LEVEL_ONE_H
#define MAP_LEVEL_ONE_H
#include "GameMap.h"
#include "Character.h"
#include "Items.h"

namespace game_framework {
	class Map_Level_One : public GameMap {
		enum AREA {							//Enemy區域
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
		Map_Level_One(int, int);			// 設定初始中心點
		void AddEnemy();					//加入Enemy
		void LoadBitmap();					//匯入圖片
		void OnMove();						//場景互動、技能、圖片等移動和計算
		void SummonBoss();					//召喚Boss
		int GetMapStatus(float, float);		//取得地圖的"點"資訊
		void Show();						//顯示地圖道具
		void Init();						//初始化地圖
		bool BuyByMoney(int);				//在關卡中購買地圖道具
	private:
		void NotifyAnemy(AREA, const int*);	//通知Anemy追擊
		CMovingBitmap _bm_hp_potion;		//HP Potion
		vector<Item*> _store_items;			//Store中的 items
		CMovingBitmap _bm_attack_info,		//攻擊Buff
					  _bm_speed_info,		//速度Buff
					  _bm_cd_info;			//CD Buff
	};
}

#endif