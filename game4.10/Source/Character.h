#include "GameMap.h"
namespace game_framework {

	class Character {
	public:
		Character();
		void Initialize();				
		void LoadBitmap();			
		void OnMove(GameMap *);				
		void OnShow();				
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag); 
		void SetMovingUp(bool flag);	
		void IntoGame();

	protected:
		CAnimation ani_up;		
		CAnimation ani_down;
		CAnimation ani_left;
		CAnimation ani_right;
		CMovingBitmap bm_stand_up;
		CMovingBitmap bm_stand_down;
		CMovingBitmap bm_stand_left;
		CMovingBitmap bm_stand_right;
		int _horizontal, _vertical;	//�W�U���k�P�w  (-MOVING_PIXEL,0,MOVING_PIXEL)	
		int _flag; // �������⭱�V���� (�k,��,�U,�W) = (0, 1, 2, 3);
		int _x, _y;
		bool isMovingDown;			
		bool isMovingLeft;			
		bool isMovingRight;			
		bool isMovingUp;	
		const int MOVING_PIXEL = 10;	//���ʳt��
	};
}
