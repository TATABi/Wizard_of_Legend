#ifndef SKILL_H
#define SKILL_H

namespace game_framework {
	//skill template class
	class Skill {				
	public:
		Skill(int, int);
		~Skill() ;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize() = 0;
	protected:
		CMovingBitmap bm_skill;
		int timer;									//�s���ɶ�
		int vecX, vecY;								//���ʤ�V�y��
		int damage;									//�ˮ`�q
		int backDistance;							//���h�Z��
		int hitbox_X, hitbox_Y;						//hitBox����
		const int CHARACTER_SCREEN_X = 285;			//����ù���m�n���n�ԥh����
		const int CHARACTER_SCREEN_Y = 205;		
		bool isDelete;
	};
}
#endif