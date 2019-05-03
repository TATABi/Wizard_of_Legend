#ifndef A_STAR_H 
#define A_STAR_H 

#include <list> 
#include <algorithm> 

namespace game_framework {

	//??�a?�W�C???����m�H���H�Φ��ȫH����?���^��? 
	typedef struct _Rect
	{
		int x;
		int y;
		int h_value;  //h��???��??��Manhattan�Z�� 
		int g_value;  //g��?�_?��??����?�Nɲ 
		struct _Rect *pre;  //���V��?? 
	}Rect;

	class A_Star
	{
	public:
		//��l��?�J�a?�G???�B�a??�B?�A�_�l��??�b??������? 
		A_Star(int *mapInfo, int width, int height, int start, int end);
		~A_Star();

		//A*�d��A�d�䦨�\��^true�A�_?��^false 
		bool Find();
		//�p�GFind()��?���\�A?�i�H?�Φ���?��?�G��?�s�J��result�� 
		void getResultPath();

		//?��pos??��g�� 
		int get_g_value(int pos);
		//?��pos??��h�� 
		int get_h_value(int pos);
		//�P?pos??�O�_�b�a?? 
		bool isReachable(int pos);
		//????�O�_��n�}�P?�O�_�w?����? 
		bool testRoad(int pos, int cur);

		int  *map;  //�a?�H�� 
		Rect *rect; //���l???�t? 
		std::list<Rect> result;  //�d�䦨�\�Z��?�G��?�O�s�b�� 

	private:
		int Width;
		int Height;
		int Start;
		int End;

		std::list<int> open_list;   //open����???��?�d��?? 
		std::list<int> close_list;  //close����?????��?�`��?? 
	};
}
#endif 