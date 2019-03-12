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
		int collision_move[4];   //(x,y,l,w) collision_move	�I���P�w�d��
		int collision_damage[4];	//����ˮ`�P�w�d��
	};

}