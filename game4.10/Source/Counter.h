#ifndef COUNTER_H
#define COUNTER_H

namespace game_framework {

	class Counter {
	public:
		Counter();
		void Set(int);	//�]�w _time
		void Count();	//Counter ��1
		bool Result();	//Counter�O�_��0
		void Reset();	//���]Counter �� _counter �� _time 
		void Stop();	//�Ȱ��p��
		void Start();	////�}�l(�~��)�p��
		int Now();
	private:
		int _time;			//��l�ƪ��ɶ�
		int _counter;		//�ثecounter�ƨ쪺�ɶ�
		bool _is_start;
	};

}

#endif

