#pragma once
#include "common.h"
#include "PadInput.h"

//3色ゲージ
struct ColerBase
{
	float x;	  //色つける四角の左上座標(x)
	float y;	  //色つける四角の左上座標(y)
	float volume; //ゲージの溜まり具合
	int maxFlg;   //(0:ゲージMAX未満 1:ゲージMAX)
};

class KYOUKA
{
private:
	ColerBase magenta; //マゼンタ
	ColerBase cyan;    //シアン
	ColerBase yellow;  //イエロー

	int image[3];  //画像用変数
};
