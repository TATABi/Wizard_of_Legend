#ifndef COUNTER_H
#define COUNTER_H

namespace game_framework {

	class Counter {
	public:
		Counter();
		void Set(int);	//設定 _time
		void Count();	//Counter 減1
		bool Result();	//Counter是否為0
		void Reset();	//重設Counter 之 _counter 為 _time 
		void Stop();	//暫停計時
		void Start();	////開始(繼續)計時
		int Now();
	private:
		int _time;			//初始化的時間
		int _counter;		//目前counter數到的時間
		bool _is_start;
	};

}

#endif

