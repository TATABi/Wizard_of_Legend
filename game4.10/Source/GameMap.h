namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // 設定初始中心點
		~GameMap();
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetCharacterXY(int, int);

	private:
		int _map[160][160] = { 0 };
		int _cx, _cy;  //角色所在Map的座標
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall;	//用來模擬3D畫面
		int cm[4];   //(x,y,l,w) collision_move
		int collision_damage[4];
	};

}