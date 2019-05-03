#ifndef LAYER_H
#define LAYER_H

namespace game_framework {

	class Layer {
	public:
		Layer();
		int GetY();
		virtual void OnShow() = 0;
	protected:
		int _xy[2] = {0, 0};
		const int CHARACTER_SCREEN_X = 285; //角色"貼在"螢幕X座標
		const int CHARACTER_SCREEN_Y = 205;	//角色"貼在"螢幕Y座標
	};

}

#endif