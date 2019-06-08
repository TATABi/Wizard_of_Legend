#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "GameData.h"

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
		void CharacterDead();
		void UpdateMemento(std::string);	//¦smemento
		void LoadMemento(std::string);		//Åª¨úmemento
		void SaveData();
		void LoadData();
		void ResetData();
	protected:
		void Cheater(UINT);		//§@¹ú
		int _game_state_num;
		bool _isSwitch;
	};
}

#endif
