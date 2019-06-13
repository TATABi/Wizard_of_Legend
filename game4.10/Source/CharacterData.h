#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {

	class CharacterData{
	public:
		static CharacterData& Instance();		//Singleton
		//�]�w
		void AddMoney(int);						//���Money�A�ǤJ����: �ȡA�t��: ��
		void SetMoney(int);						//�]�wMoney
		void AddDiamond(int);					//���Diamond�A�ǤJ����: �ȡA�t��: ��
		void SetDiamond(int);					//�]�wDiamond
		void AddHP(int);						//���HP�A�ǤJ����: �[�A�t��: ��
		void SetHP(int);						//�]�wHP
		void AddMaxHP(int);						//���Max_HP�A�ǤJ����: �[�A�t��: ��
		void SetMaxHP(int);						//�]�wMax_HP
		void AddMP(int);						//���MP�A�ǤJ����: �[�A�t��: ��
		void AttackBuff(bool);					//�Ұ�attack buff
		void SpeedBuff(bool);					//�Ұ�speed buff
		void CooldownBuff(bool);				//�Ұ�cooldown buff
		void SetAttackCoefficient(float);		//���Attack_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetDefenseCoefficient(float);		//���Defense_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetBloodSuckCoefficient(float);	//���_blood_suck_coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetMoveCoefficient(float);			//���Move_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetCDCoefficient(float);			//���CD_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetMPChargeCoefficient(float);		//���MP_Charge_Coefficient�A�ǤJ����: *�Y�ơA�t��: /�Y��
		void SetInvincible(bool);				//���L�Ī��A
		void ResetStatus();						//�������d�A���sHP, MP, Money, MagicBuff, _stage, _gold_found, _diamond_collected, _enemies_defeated
		void SetMagicBuff(bool);				//�]�wMagic Buff ���A
		vector<int> GetStageResult();			//���o���d����
		void SetStage(int);						//�]�w�{�b���d
		void AddMoneyCollected(int);			//������d��������Money
		void AddDiamondCollected(int);			//������d��������Diamond
		void AddEnemiesDefeated(int);			//������d�����Ѫ�Enemy

		//Cheat
		void LockHP(bool);
		void SuperMode(bool);

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
		bool ISMAGICBUFF();
		bool ISATTACKBUFF();
		bool ISSPEEDBUFF();
		bool ISCOOLDOWNBUFF();
		bool ISSUPERMODE();
	protected:
		CharacterData();
	private:
		int _money;								//��
		int _diamond;							//�p��
		int _hp;								//HP
		int _max_hp;							//�̤jHP
		int _mp;								//MP
		int _max_mp;							//�̤jMP
		float _attack_coefficient;				//�����Y��
		float _defense_coefficient;				//���m�Y��
		float _blood_suck_coefficient;			//�l��Y��
		float _move_coefficient;				//���ʳt�׫Y��
		float _cd_coefficient;					//�ޯ�N�o�Y��
		float _mp_charge_coefficient;			//MP�ֿn�Y��
		bool _isInvincible;						//�L�Ī��A
		bool _isMagicBuff;						//Magic Buff ���A		
		bool _isLockHP;							//��wHP�A�L�k�y���ˮ`
		int _stage;								//����ثe�Ҧb���d
		int _money_found;						//���d������o������
		int _diamond_collected;					//���d������o���_��
		int _enemies_defeated;					//���d���������ĤH�ƶq
		bool _isSuperMode;						//�}�ҤW�ҼҦ�
		bool _isAttackBuff,						// ����buff�O�_�Ұ�
			_isSpeedBuff,
			_isCooldownBuff;
	};
}

#endif