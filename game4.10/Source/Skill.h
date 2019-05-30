#ifndef SKILL_H
#define SKILL_H
#include "Layer.h"

namespace game_framework 
{
	class Enemy;
	class GameMap;

	class Skill:public Layer{
	public :
		Skill();
		void Init();								//��l��
		bool IsDelete();							//�o���O�_�ӧR��
		bool AttackedThisEnemy(Enemy*);				//�N�Ǫ��[�J�w�����C��
		void RefreshEnemyList();					//���s�Ǫ���� (���Ǫ��i�H�Q���Ƨ���)
		virtual int GetDamage(Enemy *) = 0;
		virtual void OnMove(float *, GameMap *) = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void Initialize(int, int, float*) = 0;	
	protected:
		CAnimation _ani_skill[8];					//�ޯ�ʵe
		float _dx, _dy;								//�ޯ઺���ʦV�q
		int _cast_distance;							//�ޯ�I��ɻP���⪺�Z��
		float _rx, _ry;								//�ޯ��ڭ����m(�Ψӭץ�float int �ഫ�X�{���ݰ�)
		int _speed;									//���ʳt��
		int _lifeTime;								//�s���ɶ�
		int _damage;								//�ˮ`�q
		int _backDistance;							//���h�Z��
		int _hitbox[4];						        //hitBox ���W���y�� and l,w
		int _map_collision[4];						//��a�Ϫ��I���P�w
		bool _isDelete;								//�O�_�ӧR��
		bool _isStock;								//�d����
		vector<Layer *> _enemyList;					//�s��w�g�����L���Ǫ�
	};
}

#endif