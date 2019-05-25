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
		static int Blood_Suck_Constant;	//﹀盽计
		static double Move_Coefficient;	//簿笆硉玒计
		static double CD_Coefficient;	//м玱玒计
		static int MP_Charge_Constant;	//MP仓縩盽计
		static bool INVINCIBLE;			//Dash 礚寄
		//static void InitializeStatus();

		//static bool IsEquiped_Item[];
		//static bool IsOwned_Item[];
	};
}

#endif