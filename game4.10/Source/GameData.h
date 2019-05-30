//===========================Screen===========================//

const int CHARACTER_SCREEN_X = 285;				//����"�K�b"�ù�X�y��
const int CHARACTER_SCREEN_Y = 205;				//����"�K�b"�ù�Y�y��
const int CHARACTER_SCREEN_CENTER_X = 320;		//����ù�����X�y��
const int CHARACTER_SCREEN_CENTER_Y = 240;		//����ù�����Y�y��

//=========================Character=========================//

const int CHARACTER_MOVE_HITBOX[4] = { 24, 53, 20 , 7 };	//���Ⲿ�ʮɪ�Hitbox
const int CHARACTER_HITBOX[4] = { 23, 10, 24, 49 };			//�����������Hitbox
const int WALK_TO_RUN_TIME = 45;							//�qWalk��Run���ɶ�
const int DASH_COOLDOWN_TIME = 15;							//Dash���N�o�ɶ�
const int DASH_MOVE_TIME = 9;								//Dash���ɪ�
const int CHARACTER_HIT_RECOVER_TIME = 5;					//�Q�޵w���ɶ�
const int WALK_STEP = 6;									//Walk���B��
const int RUN_STEP = 10;									//Run���B��
const int DASH_STEP = 17;									//Dash���B��
const int MAGIC_BUFF_TIME = 0.1 * 30;						//MP������BUFF���򪺮ɶ�
const int MP_DECREASE_TIME = 0.4 * 30;						//MP������BUFF���򪺮ɶ�

//===========================Skills===========================//

//Shock Nova//
const int SHOCK_NOVA_DAMAGE = 2;							//�ˮ`
const int SHOCK_NOVA_HITBOX[3] = { 103, 105, 95 };			//��� X, Y �y�СB�b�|
const int SHOCK_NOVA_LIFETIME = 300;						//�ޯ�s���ɶ�
const int SHOCK_NOVA_MAP_HITBOX[4] = { 0, 0, 0, 0 };		//�����a�ϸI��
const int SHOCK_NOVA_SPEED = 0;								//�ޯಾ�ʳt��
const int SHOCK_NOVA_CAST_DISTANCE = 0;						//�ޯ�I��P����Z��
const int SHOCK_NOVA_RE_ATTACK_COUNTER = 6;					//�y���ˮ`����
const int SHOCK_NOVA_DELAY_COUNTER = 5;						//�ϥΧޯ�᩵��ɶ�

//Rebounding Icicles//
const int REBOUNDING_ICICKES_DAMAGE = 10;
const int REBOUNDING_ICICKES_HITBOX[4] = { 32, 10, 36, 77 };
const int REBOUNDING_ICICKES_LIFETIME = 180;
const int REBOUNDING_ICICKES_MAP_HITBOX[4] = { 35, 45, 6, 5 };
const int REBOUNDING_ICICKES_SPEED = 10;
const int REBOUNDING_ICICKES_CAST_DISTANCE = 50;