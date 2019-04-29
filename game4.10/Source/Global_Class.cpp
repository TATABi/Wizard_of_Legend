#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Global_Class.h"

namespace game_framework {
	Items Global_Class::g_items;
	UI Global_Class::g_ui;
	Character Global_Class::g_character;
	PausedMenu Global_Class::g_pauseMenu;
	Bag Global_Class::g_bag;
}