#ifndef GAME_DATA_H
#define GAME_DATA_H

//===========================Screen===========================//
const string SAVE_DATA_PATH = "Data/save_data";
const char CHAR_TAB = '\t';
const string STRING_TURE = "true";
const string STRING_FALSE = "false";

//===========================Screen===========================//

const int CHARACTER_SCREEN_X = 285;								//����"�K�b"�ù�X�y��
const int CHARACTER_SCREEN_Y = 205;								//����"�K�b"�ù�Y�y��
const int CHARACTER_SCREEN_CENTER_X = 320;						//����ù�����X�y��
const int CHARACTER_SCREEN_CENTER_Y = 240;						//����ù�����Y�y��

//=========================Character=========================//

const int CHARACTER_MOVE_HITBOX[4] = { 24, 53, 20 , 7 };		//���Ⲿ�ʮɪ�Hitbox
const int CHARACTER_HITBOX[4] = { 23, 10, 24, 49 };				//�����������Hitbox
const int WALK_TO_RUN_TIME = 45;								//�qWalk��Run���ɶ�
const int DASH_COOLDOWN_TIME = 15;								//Dash���N�o�ɶ�
const int DASH_MOVE_TIME = 9;									//Dash���ɪ�
const int CHARACTER_HIT_RECOVER_TIME = 5;						//�Q�޵w���ɶ�
const int WALK_STEP = 6;										//Walk���B��
const int RUN_STEP = 10;										//Run���B��
const int DASH_STEP = 17;										//Dash���B��
const int MAGIC_BUFF_TIME = int(0.1 * 30);						//MP������BUFF���򪺮ɶ�
const int MP_DECREASE_TIME = int(0.4 * 30);						//MP������BUFF���򪺮ɶ�
const int DROP_COUNTER_TIME = 90;								//�Y���h�[��_���m
const int TRAP_COUNTER_TIME = 10;
//===========================Skills===========================//

//Air Spinner//
const int AIR_SPINNER_DAMAGE = 3;
const int AIR_SPINNER_HITBOX[3] = { 23, 23, 20 };
const int AIR_SPINNER_LIFETIME = 100;
const int AIR_SPINNER_MAP_HITBOX[4] = { 0, 0, 0, 0 };
const int AIR_SPINNER_SPEED = 0;
const int AIR_SPINNER_CAST_DISTANCE = 40;
const int AIR_SPINNER_COOLDOWN = 0;

//Shock Nova//
const int SHOCK_NOVA_DAMAGE = 2;								//�ˮ`
const int SHOCK_NOVA_HITBOX[3] = { 103, 105, 95 };				//��� X, Y �y�СB�b�|
const int SHOCK_NOVA_LIFETIME = 300;							//�ޯ�s���ɶ�
const int SHOCK_NOVA_MAP_HITBOX[4] = { 0, 0, 0, 0 };			//�����a�ϸI��
const int SHOCK_NOVA_SPEED = 0;									//�ޯಾ�ʳt��
const int SHOCK_NOVA_CAST_DISTANCE = 0;							//�ޯ�I��P����Z��
const int SHOCK_NOVA_RE_ATTACK_COUNTER = 6;						//�y���ˮ`����
const int SHOCK_NOVA_DELAY_COUNTER = 5;							//�ϥΧޯ�᩵��ɶ�
const int SHOCK_NOVA_COOLDOWN = 3 * 30;							//�N�o�ɶ�

//Rebounding Icicles//
const int REBOUNDING_ICICKES_DAMAGE = 20;						//�ˮ`
const int REBOUNDING_ICICKES_HITBOX[4] = { 32, 10, 36, 77 };	//���W X, Y �y�СBLength�BWidth
const int REBOUNDING_ICICKES_LIFETIME = 180;					//�ޯ�s���ɶ�
const int REBOUNDING_ICICKES_MAP_HITBOX[4] = { 35, 45, 6, 5 };	// �a�ϸI��
const int REBOUNDING_ICICKES_SPEED = 10;						//�ޯಾ�ʳt��
const int REBOUNDING_ICICKES_CAST_DISTANCE = 50;				//�ޯ�I��P����Z��
const int REBOUNDING_ICICKES_COOLDOWN = 1 * 30;					//�N�o�ɶ�

//===========================Enemy===========================//

//Blockhead//
const int BLOCKHEAD_HP = 10000;									//��q
const int BLOCKHEAD_STEP = 0;									//���ʳt��
const int BLOCKHEAD_ZONE = 0;									//�����ϰ�
const int BLOCKHEAD_DAMAGE = 0;									//�ˮ`
const int BLOCKHEAD_HITBOX[4] = { 0, 0, 34, 57 };				//�Ө��ˮ`��Hitbox
const int BLOCKHEAD_MOVE_HITBOX[4] = { 8, 41, 16, 16 };			//���ʪ�Hitbox
const int BLOCKHEAD_CHARGING_ZONE = 0;

//BlackMan//
const int BLACKMAN_HP = 100;									//��q
const int BLACKMAN_STEP = 5;									//���ʳt��
const int BLACKMAN_ZONE = 30;									//�����ϰ�
const int BLACKMAN_DAMAGE = 20;									//�ˮ`
const int BLACKMAN_ATTACK_DELAY_TIME = 7;						//�i�J�����d��᩵�𪺧����ɶ�
const int BLACKMAN_HITBOX[4] = {22, 15, 24, 44 };				//�Ө��ˮ`��Hitbox
const int BLACKMAN_MOVE_HITBOX[4] = { 29, 47, 17, 12 };			//���ʪ�Hitbox
const int BLACKMAN_CHARGING_ZONE = 300;							//�l���d��

//Skime//
const int SLIME_HP = 50;										//��q
const int SLIME_STEP = 3;										//���ʳt��
const int SLIME_ZONE = 30;										//�����ϰ�
const int SLIME_DAMAGE = 10;									//�ˮ`
const int SLIME_ATTACK_DELAY_TIME = 7;							//�i�J�����d��᩵�𪺧����ɶ�
const int SLIME_HITBOX[4] = { 4, 10, 25, 24 };					//�Ө��ˮ`��Hitbox
const int SLIME_MOVE_HITBOX[4] = { 5, 31, 25, 5 };				//���ʪ�Hitbox
const int SLIME_CHARGING_ZONE = 300;							//�l���d��


//============================Home============================//

const int HOME_CHARACTER_XY[2] = { 740 , 918 };					//�����l��m

//============================Town============================//

const int TOWN_CHARACTER_XY[2] = { 770, 1065 };					//�����l��m
const int TOWN_STORE_XY[2] = { 520, 1018 };						//�ө��Ҧb��m
const int TOWN_STORE_ITEM[2] = { 525 , 990};					//���~�\���m
const string Town_Or_Home = "Town or Home";

//==========================Level_One==========================//

const int LEVEL_ONE_CHARACTER_XY[2] = {3000, 2830};
const int DROP_DAMAGE = 30;										//�Y���ˮ`
const int TRAP_DAMAGE = 30;										//�����ˮ`

//============================Items============================//

const int NUM_ITEMS = 7;

#endif