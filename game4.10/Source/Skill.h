#ifndef SKILL_H
#define SKILL_H

namespace game_framework {
	//skill template class
	class Skill {				
	public:
		Skill(int, int);
		~Skill();
		virtual void OnMove();
		virtual void OnShow();
		virtual void LoadBitmap();
		virtual void Initialize();
	protected:
		CMovingBitmap bm_skill;
		int timer;									//�s���ɶ�
		int vecX, vecY;								//���ʤ�V�y��
		int damage;									//�ˮ`�q
		int backDistance;							//���h�Z��
		int hitbox_X, hitbox_Y;						//hitBox����
		const int CHARACTER_SCREEN_X = 285;			//����ù���m�n���n�ԥh����
		const int CHARACTER_SCREEN_Y = 205;		
	};
}
#endif