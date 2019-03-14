#include "Map_Home_Logic.h"
namespace game_framework {

	class GameMap {
	public:
		GameMap(); 
		~GameMap();
		bool IsEmpty(int, int);
		void LoadBitmap();
		void OnShowBackground();
		void OnShowWall();
		void SetScreenPosition(int, int);
		int GetScreenX();
		int GetScreenY();
	private:
		Map_Home_Logic _map;	//邏輯圖層，存地圖陣列(160*160)
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆
		int _sx, _sy;//螢幕在地圖上的座標
		const int collision_move[4] = {3,4,0,1};   //(x,y,l,w) collision_move	碰撞判定範圍
		const int collision_damage[4] = {0};	//受到傷害判定範圍
	};
}