#ifndef MEMENTO_H
#define MEMEMTO_H
#include <sstream>

namespace game_framework
{
	class State 
	{
		friend class Memento;
	public:
		State(const string, int, int, bool[7]);
		string Stage();
		int Diamond();
		int EquipItem();
		bool* OwnedItem();
	private:
		string _stage;					//�����I
		int _diamond;					//Diamond
		int _equip_item;				//�˳ƹD��
		bool _owned_items[7];			//�֦��D��
	};

	class Memento 
	{
		friend class Originator;
	public:
		string Stage();
	private:
		Memento(State* state);			
		void SetState(State*);
		State* _state;
	};

	class Originator
	{
	public:
		Originator();
		void SetState(State*);
		void RestoreToMemento(Memento*);
		Memento* CreateMemento();
		void SetRecord();
	private:
		State* _state;
	};

	class Caretaker
	{
	public:
		Caretaker();
		~Caretaker();
		void SetMemento(Memento*);
		Memento* GetMemento(string);
	private:
		map<string, Memento*> _mementos;
	};
}



#endif
