#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {

	class CharacterData
	{
	public:
		static CharacterData* Instance();
		
		//�]�w
		void AddMoney(int);						//���Money�A�ǤJ����: �ȡA�t��: ��
		void AddDiamond(int);					//���Diamond�A�ǤJ����: �ȡA�t��: ��
		void AddHP(int);						//���HP�A�ǤJ����: �[�A�t��: ��
		void SetHP(int);						//�]�wHP
		void AddMaxHP(int);						//���Max_HP�A�ǤJ����: �[�A�t��: ��
		void SetMaxHP(int);						//�]�wMax_HP
		void AddMP(int);						//���MP�A�ǤJ����: �[�A�t��: ��
		void SetAttackCoefficient(float);		//���Attack_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetDefenseCoefficient(float);		//���Defense_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetBloodSuckCoefficient(float);	//���_blood_suck_coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetNoveCoefficient(float);			//���Move_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetCDCoefficient(float);			//���CD_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetMPChargeCoefficient(float);		//���MP_Charge_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetInvincible(bool);				//���L�Ī��A
		void ResetStatus();						//���sHP,MP,Money
		
		//����
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
		float _blood_suck_coefficient;			//�l��Y��
		float _move_coefficient;				//���ʳt�׫Y��
		float _cd_coefficient;					//�ޯ�N�o�Y��
		int _mp_charge_coefficient;				//MP�ֿn�Y��
		bool _isInvincible;						//�L�Ī��A
								
	};

	
}

#endif