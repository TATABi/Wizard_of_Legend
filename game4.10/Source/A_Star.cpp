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

		//把二???保存到一???中去，便于信息的?理 
		map = new int[Width * Height];
		for (int i = 0; i < Width * Height; i++)
		{
			//map[i] = mapInfo[i / width][i % width]; 
			map[i] = mapInfo[i];
		}

		//??每一???的位置信息 
		rect = new Rect[Width * Height];
		for (int i = 0; i < (Width * Height); i++)
		{
			rect[i].x = i % Width;
			rect[i].y = i / Width;
		}

		//初始化起? 
		rect[Start].g_value = 0;
		rect[Start].h_value = get_h_value(Start);
		rect[Start].pre = NULL;

		//把起?加入open_list中 
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
		//只允?玩家往上下左右四?方向行走，所以?里的g值只需要在父??的g值上加10 
		return (rect[pos].pre->g_value + 10);
	}

	int A_Star::get_h_value(int pos)
	{
		//返回??到??的Manhattan距离，乘以10是?了方便?算机?算 
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

	//如果pos不可?或者它在close_list中?跳?它，否?，?行如下操作 
	//如果pos不在open_list中?加入open_list，并把?前方格?置?它的父? 
	//如果pos在open_list中??查g的大小，如果更小?把它的父??置??前方格 
	bool A_Star::testRoad(int pos, int cur)
	{
		if (isReachable(pos))
		{
			if (pos == End)
			{
				rect[pos].pre = &rect[cur];
				return true;
			}
			if (map[pos] != 1) //1代表障?物，0?可通行 
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
		//遍?open_list，查找F值最小的??作??前要?理的?? 
		//如果open_list?空，?表明?有解?方案 
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
			//?里的min==f也?重新?它?值，?致open_list中靠后的元素具有更高的优先? 
			//不????要 
			if ((min_f_value == -1) || (min_f_value >= f_value))
			{
				min_f_value = f_value;
				save = iter;
			}
		}

		//把??F值最小的??移到close_list中 
		int cur = *save;
		close_list.push_back(cur);
		open_list.erase(save);


		//??前方格的上下左右相?方格?行?? 
		//如果???入了open_list??束 
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