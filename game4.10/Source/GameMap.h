#include "Map_Home_Logic.h"

namespace game_framework {

	class GameMap {
	public:
		GameMap(); 
		~GameMap();
		bool IsEmpty(int, int);
		void LoadBitmap();
		void OnShowBackground();
		void OnShowWall();
		void SetScreenPosition(int, int);
		int GetScreenX();
		int GetScreenY();
	private:
		Map_Home_Logic _map;	//�޿�ϼh�A�s�a�ϰ}�C(160*160)
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��
		int _sx, _sy;//�ù��b�a�ϤW���y��
	};
}