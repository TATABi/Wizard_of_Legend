#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {
	class CharacterData
	{
	public:
		static int Money;
		static int Diamond;
		static int HP;
		static int Max_HP;
		static int MP;
		static int Max_MP;
		static double Attack_Coefficient;
		static double Defense_Coefficient;
		static int Blood_Suck_Constant;	//�l��`��
		static double Move_Coefficient;	//���ʳt�׫Y��
		static double CD_Coefficient;	//�ޯ�N�o�Y��
		static int MP_Charge_Constant;	//MP�ֿn�`��
		static bool INVINCIBLE;			//Dash �ɵL��
		//static void InitializeStatus();

		//static bool IsEquiped_Item[];
		//static bool IsOwned_Item[];
	};
}

#endif