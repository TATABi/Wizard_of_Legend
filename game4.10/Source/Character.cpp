#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"

namespace game_framework {
	
	Character::Character() {
		Initialize();
	}

	void Character::Initialize() {
		const int X_POS = 280;
		const int Y_POS = 400;
		_x = X_POS;
		_y = Y_POS;	
	}
	void Character::OnMove() {

		
	}					// 移動擦子
	void OnShow();					// 將擦子圖形貼到畫面
	void SetMovingDown(bool flag);	// 設定是否正在往下移動
	void SetMovingLeft(bool flag);	// 設定是否正在往左移動
	void SetMovingRight(bool flag); // 設定是否正在往右移動
	void SetMovingUp(bool flag);	// 設定是否正在往上移動
	void SetXY(int nx, int ny);
}