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
		void OnMove(int, int, vector<Skill*>&);			//傳入現在場上所有由主角發出的魔法
		bool IsLive();									//活著嗎
		bool CanAchieved(int, int);						//判斷能否移動
		void NotifyCharge();							//開始追擊Character
		int Area();										//所在區域
		void SetXY(int, int);							//移動
		int* GetMoveHitbox();							//移動碰撞框
		int* GetHitbox();								//傷害碰撞框
		void LoadBitmap();								//匯入圖片
		bool IsInAttackZone(int, int);					//判斷Character是否在攻擊範圍
		void Dead();									//主動使Enemy死亡(透過特殊按鍵)
		bool IsReset();									//是否是透過按鍵使Enemy死亡
		void ResetAnimation();							//重置動畫
		virtual vector<Reward*> CreateReward();			//產生血球、錢、鑽石掉落物
		virtual void Init() = 0;						//初始化
		virtual void LoadEnemyBitmap() = 0;				//匯入子類別所需的圖
		virtual void Move(int, int) = 0;				//子類別的計算
		virtual void OnShow() = 0;						//顯示畫面
		virtual void PlayDeadAudio();					//死亡音效
	protected:
		enum STATE {									//Enemy狀態
			ATTACKING,
			CHARGING,
			RESET,
			NOTHING,
			HIT_RECOVER,
			SKILL
		};

		enum DIRECTION {								//Enemy方向
			LEFT,
			RIGHT
		};

		void MoveToTarget(int, int);					//移動
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
		bool _is_detour,								//繞路狀態
			 _is_left,
			 _is_right,
			 _is_up,
			 _is_down;
		bool _neighbor[4];								// 上下左右的Logic點
		int _detour_time;
		int _damage;
		int _attack_counter;
		int _hit_recover_counter;
		bool _hit_recover_flag;
		bool _is_transfer;
		bool _isAttack;
		bool _isReset;
		int _invincible_counter;						//無敵狀態的時間
		int _stock_counter;
	};
}

#endif