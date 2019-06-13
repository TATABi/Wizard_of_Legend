#ifndef PAUSED_MENU_H
#define PAUSED_MENU_H

namespace game_framework {
	class PausedMenu {
	public:
		static PausedMenu &Instance();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void Paused(bool);					//Ĳ�o�Ȱ�
		void NextPausedMenu();				//�U�@��pause menu
		void PrePausedMenu();				//�e�@��pause menu
		int EnterPauseMenu();				//��space �^�ǵ�mygmae flag �������A
	protected:
		PausedMenu();
	private:
		CMovingBitmap _bm_paused_resume;
		CMovingBitmap _bm_paused_title;
		CMovingBitmap _bm_paused_options;
		CMovingBitmap _bm_paused_quit;
		CMovingBitmap _bm_pause_optionss;
		bool _isPaused;						//�O�_pause
		int _paused_flag;					//�Ȱ����
	};
}

#endif
