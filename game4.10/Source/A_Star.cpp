#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "A_Star.h"

namespace game_framework {

	A_Star::A_Star(int *mapInfo, int width, int height, int start, int end)
	{
		Width = width;
		Height = height;
		Start = start;
		End = end;

		//��G???�O�s��@???���h�A�K�_�H����?�z 
		map = new int[Width * Height];
		for (int i = 0; i < Width * Height; i++)
		{
			//map[i] = mapInfo[i / width][i % width]; 
			map[i] = mapInfo[i];
		}

		//??�C�@???����m�H�� 
		rect = new Rect[Width * Height];
		for (int i = 0; i < (Width * Height); i++)
		{
			rect[i].x = i % Width;
			rect[i].y = i / Width;
		}

		//��l�ư_? 
		rect[Start].g_value = 0;
		rect[Start].h_value = get_h_value(Start);
		rect[Start].pre = NULL;

		//��_?�[�Jopen_list�� 
		open_list.push_back(Start);
	}

	A_Star::~A_Star()
	{
		if (map != NULL)
		{
			delete[] map;
		}
		if (rect != NULL)
		{
			delete[] rect;
		}
	}

	int A_Star::get_g_value(int pos)
	{
		//�u��?���a���W�U���k�|?��V�樫�A�ҥH?����g�ȥu�ݭn�b��??��g�ȤW�[10 
		return (rect[pos].pre->g_value + 10);
	}

	int A_Star::get_h_value(int pos)
	{
		//��^??��??��Manhattan�Z�áA���H10�O?�F��K?����?�� 
		return (10 * (abs(End / Width - pos / Width) + abs(End % Width - pos % Width)));
	}

	void A_Star::getResultPath()
	{
		Rect *temp = &rect[End];
		while (temp != NULL)
		{
			result.push_back(*temp);
			temp = temp->pre;
		}
		return;
	}

	bool A_Star::isReachable(int pos)
	{
		if ((pos / Width < Height) && (pos / Width >= 0) &&
			(pos % Width < Width) && (pos % Width >= 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//�p�Gpos���i?�Ϊ̥��bclose_list��?��?���A�_?�A?��p�U�ާ@ 
	//�p�Gpos���bopen_list��?�[�Jopen_list�A�}��?�e���?�m?������? 
	//�p�Gpos�bopen_list��??�dg���j�p�A�p�G��p?�⥦����??�m??�e��� 
	bool A_Star::testRoad(int pos, int cur)
	{
		if (isReachable(pos))
		{
			if (pos == End)
			{
				rect[pos].pre = &rect[cur];
				return true;
			}
			if (map[pos] != 1) //1�N���?���A0?�i�q�� 
			{
				if (close_list.end() == find(close_list.begin(), close_list.end(), pos))
				{
					std::list<int>::iterator iter = find(open_list.begin(), open_list.end(), pos);
					if (iter == open_list.end())
					{
						open_list.push_back(pos);
						rect[pos].pre = &rect[cur];
						rect[pos].h_value = get_h_value(pos);
						rect[pos].g_value = get_g_value(pos);
					}
					else
					{
						if ((rect[cur].g_value + 10) < rect[pos].g_value)
						{
							rect[pos].pre = &rect[cur];
							rect[pos].g_value = get_g_value(pos);
						}
					}
				}
			}
		}
		return false;
	}

	bool A_Star::Find()
	{
		//�M?open_list�A�d��F�ȳ̤p��??�@??�e�n?�z��?? 
		//�p�Gopen_list?�šA?���?����?��� 
		if (open_list.empty())
		{
			return false;
		}

		int f_value = 0;
		int min_f_value = -1;
		std::list<int>::iterator iter, save;
		for (iter = open_list.begin(); iter != open_list.end(); iter++)
		{
			f_value = rect[*iter].g_value + rect[*iter].h_value;
			//?����min==f�]?���s?��?�ȡA?�Popen_list���a�Z�������㦳�󰪪�ɬ��? 
			//��????�n 
			if ((min_f_value == -1) || (min_f_value >= f_value))
			{
				min_f_value = f_value;
				save = iter;
			}
		}

		//��??F�ȳ̤p��??����close_list�� 
		int cur = *save;
		close_list.push_back(cur);
		open_list.erase(save);


		//??�e��檺�W�U���k��?���?��?? 
		//�p�G???�J�Fopen_list??�� 
		int up = cur - Width;
		int down = cur + Width;
		int left = cur - 1;
		int right = cur + 1;
		if (true == testRoad(up, cur))
		{
			return true;
		}
		if (true == testRoad(down, cur))
		{
			return true;
		}
		if (true == testRoad(left, cur))
		{
			return true;
		}
		if (true == testRoad(right, cur))
		{
			return true;
		}

		return Find();
	}

}