//在"src/"放入map.h 輸入地圖x,y (argv[1], argv[2]) 轉換結果為 map_code
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <fstream>
#include "Home.c"

using namespace std;

int main(int argc, char const *argv[]) {

  const int x = atoi(argv[1]), y = atoi(argv[2]);   // x = 1600 , y = 1600
  const float mag = 0.25; //縮小倍率 0.1
  const int numOfRGB = 3;

  fstream ofs;
  ofs.open("map_code.txt", ios::out);
  ofs << "int map[";
  ofs << x * mag;
  ofs << "][";
  ofs << y * mag;
  ofs << "] = {";

  int flag = 0;
  bool initial = true;

  for (int i = x * numOfRGB + (1 * numOfRGB); i < 3 * x * y; i = i + 4 * numOfRGB)
  {
      if(!initial)
        ofs << ", ";

      initial = false;

    if(flag == x * mag)
    {
      i += 3*x*numOfRGB;
      flag = 0;
      ofs<<"\n             ";
    }

    if(i >= 3*x*y)
      break;

    if(gimp_image.pixel_data[i] == 255) //白色
      ofs << "0";
    else  //黑色
      ofs << "-1";

    flag++;
  }

  ofs << "};";

	return 0;
}
