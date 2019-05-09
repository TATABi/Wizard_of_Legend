#ifndef BLACK_MAN_H
#define BLACK_MAN_H

#include "Enemy.h"

#define HP 500
#define  STEP 5
#define  ZONE 30
#define DAMAGE  20

namespace game_framework {
	class Black_Man : public Enemy {
	public:
		Black_Man(int, int, int, int);
		~Black_Man();
		void Init();
		void Reset();
		void LoadBitmap_2();
		void Move(int, int);
		void OnShow();						
	};

}


#endif