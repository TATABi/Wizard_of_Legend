#ifndef A_STAR_H 
#define A_STAR_H 

#include <list> 
#include <algorithm> 

namespace game_framework {

	//??地?上每???的位置信息以及估值信息的?构体堆? 
	typedef struct _Rect
	{
		int x;
		int y;
		int h_value;  //h值???到??的Manhattan距离 
		int g_value;  //g值?起?到??的移?代价 
		struct _Rect *pre;  //指向父?? 
	}Rect;

	class A_Star
	{
	public:
		//初始化?入地?二???、地??、?，起始及??在??中的序? 
		A_Star(int *mapInfo, int width, int height, int start, int end);
		~A_Star();

		//A*查找，查找成功返回true，否?返回false 
		bool Find();
		//如果Find()函?成功，?可以?用此函?把?果路?存入到result中 
		void getResultPath();

		//?算pos??的g值 
		int get_g_value(int pos);
		//?算pos??的h值 
		int get_h_value(int pos);
		//判?pos??是否在地?? 
		bool isReachable(int pos);
		//????是否更好并判?是否已?找到路? 
		bool testRoad(int pos, int cur);

		int  *map;  //地?信息 
		Rect *rect; //父子???系? 
		std::list<Rect> result;  //查找成功后的?果路?保存在此 

	private:
		int Width;
		int Height;
		int Start;
		int End;

		std::list<int> open_list;   //open表中的???待?查的?? 
		std::list<int> close_list;  //close表中的?????不?注的?? 
	};
}
#endif 