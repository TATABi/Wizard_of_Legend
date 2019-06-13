#ifndef REWARD_MONEY_H
#define REWARD_MONEY_H

#include "reward.h"

namespace game_framework {

	class GameMap;

	class Reward_Money : public Reward{
	public:
		Reward_Money(float, float, GameMap*);	//�ͦ���m�B�a��
		void LoadBitmap();		
		void Initialize(float, float);
		void Effect();							//Ĳ�o�ĪG
	private:
		//_hitbox[4] = {5, 5, 9, 9};
		GameMap *_map;
	};


}

#endif