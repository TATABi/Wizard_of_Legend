#ifndef A_STAR_H 
#define A_STAR_H 

#include <list> 
#include <algorithm> 

namespace game_framework {

	struct Position {
		int _x;
		int _y;
		bool operator ==(const Position &p) const
		{
			return ((this->_x == p._x) && (this->_y == p._y));
		}
	};

	struct Rect
	{
		Position _position;
		int _HValue;
		int _GValue;
		Rect *_parent;	
	};

	class A_Star {
	public:
		A_Star(const int[][1600], int, int, int, int, int);
		~A_Star();
		void getResult();
		int getX();
		int getY();
		bool getIsDone();
	private:
		int _side, _sx, _sy, _ex, _ey, _col;
		int ** _map;
		Rect **_rects;
		int * array_to_map(int x, int y) const;
		int * map_to_array(int, int) const;
		int get_h_value(Position) const;
		int get_g_value(Position) const;
		bool IsReachable(Position) const;
		bool testRoad(Position, Position);
		bool findRoad();
		std::list<Position> _openList;
		std::list<Position> _closeList;
		std::list<Position> _result;
		bool _isDone;
	};
}
#endif 