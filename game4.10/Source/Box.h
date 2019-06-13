#ifndef BOX_H
#define BOX_H
#include "Items.h"

namespace game_framework {
	class Box {
	public:
		Box();					
		void Initialize();			//��l��
		void LoadBitmap();			//�פJ�Ϥ�
		void SetXY();				//�]�w��l��m
		void OnMove();				//����D��M�˳ƪ��P�_
		void OnShow(Items*);		//���
		void Down();				//���U���
		void Up();					//���W���
		void Left();				//�������
		void Right();				//���k���
		void Open(bool);			//�}�Dor����Box(�~�h)
		void OpenOpen(bool);		//�}�Dor����Box(���h)
		bool Equip(Items*);			//�˳ƹD��
	private:
		CMovingBitmap _bm_board;
		CMovingBitmap _bm_item_board;	
		CMovingBitmap _bm_cursor;		
		CMovingBitmap _bm_equip_board;
		CMovingBitmap _bm_offense_text;
		CMovingBitmap _bm_defense_text;
		CMovingBitmap _bm_misc_text;
		CMovingBitmap _bm_unknown_item;
		CMovingBitmap _bm_item_description_board;
		CAnimation _ani_offense;			//�}�d�l�ʵe
		CAnimation _ani_defense;
		CAnimation _ani_misc;
		Item* equiped_item = nullptr;		//��۪��˳�
		Item* chosed_item = nullptr;		//��ܭn�˳ƤW���˳�
		int _category_flag;					//���� 0:offense 1:defense 2:misc 
		int _item_flag_x;					//���x,y
		int _item_flag_y;
		bool _isOpened;
		bool _isOpendOffense;
		bool _isOpendDefense;
		bool _isOpendMisc;
		int _choose_flag;
		int _NUMBER_OF_OFFENSE;				//�����O�`�D��ƶq
		int _NUMBER_OF_DEFENSE;
		int _NUMBER_OF_MISC;
		const int _ITEM_X = 40;
		const int _ITEM_Y = 40;
	};
}

#endif