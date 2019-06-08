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
		State(const string, int, int, bool[NUM_ITEMS]);
		~State();
		string Stage();
		int Diamond();
		int EquipItem();
		bool* OwnedItem();
	private:
		string _stage;					//�����I
		int _diamond;					//Diamond
		int _equip_item;				//�˳ƹD��
		bool _owned_items[NUM_ITEMS];			//�֦��D��
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Memento 
	{
		friend class Originator;
	public:
		~Memento();
		string Stage();
	private:
		Memento(State* state);			
		void SetState(State*);
		State* _state;
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Originator
	{
	public:
		static Originator &Instance();
		void SetState(State*);
		void RestoreToMemento(Memento*);
		Memento* CreateMemento();
	protected:
		Originator();
	private:
		State* _state;
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Caretaker
	{
	public:
		static Caretaker &Instance();
		~Caretaker();
		void SetMemento(Memento*);
		Memento* GetMemento(string);
	protected:
		Caretaker();
	private:
		map<string, Memento*> _mementos;
	};
}
/////////////////////////////////////////////////

#endif
