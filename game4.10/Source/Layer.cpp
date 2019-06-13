#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Layer.h"


namespace game_framework {

	Layer::Layer() {}

	int Layer::GetY()
	{
		return _xy[1];				//取得y座標
	}

	float* Layer::GetPosition()		//取得座標
	{
		return _xy;
	}

}
