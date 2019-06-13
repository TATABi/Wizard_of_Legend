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
		void CharacterDead();						//�P�_���⦺�`
		void SaveMemento(std::string);				//�smemento
		void LoadMemento(std::string);				//Ū��memento
		void SaveData();							//�s��
		void LoadData();							//Ū��
		void ResetData();							//���m�ɮ�
	protected:
		void Cheater(UINT);							//Cheat
		int _game_state_num;						//���ಾ��State
		bool _isSwitch;								//�O�_���ಾ
	};
}

#endif
