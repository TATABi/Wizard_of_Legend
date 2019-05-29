#ifndef CONTROLLER_H
#define CONTROLLER_H
namespace game_framework {

	class Controller {
	public:
		Controller();
		~Controller();
		virtual void Initialize();
		virtual void Begin();
		virtual void OnKeyUp(UINT, UINT, UINT);
		virtual void OnKeyDown(UINT, UINT, UINT);
		virtual void OnLButtonDown(UINT, CPoint);
		virtual void OnRButtonDown(UINT, CPoint);
		virtual void OnShow();
		virtual bool IsSwitchGameState();
		virtual int GameState();
	protected:
		void Cheater(UINT);		//§@¹ú
		int _game_state_num;
		bool _isSwitch;
	};
}

#endif
