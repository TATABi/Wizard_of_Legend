#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework {
	class GameMap;
	class Skill:public Layer{
	public :
		Skill();
		~Skill();
		bool IsDelete();
		void Init();
		int* GetHitbox();
		int GetDamage();
		int* GetPosition();
		virtual void OnMove(int *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, int*) = 0;
	protected:
		CMovingBitmap bm_skill_icon;
		float dx, dy;								//�ޯ઺���ʦV�q
		int cast_distance;							//�ޯ�I��ɻP���⪺�Z��
		float rx, ry;								//�ޯ��ڭ����m(�Ψӭץ�float int �ഫ�X�{���ݰ�)
		int speed;									//���ʳt��
		int lifeTimer;								//�s���ɶ�
		int damage;									//�ˮ`�q
		int backDistance;							//���h�Z��
		int hitbox[4];						        //hitBox ���W���y�� and l,w
		int map_collision[4];						//��a�Ϫ��I���P�w
		const int CHARACTER_SCREEN_CENTER_X = 320;	
		const int CHARACTER_SCREEN_CENTER_Y = 240;
		bool isDelete;
		bool isStock;								//�d����
		CAnimation ani_skill[8];
	};


}

#endif