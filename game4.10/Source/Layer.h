#ifndef LAYER_H
#define LAYER_H

namespace game_framework {
	class Layer {
	public:
		Layer();							
		int GetY();								//�ΨӱƧǹϼh
		float* GetPosition();					//���Ϫ��a�O��m
		virtual void OnShow() = 0;				//���
	protected:
		float _xy[2] = { 0, 0 };
		//float _xy[2];							//��"�b�a�O"�� X, Y �y��
		//int _floor;							//�K�Ϧ�m�Z�����⯸�ߪ��Z��
		//int _centerXY;						//�K�� X �y�жZ���Z�����⤤�� X �y�Ъ��Z��
	};
}

#endif