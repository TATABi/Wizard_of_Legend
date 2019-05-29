#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {

	class CharacterData
	{
	public:
		static CharacterData* Instance();
		
		//砞﹚
		void AddMoney(int);						//эMoney肚タ计: 寥璽计: Ι
		void AddDiamond(int);					//эDiamond肚タ计: 寥璽计: Ι
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
		void ResetStatus();						//籹HP,MP,Money
		
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

	protected:
		CharacterData();

	private:
		static CharacterData* _instance;
		

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
		int _mp_charge_coefficient;				//MP仓縩玒计
		bool _isInvincible;						//礚寄篈
								
	};

	
}

#endif