#ifndef PAUSED_MENU_H
#define PAUSED_MENU_H

namespace game_framework {
	class PausedMenu {
	public:
		static PausedMenu &Instance();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void Paused(bool);					//觸發暫停
		void NextPausedMenu();				//下一個pause menu
		void PrePausedMenu();				//前一個pause menu
		int EnterPauseMenu();				//按space 回傳給mygmae flag 切換狀態
	protected:
		PausedMenu();
	private:
		CMovingBitmap _bm_paused_resume;
		CMovingBitmap _bm_paused_title;
		CMovingBitmap _bm_paused_options;
		CMovingBitmap _bm_paused_quit;
		CMovingBitmap _bm_pause_optionss;
		bool _isPaused;						//是否pause
		int _paused_flag;					//暫停選單
	};
}

#endif
