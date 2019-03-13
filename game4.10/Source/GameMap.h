#include "Map_Home_Logic.h"
namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // �]�w��l�����I
		~GameMap();
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetCharacterXY(int, int);

	private:
		Map_Home_Logic _map;	//�޿�ϼh
		CMovingBitmap _background; //�I����
		int _cx, _cy;  //����ҦbMap���y��
		const int collision_move[4] = {3,4,0,1};   //(x,y,l,w) collision_move	�I���P�w�d��
		const int collision_damage[4] = {0};	//����ˮ`�P�w�d��
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
	};

}