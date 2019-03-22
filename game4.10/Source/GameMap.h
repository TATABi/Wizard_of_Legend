namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // 設定初始中心點
		~GameMap();
		void Initialize(int, int);
		void ParentLoadBitmap();
		void ParentOnMove();
		void OnShowBackground();
		void OnShowWall();
		void OnShowPressF();
		int GetCharacterStatus();
		virtual void LoadBitmap()=0;
		virtual void OnMove()=0;
		virtual void OnShow()=0;
		virtual void SetCharacterXY(int,int)=0;
	protected:
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆
		CAnimation ani_press_f;  //press f 動畫
		int _cx, _cy;  //角色所在Map的座標
		bool can_press_f;
		int character_status;
		const int collision_move[4] = { 24, 53, 20 , 7};   //(x,y,l,w) collision_move	碰撞判定範圍
		const int collision_damage[4] = {0};	//受到傷害判定範圍
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
	};

}