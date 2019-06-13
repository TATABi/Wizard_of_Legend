#ifndef LAYER_H
#define LAYER_H

namespace game_framework {
	class Layer {
	public:
		Layer();							
		int GetY();								//用來排序圖層
		float* GetPosition();					//取圖的地板位置
		virtual void OnShow() = 0;				//顯示
	protected:
		float _xy[2] = { 0, 0 };
		//float _xy[2];							//圖"在地板"的 X, Y 座標
		//int _floor;							//貼圖位置距離角色站立的距離
		//int _centerXY;						//貼圖 X 座標距離距離角色中心 X 座標的距離
	};
}

#endif