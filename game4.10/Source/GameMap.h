namespace game_framework {

	class GameMap
	{
	public:
		GameMap();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		void Initialize();				// 設定擦子為初始值
		void OnShow();					// 將擦子圖形貼到畫面
		void SetXY(int x, int y);		// 設定擦子左上角座標
		void RandomMap();
	private:
		int _x, _y;					// 擦子左上角座標
		CMovingBitmap _pic;
	};
}