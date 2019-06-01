#ifndef MEMENTO_H
#define MEMEMTO_H
#include <sstream>

namespace game_framework
{
	class Memento 
	{
		friend class Originator;
	public:
		vector<string> ToString();
		string State();
	private:
		Memento(const string, int, int, bool[7]);			//�����I�BDiamond�B�֦��D��B�˳ƹD��
		string _state;
		int _diamond;
		bool _owned_items[7];
		int _equip_item;
	};

	class Originator
	{
	public:
		Originator(const string, int, int, bool[7]);
		~Originator();
		void RestoreToMemento(Memento*);
		Memento* CreateMemento();
		void SetRecord();
		string State();
	private:
		Memento* _memento;
	};

	class Caretaker
	{
	public:
		Caretaker();
		void Save(Memento*);
		Memento* Load(string);
	private:
		map<string, Memento*> _mementos;
	};
}



#endif
