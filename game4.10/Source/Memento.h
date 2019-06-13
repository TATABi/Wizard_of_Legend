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
		State(const string, int, bool[NUM_ITEMS]);	//state名稱、裝備道具編號、所有道具擁有狀態
		~State();
		string Stage();						//stage名稱
		int EquipItem();					//身上裝備且擁有的道具編號
		bool* OwnedItem();					//所以道具擁有狀況
	private:
		string _stage;						//紀錄點
		int _equip_item;					//裝備道具
		bool _owned_items[NUM_ITEMS];		//擁有道具
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Memento 
	{
		friend class Originator;
	public:
		~Memento();
		string Stage();						//stage名稱
	private:
		Memento(State* state);				//讓Originator能產生Memento
		void SetState(State*);				//設定state
		State* _state;
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Originator
	{
	public:
		static Originator &Instance();		//Singleton
		void SetState(State*);				//設定state
		void RestoreToMemento(Memento*);	//用傳入的Memento裝備狀態
		Memento* CreateMemento();			//產生Memento
	protected:
		Originator();
	private:
		State* _state;						//存state
	};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
	class Caretaker
	{
	public:
		static Caretaker &Instance();		//Singleton
		~Caretaker();
		void SetMemento(Memento*);			//設定Memento
		Memento* GetMemento(string);		//從用string從map裡面取出Memento
	protected:
		Caretaker();
	private:
		map<string, Memento*> _mementos;	//map存放所有Memento
	};
}
/////////////////////////////////////////////////

#endif
