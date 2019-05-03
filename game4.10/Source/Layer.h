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
		const int CHARACTER_SCREEN_X = 285; //����"�K�b"�ù�X�y��
		const int CHARACTER_SCREEN_Y = 205;	//����"�K�b"�ù�Y�y��
	};

}

#endif