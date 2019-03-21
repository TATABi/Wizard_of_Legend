namespace game_framework {
	class UI {
	public:
		UI() {};
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap bm_status;
		CMovingBitmap bm_money;
		CMovingBitmap bm_diamond;
		CMovingBitmap bm_skill_background;
		CMovingBitmap bm_key_q;
		CMovingBitmap bm_key_space;
		CMovingBitmap bm_right_button;
		CMovingBitmap bm_left_button;
		CMovingBitmap bm_hp_bar;
	};
}
