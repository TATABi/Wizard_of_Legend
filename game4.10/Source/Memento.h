#ifndef MEMENTO_H
#define MEMEMTO_H

#include <sstream>
#include "GameData.h"

namespace game_framework
{
/////////////////////////////////////////////////
	class State 
	{
		friend class Memento;
	public:
		State(const string, int, bool[NUM_ITEMS]);	//state�W�١B�˳ƹD��s���B�Ҧ��D��֦����A
		~State();
		string Stage();						//stage�W��
		int EquipItem();					//���W�˳ƥB�֦����D��s��
		bool* OwnedItem();					//�ҥH�D��֦����p
	private:
		string _stage;						//�����I
		int _equip_item;					//�˳ƹD��
		bool _owned_items[NUM_ITEMS];		//�֦��D��
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Memento 
	{
		friend class Originator;
	public:
		~Memento();
		string Stage();						//stage�W��
	private:
		Memento(State* state);				//��Originator�ಣ��Memento
		void SetState(State*);				//�]�wstate
		State* _state;
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Originator
	{
	public:
		static Originator &Instance();		//Singleton
		void SetState(State*);				//�]�wstate
		void RestoreToMemento(Memento*);	//�ζǤJ��Memento�˳ƪ��A
		Memento* CreateMemento();			//����Memento
	protected:
		Originator();
	private:
		State* _state;						//�sstate
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Caretaker
	{
	public:
		static Caretaker &Instance();		//Singleton
		~Caretaker();
		void SetMemento(Memento*);			//�]�wMemento
		Memento* GetMemento(string);		//�q��string�qmap�̭����XMemento
	protected:
		Caretaker();
	private:
		map<string, Memento*> _mementos;	//map�s��Ҧ�Memento
	};
}
/////////////////////////////////////////////////

#endif
