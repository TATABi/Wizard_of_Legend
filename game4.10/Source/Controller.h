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
		void CharacterDead();						//判斷角色死亡
		void SaveMemento(std::string);				//存memento
		void LoadMemento(std::string);				//讀取memento
		void SaveData();							//存檔
		void LoadData();							//讀檔
		void ResetData();							//重置檔案
	protected:
		void Cheater(UINT);							//Cheat
		int _game_state_num;						//待轉移的State
		bool _isSwitch;								//是否待轉移
	};
}

#endif
