#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <fstream>
#include "FireMap_Logic.c"

using namespace std;

int main(int argc, char const *argv[]) {

  const int x = atoi(argv[1]), y = atoi(argv[2]);   // x = 1600 , y = 1600
  const float mag = 1;
  const int numOfRGB = 3;
  fstream ofs;
  ofs.open("map_code.txt", ios::out);
  ofs << "const int map[";
  ofs << x * mag;
  ofs << "][";
  ofs << y * mag;
  ofs << "] = {";

  int flag = 0;
  bool initial = true;

  for (int i = 0 ; i < 3 * x * y; i = i + 1 * numOfRGB)
  {
      if(!initial)
        ofs << ", ";

      initial = false;

    if(flag == x)
    {
      flag = 0;
      ofs<<"\n             ";
    }

    if(i >= 3*x*y)
      break;


    if(gimp_image.pixel_data[i] == 0) //白色
      ofs << "-1";
    else
      ofs << "0";


    /*
    if(gimp_image.pixel_data[i] == 255) //白色
      ofs << "0";
    else if (gimp_image.pixel_data[i] == 200)//傳送門(關卡)
      ofs << "2";
    else if (gimp_image.pixel_data[i] == 100)// 道具1
      ofs << "3";
    else if (gimp_image.pixel_data[i] == 70)// 道具2
      ofs << "4";
    else if (gimp_image.pixel_data[i] == 30)// 道具3
      ofs << "5";
    else if (gimp_image.pixel_data[i] == 150)//傳送門(家)
      ofs << "1";
    else          //黑色
      ofs << "-1";
      */
    flag++;

  }


  ofs << "};";

	return 0;
}
