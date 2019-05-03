#ifndef PAUSED_MENU_H
#define PAUSED_MENU_H

namespace game_framework {
	class PausedMenu {
	public:
		PausedMenu();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void Paused(bool);
		void NextPausedMenu();
		void PrePausedMenu();
		int EnterPauseMenu(); //按space 回傳給mygmae flag 切換狀態
	private:
		CMovingBitmap _bm_paused_resume;
		CMovingBitmap _bm_paused_title;
		CMovingBitmap _bm_paused_options;
		CMovingBitmap _bm_paused_quit;
		CMovingBitmap _bm_pause_optionss;
		bool _isPaused;
		int _paused_flag; //暫停選單
	};
}

#endif
