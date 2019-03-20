namespace game_framework {
	class Box {
	public:
		Box();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void Next();
		void Previous();
		void Open(bool);
	private:
		CMovingBitmap bm_board;
		CAnimation ani_offense;
		CAnimation ani_defense;
		CAnimation ani_misc;
		int classification;	//¤ÀÃþ 0:offense 1:defense 2:misc 
		bool isOpened;
	};

}