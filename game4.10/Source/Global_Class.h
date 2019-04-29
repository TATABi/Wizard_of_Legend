#ifndef GLOBAL_CLASS_H
#define	GLOBAL_CLASS_H
#include "Items.h"
#include "UI.h"
#include "Character.h"
#include "PausedMenu.h"
#include "Bag.h"

namespace game_framework {

	class Global_Class
	{
	public:
		static Items g_items;
		static UI g_ui;
		static Character g_character;
		static PausedMenu g_pauseMenu;
		static Bag g_bag;
	};
}

#endif
