#ifndef ENEMY_H
#define ENEMY_H
#include "Skill.h"
#include "Layer.h"

namespace game_framework {
	class GameMap;
	class Reward;
	class Enemy : public Layer {
	public:
		Enemy(int, int, int, GameMap*);
		void Initialize(int, int);
		void OnMove(int, int, vector<Skill*>&);			//�ǤJ�{�b���W�Ҧ��ѥD���o�X���]�k
		bool IsLive();									//���۶�
		bool CanAchieved(int, int);						//�P�_��_����
		void NotifyCharge();							//�}�l�l��Character
		int Area();										//�Ҧb�ϰ�
		void SetXY(int, int);							//����
		int* GetMoveHitbox();							//���ʸI����
		int* GetHitbox();								//�ˮ`�I����
		void LoadBitmap();								//�פJ�Ϥ�
		bool IsInAttackZone(int, int);					//�P�_Character�O�_�b�����d��
		void Dead();									//�D�ʨ�Enemy���`(�z�L�S�����)
		bool IsReset();									//�O�_�O�z�L�����Enemy���`
		void ResetAnimation();							//���m�ʵe
		virtual vector<Reward*> CreateReward();			//���ͦ�y�B���B�p�۱�����
		virtual void Init() = 0;						//��l��
		virtual void LoadEnemyBitmap() = 0;				//�פJ�l���O�һݪ���
		virtual void Move(int, int) = 0;				//�l���O���p��
		virtual void OnShow() = 0;						//��ܵe��
		virtual void PlayDeadAudio();					//���`����
	protected:
		enum STATE {									//Enemy���A
			ATTACKING,
			CHARGING,
			RESET,
			NOTHING,
			HIT_RECOVER,
			SKILL
		};

		enum DIRECTION {								//Enemy��V
			LEFT,
			RIGHT
		};

		void MoveToTarget(int, int);					//����
		STATE _state;
		DIRECTION _direction;
		CMovingBitmap _bm_stand_left, _bm_stand_right, _bm_stand;
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;
		CAnimation _ani_hurt;
		CAnimation _ani_left, _ani_right;
		CAnimation _ani_attack_left, _ani_attack_right;
		CAnimation _ani_skill;
		GameMap* _map;
		int _hp, _step, _zone;
		int _area;
		int _ori_x, _ori_y;
		int _target_x, _target_y;
		int _hitbox[4] = { 0 }; 
		int _move_hitbox[4] = { 0 }; 					
		int _charge_zone;
		bool _is_x_arrive;
		bool _is_y_arrive;
		bool _is_detour,								//¶�����A
			 _is_left,
			 _is_right,
			 _is_up,
			 _is_down;
		bool _neighbor[4];								// �W�U���k��Logic�I
		int _detour_time;
		int _damage;
		int _attack_counter;
		int _hit_recover_counter;
		bool _hit_recover_flag;
		bool _is_transfer;
		bool _isAttack;
		bool _isReset;
		int _invincible_counter;						//�L�Ī��A���ɶ�
		int _stock_counter;
	};
}

#endif