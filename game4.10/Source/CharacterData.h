#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {

	class CharacterData{
	public:
		static CharacterData& Instance();		//Singleton
		//設定
		void AddMoney(int);						//更改Money，傳入正數: 賺，負數: 扣
		void SetMoney(int);						//設定Money
		void AddDiamond(int);					//更改Diamond，傳入正數: 賺，負數: 扣
		void SetDiamond(int);					//設定Diamond
		void AddHP(int);						//更改HP，傳入正數: 加，負數: 扣
		void SetHP(int);						//設定HP
		void AddMaxHP(int);						//更改Max_HP，傳入正數: 加，負數: 扣
		void SetMaxHP(int);						//設定Max_HP
		void AddMP(int);						//更改MP，傳入正數: 加，負數: 扣
		void AttackBuff(bool);						//啟動attack buff
		void SpeedBuff(bool);						//啟動speed buff
		void CooldownBuff(bool);					//啟動cooldown buff
		void SetAttackCoefficient(float);		//更改Attack_Coefficient，傳入正數: *係數，負數: /係數
		void SetDefenseCoefficient(float);		//更改Defense_Coefficient，傳入正數: *係數，負數: /係數
		void SetBloodSuckCoefficient(float);	//更改_blood_suck_coefficient，傳入正數: *係數，負數: /係數
		void SetMoveCoefficient(float);			//更改Move_Coefficient，傳入正數: *係數，負數: /係數
		void SetCDCoefficient(float);			//更改CD_Coefficient，傳入正數: *係數，負數: /係數
		void SetMPChargeCoefficient(float);		//更改MP_Charge_Coefficient，傳入正數: *係數，負數: /係數
		void SetInvincible(bool);				//更改無敵狀態
		void ResetStatus();						//結束關卡，重製HP, MP, Money, MagicBuff, _stage, _gold_found, _diamond_collected, _enemies_defeated
		void SetMagicBuff(bool);				//設定Magic Buff 狀態
		int* GetStageResult();					//取得關卡結算
		void SetStage(int);						//設定現在關卡
		void AddMoneyCollected(int);			//更改關卡內收集的Money
		void AddDiamondCollected(int);			//更改關卡內收集的Diamond
		void AddEnemiesDefeated(int);			//更改關卡內擊敗的Enemy

		//Beater -- 封弊者 ???????
		void LockHP(bool);
		void SuperMode(bool);

		//取值
		int MONEY();
		int DIAMOND();
		int HP();
		int MAX_HP();
		int MP();
		int MAX_MP();
		float ATTACK_COEFFICIENT();
		float DEFENSE_COEFFICIENT();
		float BLOOD_SUCK_COEFFICIENT();
		float MOVE_COEFFICIENT();
		float CD_COEFFICIENT();
		float MP_CHARGE_COEFFICIENT();
		bool ISVINCIBLE();
		bool ISMAGICBUFF();
		bool ISATTACKBUFF();
		bool ISSPEEDBUFF();
		bool ISCOOLDOWNBUFF();
		bool ISSUPERMODE();
	protected:
		CharacterData();
	private:
		int _money;
		int _diamond;
		int _hp;
		int _max_hp;
		int _mp;
		int _max_mp;
		float _attack_coefficient;
		float _defense_coefficient;
		float _blood_suck_coefficient;			//吸血係數
		float _move_coefficient;				//移動速度係數
		float _cd_coefficient;					//技能冷卻係數
		float _mp_charge_coefficient;				//MP累積係數
		bool _isInvincible;						//無敵狀態
		bool _isMagicBuff;						//Magic Buff 狀態		
		bool _isLockHP;
		int _stage;								//角色目前所在關卡
		int _money_found;						//關卡中所獲得的金錢
		int _diamond_collected;					//關卡中所獲得的寶石
		int _enemies_defeated;					//關卡中擊殺的敵人數量
		bool _isAttackBuff, _isSpeedBuff, _isCooldownBuff;	//紀錄buff是否啟動
		bool _isSuperMode;
	};
}

#endif