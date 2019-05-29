//===========================Screen===========================//

const int CHARACTER_SCREEN_X = 285;				//角色"貼在"螢幕X座標
const int CHARACTER_SCREEN_Y = 205;				//角色"貼在"螢幕Y座標
const int CHARACTER_SCREEN_CENTER_X = 320;		//角色螢幕中心X座標
const int CHARACTER_SCREEN_CENTER_Y = 240;		//角色螢幕中心Y座標

//=========================Character=========================//

const int CHARACTER_MOVE_HITBOX[4] = { 24, 53, 20 , 7 };	//角色移動時的Hitbox
const int CHARACTER_HITBOX[4] = { 23, 10, 24, 49 };			//角色受攻擊的Hitbox
const int WALK_TO_RUN_TIME = 45;							//從Walk至Run的時間
const int DASH_COOLDOWN_TIME = 15;							//Dash的冷卻時間
const int DASH_MOVE_TIME = 9;								//Dash的時長
const int CHARACTER_HIT_RECOVER_TIME = 5;					//被毆硬直時間
const int WALK_STEP = 6;									//Walk的步長
const int RUN_STEP = 10;									//Run的步長
const int DASH_STEP = 17;									//Dash的步長
const int MAGIC_BUFF_TIME = 0.1 * 30;						//MP集滿時BUFF持續的時間
const int MP_DECREASE_TIME = 0.4 * 30;								//MP集滿時BUFF持續的時間
//===========================Skills===========================//
