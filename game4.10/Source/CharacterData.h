#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {

	class CharacterData{
	public:
		static CharacterData& Instance();		//Singleton
		//砞﹚
		void AddMoney(int);						//эMoney肚タ计: 寥璽计: Ι
		void SetMoney(int);						//砞﹚Money
		void AddDiamond(int);					//эDiamond肚タ计: 寥璽计: Ι
		void SetDiamond(int);					//砞﹚Diamond
		void AddHP(int);						//эHP肚タ计: 璽计: Ι
		void SetHP(int);						//砞﹚HP
		void AddMaxHP(int);						//эMax_HP肚タ计: 璽计: Ι
		void SetMaxHP(int);						//砞﹚Max_HP
		void AddMP(int);						//эMP肚タ计: 璽计: Ι
		void SetAttackCoefficient(float);		//эAttack_Coefficient肚タ计: *玒计璽计: /玒计
		void SetDefenseCoefficient(float);		//эDefense_Coefficient肚タ计: *玒计璽计: /玒计
		void SetBloodSuckCoefficient(float);	//э_blood_suck_coefficient肚タ计: *玒计璽计: /玒计
		void SetNoveCoefficient(float);			//эMove_Coefficient肚タ计: *玒计璽计: /玒计
		void SetCDCoefficient(float);			//эCD_Coefficient肚タ计: *玒计璽计: /玒计
		void SetMPChargeCoefficient(float);		//эMP_Charge_Coefficient肚タ计: *玒计璽计: /玒计
		void SetInvincible(bool);				//э礚寄篈
		void ResetStatus();						//挡闽籹HP, MP, Money, MagicBuff, _stage, _gold_found, _diamond_collected, _enemies_defeated
		void SetMagicBuff(bool);				//砞﹚Magic Buff 篈
		int* GetStageResult();					//眔闽挡衡
		void SetStage(int);						//砞﹚瞷闽
		void AddMoneyCollected(int);			//э闽ずΜ栋Money
		void AddDiamondCollected(int);			//э闽ずΜ栋Diamond
		void AddEnemiesDefeated(int);			//э闽ず阑毖Enemy

		//Beater -- 国 ???????
		void LockHP();
		
		//
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
		float _blood_suck_coefficient;			//﹀玒计
		float _move_coefficient;				//簿笆硉玒计
		float _cd_coefficient;					//м玱玒计
		float _mp_charge_coefficient;				//MP仓縩玒计
		bool _isInvincible;						//礚寄篈
		bool _isMagicBuff;						//Magic Buff 篈		
		bool _isLockHP;
		int _stage;								//à︹ヘ玡┮闽
		int _money_found;						//闽い┮莉眔窥
		int _diamond_collected;					//闽い┮莉眔腳ホ
		int _enemies_defeated;					//闽い阑炳寄计秖
	};
}

#endif