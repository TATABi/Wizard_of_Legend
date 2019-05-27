#ifndef LAYER_H
#define LAYER_H

namespace game_framework {

	class Layer {
	public:
		Layer();
		int GetY();
		//virtual int* GetPosition() = 0;
		//virtual int* GetHitbox() = 0;
		virtual void OnShow() = 0;
	protected:
		int _xy[2] = { 0, 0 };

	};
}

#endif