#ifndef GAME_DATA_H
#define GAME_DATA_H

//============================Save============================//
const string SAVE_DATA_PATH = "./Data/save_data.txt";				//存檔路徑
const char CHAR_TAB = '\t';										//間格
const string STRING_TURE = "true";								//擁有道具
const string STRING_FALSE = "false";							//沒有道具

//===========================Screen===========================//
const int CHARACTER_SCREEN_X = 285;								//角色"貼在"螢幕X座標
const int CHARACTER_SCREEN_Y = 205;								//角色"貼在"螢幕Y座標
const int CHARACTER_SCREEN_CENTER_X = 320;						//角色螢幕中心X座標
const int CHARACTER_SCREEN_CENTER_Y = 240;						//角色螢幕中心Y座標

//=========================Character=========================//
const int CHARACTER_MOVE_HITBOX[4] = { 24, 53, 20 , 7 };		//角色移動時的Hitbox
const int CHARACTER_HITBOX[4] = { 23, 10, 24, 49 };				//角色受攻擊的Hitbox
const int WALK_TO_RUN_TIME = 45;								//從Walk至Run的時間
const int DASH_COOLDOWN_TIME = 15;								//Dash的冷卻時間
const int DASH_MOVE_TIME = 9;									//Dash的時長
const int CHARACTER_HIT_RECOVER_TIME = 5;						//被毆硬直時間
const int WALK_STEP = 6;										//Walk的步長
const int RUN_STEP = 10;										//Run的步長
const int DASH_STEP = 17;										//Dash的步長
const int MAGIC_BUFF_TIME = int(0.1 * 30);						//MP集滿時BUFF持續的時間
const int MP_DECREASE_TIME = int(0.4 * 30);						//MP集滿時BUFF持續的時間
const int DROP_COUNTER_TIME = 15;								//墜落後復原位置的時間
const int TRAP_COUNTER_TIME = 10;								//觸發陷阱時間
const int DROP_RESET_ANI_TIME = 8;								//掉落後多久播動畫

//===========================Skills===========================//
//Air Spinner//
const int AIR_SPINNER_DAMAGE = 6;								//傷害
const int AIR_SPINNER_HITBOX[3] = { 23, 23, 20 };				//圓心 X, Y 座標、半徑
const int AIR_SPINNER_LIFETIME = 100;							//技能存活時間
const int AIR_SPINNER_MAP_HITBOX[4] = { 0, 0, 0, 0 };			//不受地圖碰撞
const int AIR_SPINNER_SPEED = 0;								//技能移動速度
const int AIR_SPINNER_CAST_DISTANCE = 40;						//技能施放與角色距離
const int AIR_SPINNER_COOLDOWN = 0;								//冷卻時間

//Shock Nova//
const int SHOCK_NOVA_DAMAGE = 4;								//傷害
const int SHOCK_NOVA_HITBOX[3] = { 103, 105, 95 };				//圓心 X, Y 座標、半徑
const int SHOCK_NOVA_LIFETIME = 300;							//技能存活時間
const int SHOCK_NOVA_MAP_HITBOX[4] = { 0, 0, 0, 0 };			//不受地圖碰撞
const int SHOCK_NOVA_SPEED = 0;									//技能移動速度
const int SHOCK_NOVA_CAST_DISTANCE = 0;							//技能施放與角色距離
const int SHOCK_NOVA_RE_ATTACK_COUNTER = 6;						//造成傷害次數
const int SHOCK_NOVA_DELAY_COUNTER = 5;							//使用技能後延遲時間
const int SHOCK_NOVA_COOLDOWN = 3 * 30;							//冷卻時間

//Rebounding Icicles//
const int REBOUNDING_ICICKES_DAMAGE = 20;						//傷害
const int REBOUNDING_ICICKES_HITBOX[4] = { 32, 10, 36, 77 };	//左上 X, Y 座標、Length、Width
const int REBOUNDING_ICICKES_LIFETIME = 180;					//技能存活時間
const int REBOUNDING_ICICKES_MAP_HITBOX[4] = { 35, 45, 6, 5 };	// 地圖碰撞
const int REBOUNDING_ICICKES_SPEED = 10;						//技能移動速度
const int REBOUNDING_ICICKES_CAST_DISTANCE = 50;				//技能施放與角色距離
const int REBOUNDING_ICICKES_COOLDOWN = 1 * 30;					//冷卻時間

//===========================Enemy===========================//
//Blockhead//
const int BLOCKHEAD_HP = 10000;									//血量
const int BLOCKHEAD_STEP = 0;									//移動速度
const int BLOCKHEAD_ZONE = 0;									//攻擊區域
const int BLOCKHEAD_DAMAGE = 0;									//傷害
const int BLOCKHEAD_HITBOX[4] = { 0, 0, 34, 57 };				//承受傷害的Hitbox
const int BLOCKHEAD_MOVE_HITBOX[4] = { 8, 41, 16, 16 };			//移動的Hitbox
const int BLOCKHEAD_CHARGING_ZONE = 0;							//追擊範圍

