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

		
	}					// �������l
	void OnShow();					// �N���l�ϧζK��e��
	void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
	void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
	void SetMovingRight(bool flag); // �]�w�O�_���b���k����
	void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
	void SetXY(int nx, int ny);
}