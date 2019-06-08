//在"src/"放入map.h 輸入地圖x,y (argv[1], argv[2]) 轉換結果為 map_code
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <fstream>
#include "FireMap_Logic.c"

using namespace std;

int main(int argc, char const *argv[]) {

  const int x = atoi(argv[1]), y = atoi(argv[2]);   // x = 1600 , y = 1600
  const float mag = 0.1; //縮小倍率 0.1
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

  for (int i =  numOfRGB * 4 + (numOfRGB * x * 4); i < 3 * x * y; i = i + numOfRGB * 10)
  {
      if(!initial)
        ofs << ", ";

      initial = false;


    if(flag == x * mag)
    {
      i += numOfRGB*x*9;
      flag = 0;
      ofs<<"\n";
    }

    if(i >= 3*x*y)
      break;

    // if(gimp_image.pixel_data[i] == 255) //白色
    //   ofs << "0";
    // else if(gimp_image.pixel_data[i] == 150) //傳送門
    //     ofs << "1";
    // else if(gimp_image.pixel_data[i] == 100) //道具箱
    //     ofs << "2";
    // else if(gimp_image.pixel_data[i] == 200) //書
    //     ofs << "3";
    // else  //黑色
    //   ofs << "-1";

    // if(gimp_image.pixel_data[i] == 255) //白色
    //   ofs << "0";
    // else if (gimp_image.pixel_data[i] == 200)//傳送門(關卡)
    //   ofs << "2";
    // else if (gimp_image.pixel_data[i] == 100)// 道具1
    //   ofs << "3";
    // else if (gimp_image.pixel_data[i] == 70)// 道具2
    //   ofs << "4";
    // else if (gimp_image.pixel_data[i] == 30)// 道具3
    //   ofs << "5";
    // else if (gimp_image.pixel_data[i] == 150)//傳送門(家)
    //   ofs << "1";
    // else          //黑色
    //   ofs << "-1";

    if(gimp_image.pixel_data[i] == 255) //白色
      ofs << "0";
    else if (gimp_image.pixel_data[i] == 100)//傳送門(關卡)
      ofs << "1";
    else if (gimp_image.pixel_data[i] == 60)// 上方道具1
      ofs << "2";
    else if (gimp_image.pixel_data[i] == 120)// 道具2
      ofs << "3";
    else if (gimp_image.pixel_data[i] == 80)// 道具3
      ofs << "4";
    else if (gimp_image.pixel_data[i] == 220)// 中間道具1
      ofs << "5";
    else if (gimp_image.pixel_data[i] == 20)// 道具2
      ofs << "6";
    else if (gimp_image.pixel_data[i] == 40)// 道具3
      ofs << "7";
    else if (gimp_image.pixel_data[i] == 140)// 下方道具1
      ofs << "8";
    else if (gimp_image.pixel_data[i] == 160)// 道具2
      ofs << "9";
    else if (gimp_image.pixel_data[i] == 52)// 道具3
      ofs << "10";
  	else if (gimp_image.pixel_data[i] == 200)//掉落
  		ofs << "-2";
  	else if (gimp_image.pixel_data[i] == 240)//陷阱
  		ofs << "-3";
    else          //黑色
      ofs << "-1";

    flag++;
  }

  ofs << "};";

	return 0;
}
