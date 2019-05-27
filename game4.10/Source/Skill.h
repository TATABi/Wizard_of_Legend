#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework {
	class Enemy;
	class GameMap;
	class Skill:public Layer{
	public :
		Skill();
		~Skill();
		bool IsDelete();
		void Init();
		int* GetHitbox();	
		bool AttackedThisEnemy(Enemy*);			//�����virtual
		virtual int GetDamage(Enemy *) = 0;
		virtual void OnMove(int *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, float*) = 0;	
	protected:
		CMovingBitmap _bm_skill_icon;
		float _dx, _dy;								//�ޯ઺���ʦV�q
		int _cast_distance;							//�ޯ�I��ɻP���⪺�Z��
		float _rx, _ry;								//�ޯ��ڭ����m(�Ψӭץ�float int �ഫ�X�{���ݰ�)
		int _speed;									//���ʳt��
		int _lifeTimer;								//�s���ɶ�
		int _damage;									//�ˮ`�q
		int _backDistance;							//���h�Z��
		int _hitbox[4];						        //hitBox ���W���y�� and l,w
		int _map_collision[4];						//��a�Ϫ��I���P�w
		const int CHARACTER_SCREEN_CENTER_X = 320;	
		const int CHARACTER_SCREEN_CENTER_Y = 240;
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
		bool _isDelete;
		bool _isStock;								//�d����
		CAnimation _ani_skill[8];					//�ޯ�ʵe
		vector<Layer *> _enemyList;					//�s��w�g�����L���Ǫ�
	};


}

#endif