#pragma once
#include "common.h"
#include "PadInput.h"

//3色ゲージ
struct ColerBase
{
	int x;	  //色つける四角の右下座標(x)
	int y;	  //色つける四角の右下座標(y)
	float h;  //色つける四角の高さ
	float volume; //色の溜まり具合
	float ratio;  //ゲージの溜まり具合
	int maxFlg;   //(0:ゲージMAX未満 1:ゲージMAX)
};

class PowerGauge
{
private:
	ColerBase magenta; //マゼンタ
	ColerBase cyan;    //シアン
	ColerBase yellow;  //イエロー

	int image[3];  //画像用変数

public: 
	PowerGauge();  //コンストラクタ
	~PowerGauge(); //デストラクタ

	void Update();
	void Draw()const;

	float VolumeCalculate(float volume, float h); //ゲージの溜まり具合を計算
};
