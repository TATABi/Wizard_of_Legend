#ifndef ITEM_H
#define ITEM_H

namespace game_framework {
	class Item {
	public:
		Item(int);
		void Initialize();
		void OnMove();
		void OnShow();
		void Equip(bool);	// 穿/脫 裝備
		void MeetCondition();	//滿足發動能力條件
		bool IsEquiped();	// 是否裝備
		void Effect();		// 啟動能力
		bool HaveItem();
		bool BuyItem();
	private:
		CMovingBitmap bm_item;
		bool isequiped;			//是否裝備
		bool meet_condition;	//滿足發動條件
		bool have_luanched;		//發動
		bool have_it;			//擁有該裝備
		int money;
	};

}


#endif