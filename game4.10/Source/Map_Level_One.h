#ifndef MAP_LEVEL_ONE_H
#define MAP_LEVEL_ONE_H
#include "GameMap.h"
#include "Character.h"
#include "Items.h"

namespace game_framework {
	class Map_Level_One : public GameMap {
		enum AREA {							//Enemy�ϰ�
			AREA_1,
			AREA_2,
			AREA_3,
			AREA_4,
			AREA_5,
			AREA_6,
			AREA_7,
			AREA_8,
			AREA_9,
			AREA_10,
			AREA_11,
			AREA_BOSS
		};
	public:
		Map_Level_One(int, int);			// �]�w��l�����I
		void AddEnemy();					//�[�JEnemy
		void LoadBitmap();					//�פJ�Ϥ�
		void OnMove();						//�������ʡB�ޯ�B�Ϥ������ʩM�p��
		void SummonBoss();					//�l��Boss
		int GetMapStatus(float, float);		//���o�a�Ϫ�"�I"��T
		void Show();						//��ܦa�ϹD��
		void Init();						//��l�Ʀa��
		bool BuyByMoney(int);				//�b���d���ʶR�a�ϹD��
	private:
		void NotifyAnemy(AREA, const int*);	//�q��Anemy�l��
		CMovingBitmap _bm_hp_potion;		//HP Potion
		vector<Item*> _store_items;			//Store���� items
		CMovingBitmap _bm_attack_info,		//����Buff
					  _bm_speed_info,		//�t��Buff
					  _bm_cd_info;			//CD Buff
	};
}

#endif