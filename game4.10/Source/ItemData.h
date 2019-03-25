#ifndef ITEMDATA_H
#define ITEMDATA_H
#include <vector>
#include "Item.h"

namespace game_framework {
	class ItemData
	{
	public:
		static std::vector<Item*> items;
	};

}

#endif