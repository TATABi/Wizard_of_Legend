#ifndef SKILL_H
#define SKILL_H
#include "CharacterData.h"
namespace game_framework {
	//skill template class
	class Skill {				
	public:
		Skill(int, int );
		~Skill() ;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize() = 0;
		bool GetIsDelete();
	protected:
		CMovingBitmap bm_skill;
		float dx,dy, sx, sy, mx, my;				//�ֿn���ʶZ���B����I��ޯ�ɦa�Ϯy�СB�C��frame�ޯ�Ҧb�a�Ϧ�m				
		int speed;									//���ʳt��
		int lifeTimer;								//�s���ɶ�
		int vecX, vecY;								//�ƹ���m
		int damage;									//�ˮ`�q
		int backDistance;							//���h�Z��
		int hitbox_X, hitbox_Y;						//hitBox����
		const int CHARACTER_SCREEN_X = 285;			//����ù���m�n���n�ԥh����
		const int CHARACTER_SCREEN_Y = 205;		
		bool isDelete;
	};
}
#endif