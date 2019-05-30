#ifndef MEMENTO_H
#define MEMEMTO_H

namespace game_framework
{
	class Memento 
	{
		friend class Originator;
	private:
		Memento(const string, int, int, bool[7]);			//紀錄點、Diamond、擁有道具、裝備道具
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
	private:
		Memento* _memento;
	};

	class Caretaker
	{
	public:
		Caretaker();
		void Save(Memento*);
		Memento* Load();
	private:
		Memento* _memento;
	};
}



#endif
