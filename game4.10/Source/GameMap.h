#include "Map_Home_Logic.h"

namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // �]�w��l�����I
		~GameMap();
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove();
		void OnShowBackground();
		void OnShowWall();
		bool OnShowPressF();
		int SetCharacterXY(int, int);
	private:
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall; //��
		CAnimation ani_press_f;  //press f �ʵe
		int _cx, _cy;  //����ҦbMap���y��
		bool can_press_f;
		const int collision_move[4] = { 24, 53, 20 , 7};   //(x,y,l,w) collision_move	�I���P�w�d��
		const int collision_damage[4] = {0};	//����ˮ`�P�w�d��
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
	};

}