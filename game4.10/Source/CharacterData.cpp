#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "CharacterData.h"

namespace game_framework {
	int CharacterData::money = 100;
	int CharacterData::diamond = 0;
	int HP = 500;
	int MP = 0;
	double attack_coefficient = 1;
	double defense_coefficient = 1;
}