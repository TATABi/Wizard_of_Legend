namespace game_framework {
	class Skill{
	public :
		Skill() {};
	protected:
		CAnimation ani_character_skill;	//技能施放時角色動畫
		CMovingBitmap bm_skill;			//技能圖示
		bool isPerform;				//是否正在施放
		bool isEquip;				//是否裝備中
		bool isRecover;				//角色是否能移動
		int damage;					//傷害量
		int recoverTime;			//硬直時間
		double coolDownTime;		//冷卻時間
	};


}