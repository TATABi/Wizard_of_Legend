#include "Character.h"
#include "Box.h"
#include "UI.h"
#include "PausedMenu.h"
#include "CharacterData.h"
#include "Skill.h"
#include "Items.h"
#include "Bag.h"

namespace game_framework {
	

	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////
	static Items g_items;
	static UI g_ui;
	static Character g_character;
	static PausedMenu g_pauseMenu;
	static Bag g_bag;

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_BE,		
		AUDIO_TITLE,
		AUDIO_HOME,
		AUDIO_DASH,
		AUDIO_TOWN,
		AUDIO_ARRIVAL,
		AUDIO_PULL,
		AUDIO_PUTTING,
		AUDIO_PULL2
	};

	enum HOME_FLAG {
		FLAG_HOME_NORMAL,
		FLAG_JOIN,
		FLAG_BOX,
		FLAG_BOX_ITEM,
		FLAG_HOME_PAUSED,
		FLAG_HOME_OPTIONS,
		FLAG_HOME_BAG
	};

	enum TOWN_FLAG {
		FLAG_TOWN_NORMAL,
		FLAG_TOWN_PAUSED,
		FLAG_TOWN_OPTIONS,
		FLAG_TOWN_BAG
	};

	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CAnimation ani_menu_1;
		CAnimation ani_menu_2;
		CMovingBitmap bm_option;
		CMovingBitmap bm_quit;
		CMovingBitmap bm_single_player;
		int flags = 0;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun_Home : public CGameState {
	public:
		CGameStateRun_Home(CGame *g);
		~CGameStateRun_Home();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap bm_join;							// join遊戲的提示選單
		CMovingBitmap bm_loading;						// loading字樣的圖片
		CAnimation ani_light_beam;						// 角色在家中現身的動畫
		HOME_FLAG flags;										// 現在畫面的狀態 0:顯示加入遊戲的選項 1:進入遊戲(沒開任何選單) 2:開啟道具箱 3:開啟書 4:傳送至Town
		int delay_counter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Home map;								// 地圖
		Box box;
	};

	/////////////////////////////////////////////////////////////////////////////
	//Options 
	//
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun_Options : public CGameState {
	public:
		CGameStateRun_Options(CGame *g);
		~CGameStateRun_Options();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap bm_option;
	};

	/////////////////////////////////////////////////////////////////////////////
	//Town
	//
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateRun_Town : public CGameState {
	public:
		CGameStateRun_Town(CGame *g);
		~CGameStateRun_Town();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap bm_loading;						// loading字樣的圖片
		int flags;										// 
		int delay_counter;								// 進入遊戲的緩衝，避免畫面出現但音樂、圖片的還未準備好
		Map_Town map;								// 地圖

	};
	
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器

	};

}