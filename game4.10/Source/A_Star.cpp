#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "A_Star.h"

namespace game_framework {
	A_Star::A_Star(const int map[][1600], int sx, int sy, int ex, int ey, int side) : _sx(sx), _sy(sy), _ex(ex), _ey(ey), _side(side)
	{
		_isDone = false;
		_map = nullptr;
		_rects = nullptr;
		if((_sx != _ex) || (_sy != _ey))
		{
			_col = sizeof(map[0]) / sizeof(map[0][0]);
			//new _map & rects
			_map = new int *[_side];
			_rects = new Rect*[_side];
			for (int i = 0; i < _side; i++)
			{
				_rects[i] = new Rect[_side];
				_map[i] = new int[_side];
			}

			//initialize rects
			for (int i = 0; i < _side; i++)
			{
				for (int j = 0; j < _side; j++)
				{
					_rects[i][j]._position._x = i;
					_rects[i][j]._position._y = j;
					_rects[i][j]._parent = NULL;
				}
			}
			//initialize map
			for (int i = 0; i < _side; i++)
			{
				for (int j = 0; j < _side; j++)
				{
					int *mapXY = array_to_map(i, j);									//�Ni, j�ন�a�Ϯy��
					int mapX = mapXY[0];
					int mapY = mapXY[1];
					if ((mapX > 0) && (mapX < _col) && (mapY > 0) && (mapY < _col))		//�p�G�S�W�Xmap�d��A�Nmap��T�g�J_map
					{
						_map[i][j] = map[mapX][mapY];
					}
					else
					{
						_map[i][j] = -1;												//����q�L
					}
				}
			}
			//�N�_�I�[�Jopenlist
			_rects[_side / 2][_side / 2]._parent = NULL;
			_rects[_side / 2][_side / 2]._GValue = 0;
			_rects[_side / 2][_side / 2]._HValue = get_h_value(_rects[_side / 2][_side / 2]._position);
			_openList.push_back(_rects[_side / 2][_side / 2]._position);
			findRoad();
			getResult();
			_isDone = true;
		}	
	}

	A_Star::~A_Star()
	{
		if (_map != nullptr)
		{
			for (int i = 0; i < _side; i++)
			{
				delete[] _map[i];
			}
			delete[] _map;
		}
		if (_rects != nullptr)
		{
			for (int i = 0; i < _side; i++)
			{
				delete[] _rects[i];
			}
			delete[] _rects;
		}
	}

	int* A_Star::array_to_map(int x, int y) const
	{
		int tempX = x - _side / 2 + _sx;
		int tempY = y - _side / 2 + _sy;
		int ans[2] = { tempX, tempY };
		ans[0] = tempX;
		ans[1] = tempY;
		return ans;
	}

	int * A_Star::map_to_array(int x, int y) const
	{
		int tempX = x - _sx + _side / 2;
		int tempY = y - _sy + _side / 2;
		int ans[2] = { tempX, tempY };
		ans[0] = tempX;
		ans[1] = tempY;
		return ans;
	}

	int A_Star::get_h_value(Position pos) const
	{
		//����M���I�Z��
		int *endXY = map_to_array(_ex, _ey);
		int endX = endXY[0];
		int endY = endXY[1];
		return abs(pos._x - endX) + abs(pos._y - endY);
	}

	int A_Star::get_g_value(Position pos) const
	{
		return ((_rects[pos._x][pos._y])._parent->_GValue) + 1;
	}

	bool A_Star::IsReachable(Position pos) const
	{
		if ((pos._x >= 0) && (pos._x < _side) && (pos._y >= 0) && (pos._y < _side))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void A_Star::getResult()
	{
		int *endXY = map_to_array(_ex, _ey);
		int endX = endXY[0];
		int endY = endXY[1];
		_closeList.clear();
		_openList.clear();
		Rect* rect = &(_rects[endX][endY]);
		while (rect != NULL)
		{
			_result.push_back(rect->_position);
			rect = rect->_parent;
		}
	}

	bool A_Star::testRoad(Position pos, Position current)
	{
		int *endXY = map_to_array(_ex, _ey);
		int endX = endXY[0];
		int endY = endXY[1];
		//�ˬd�O�_�barray�̭�
		if (IsReachable(pos))
		{
			//�ˬd�O�_�����I
			if ((pos._x == endX) && (pos._y == endY))
			{
				_rects[pos._x][pos._y]._parent = &(_rects[current._x][current._y]);
				return true;
			}
			//�P�_�a�ϯण�ਫ
			if (_map[pos._x][pos._y] != -1)
			{
				//�P�_�O�_�X�{�bcloseList
				if (_closeList.end() == std::find(_closeList.begin(), _closeList.end(), pos))
				{	
					//�p�Gpos���bopenlist�h�[�J�L
					if (_openList.end() == std::find(_openList.begin(), _openList.end(), pos))
					{
						_openList.push_back(pos);
						(_rects[pos._x][pos._y])._parent = &_rects[current._x][current._y];
						(_rects[pos._x][pos._y])._GValue = get_g_value(pos);
						(_rects[pos._x][pos._y])._HValue = get_h_value(pos);
					}
					else
					{
						//�ˬd�s���u�O�_���n
						if ((_rects[current._x][current._y]._GValue + 1) < _rects[pos._x][pos._y]._GValue)
						{
							_rects[pos._x][pos._y]._parent = &_rects[current._x][current._y];
							_rects[pos._x][pos._y]._GValue = get_g_value(pos);
						}
					}
				}
			}
		}
		return false;
	}

	bool A_Star::findRoad()
	{
		//�ˬdopenlist�O�_����
		if (_openList.empty())
		{
			//�p�G�ŤF�h�פ��ˬd
			return false;
		}
		int FValue = 0;
		int min_FValue = -1;
		std::list<Position>::iterator it, save;
		for (it = _openList.begin(); it != _openList.end(); it++)
		{
			//�p��FValue
			FValue = _rects[(*it)._x][(*it)._y]._GValue + _rects[(*it)._x][(*it)._y]._HValue;
			if ((min_FValue == -1) || (min_FValue >= FValue))
			{
				min_FValue = FValue;
				save = it;
			}
		}
		//��FValue�̤p����m�qopenlist�����A�[�JcloseList
		Position currentPos = *save;
		_closeList.push_back(currentPos);
		_openList.erase(save);

		//�ˬd�W�U���k
		Position up;
		up._x = currentPos._x;
		up._y = currentPos._y + 1;
		Position down;
		down._x = currentPos._x;
		down._y = currentPos._y - 1;
		Position left;
		left._x = currentPos._x - 1;
		left._y = currentPos._y;
		Position right;
		right._x = currentPos._x + 1;
		right._y = currentPos._y;

	
		if (testRoad(up, currentPos))
		{
			return true;
		}
		if (testRoad(down, currentPos))
		{
			return true;
		}
		if (testRoad(left, currentPos))
		{
			return true;
		}
		if (testRoad(right, currentPos))
		{
			return true;
		}
		return findRoad();
	}

	int A_Star::getX()
	{
		if (_result.size() > 1)
		{
			std::list<Position>::iterator it = _result.end();
			it--;
			int tempX = (*it)._x;
			it--;
			int ansX = (*it)._x;
			return ansX - tempX;
		}
	}

	int A_Star::getY()
	{
		if (_result.size() > 1) 
		{
			std::list<Position>::iterator it = _result.end();
			it--;
			int tempY = (*it)._y;
			it--;
			int ansY = (*it)._y;
			return ansY - tempY;
		}
	}

	bool A_Star::getIsDone()
	{
		return _isDone;
	}
}