//BlackMan//
const int BLACKMAN_HP = 70;										//血量
const int BLACKMAN_STEP = 5;									//移動速度
const int BLACKMAN_ZONE = 30;									//攻擊區域
const int BLACKMAN_DAMAGE = 15;									//傷害
const int BLACKMAN_ATTACK_DELAY_TIME = 7;						//進入攻擊範圍後延遲的攻擊時間
const int BLACKMAN_HITBOX[4] = {22, 15, 24, 44 };				//承受傷害的Hitbox
const int BLACKMAN_MOVE_HITBOX[4] = { 29, 47, 17, 12 };			//移動的Hitbox
const int BLACKMAN_CHARGING_ZONE = 300;							//追擊範圍

//Skime//
const int SLIME_HP = 50;										//血量
const int SLIME_STEP = 3;										//移動速度
const int SLIME_ZONE = 30;										//攻擊區域
const int SLIME_DAMAGE = 10;									//傷害
const int SLIME_ATTACK_DELAY_TIME = 7;							//進入攻擊範圍後延遲的攻擊時間
const int SLIME_HITBOX[4] = { 4, 10, 25, 24 };					//承受傷害的Hitbox
const int SLIME_MOVE_HITBOX[4] = { 5, 31, 25, 5 };				//移動的Hitbox
const int SLIME_CHARGING_ZONE = 300;							//追擊範圍

//Boss//
const int BOSS_HP = 700;										//血量
const int BOSS_STEP = 5;										//移動速度
const int BOSS_ZONE = 60;										//攻擊區域
const int BOSS_DAMAGE = 40;										//傷害
const int BOSS_ATTACK_DELAY_TIME = 7;							//進入攻擊範圍後延遲的攻擊時間
const int BOSS_HITBOX[4] = {39, 42, 60, 60};					//承受傷害的Hitbox
const int BOSS_MOVE_HITBOX[4] = {43, 86, 40, 13};				//移動的Hitbox
const int BOSS_CHARGE_ZONE = 800;								//追擊範圍

//============================Home============================//
const int HOME_CHARACTER_XY[2] = { 740 , 918 };					//角色初始位置
const int HOME_AREA_1[4] = { 633, 811, 926, 1081};				//左上 & 右下座標

//============================Town============================//
const int TOWN_CHARACTER_XY[2] = { 770, 1065 };					//角色初始位置
const int TOWN_STORE_XY[2] = { 520, 1018 };						//商店所在位置
const int TOWN_STORE_ITEM[2] = { 525 , 990};					//物品擺放位置
const string Town_Or_Home = "Town or Home";

//==========================Level_One==========================//
const int LEVEL_ONE_CHARACTER_XY[2] = {3000, 2830};
const int LEVEL_ONE_STORE_XY[2] = {2547, 345};
const int DROP_DAMAGE = 30;										//墜落傷害
const int TRAP_DAMAGE = 30;										//陷阱傷害
const int LEVEL_AREA_1[4] = { 2285, 3162, 3076, 3251 };
const int LEVEL_AREA_2[4] = { 3466, 2720, 3860, 2877 };
const int LEVEL_AREA_3[4] = { 1818, 2425, 2405, 2724 };
const int LEVEL_AREA_4[4] = { 1325, 2243, 1612, 2730 };
const int LEVEL_AREA_5[4] = { 757, 2620, 1127, 3098 };
const int LEVEL_AREA_6[4] = { 88, 2458, 356, 2678 };
const int LEVEL_AREA_7[4] = { 653, 2100, 945, 2275 };
const int LEVEL_AREA_8[4] = { 1430, 1657, 1820, 2028 };
const int LEVEL_AREA_9[4] = { 1916, 1647, 2405, 1926 };
const int LEVEL_AREA_10[4] = { 2012, 1170, 2201, 1351 };
const int LEVEL_AREA_11[4] = { 2590, 1318, 3024, 1680 };
const int LEVEL_AREA_BOSS[4] = { 3248, 372, 3820, 845 };
const int LEVEL_ONE_PRESS_BOSS[2] = { 3509, 668 };
const int LEVEL_ONE_PRESS_ITEM_STORE_1[2] = { 2545, 280 };
const int LEVEL_ONE_PRESS_ITEM_STORE_2[2] = { 2622, 280 };
const int LEVEL_ONE_PRESS_ITEM_STORE_3[2] = { 2705, 280 };
const int LEVEL_ONE_PRESS_BUFF_STORE_1[2] = { 1093, 1445 };
const int LEVEL_ONE_PRESS_BUFF_STORE_2[2] = { 1170, 1445 };
const int LEVEL_ONE_PRESS_BUFF_STORE_3[2] = { 1253, 1445 };
const int LEVEL_ONE_PRESS_POTION_STORE[2] = { 1274, 3635 };
const int LEVEL_ONE_ITEM_STORE[2] = { 2542, 313 };
const int LEVEL_ONE_BUFF_STORE_1[2] = { 1080, 1465 };
const int LEVEL_ONE_BUFF_STORE_2[2] = { 1155, 1465 };
const int LEVEL_ONE_BUFF_STORE_3[2] = { 1230, 1465 };
const int LEVEL_ONE_POTION_STORE[2] = { 1275, 3666 };

//============================Items============================//
const int NUM_ITEMS = 7;										//Item數量
const int NUMBER_OF_OFFENSE = 2;
const int NUMBER_OF_DEFENSE = 3;
const int NUMBER_OF_MISC = 1;

#endif