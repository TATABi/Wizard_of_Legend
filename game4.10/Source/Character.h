namespace game_framework {
	class Character {
	public:
		Character();
		void Initialize();
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int x, int y);		// 設定擦子左上角座標
		
	private:
		int _x, _y;
		CMovingBitmap _pic;
		int _hp;
		int _mp;
		
	};
}