#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "CharacterData.h"

namespace game_framework {
	int CharacterData::characterX = 0;
	int CharacterData::characterY = 0;
	int CharacterData::Money = 100;
	int CharacterData::Diamond = 0;
	int CharacterData::HP = 300;
	int CharacterData::Max_HP = 500;
	int CharacterData::MP = 0;
	int CharacterData::Max_MP = 100;
	double CharacterData::Attack_Coefficient = 1;
	double CharacterData::Defense_Coefficient = 1;
	
	//bool CharacterData::Equip_Item[10] = { 0,0,0,0,0,0,0,0,0,0 };
	//bool CharacterData::Have_Item[10] = { 0,0,0,0,0,0,0,0,0,0 };

}