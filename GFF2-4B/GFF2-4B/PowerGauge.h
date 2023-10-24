#pragma once
#include "common.h"
#include "PadInput.h"

//ゲージ
struct GuegeBase
{
	int x;	  //色つける四角の右下座標(x)
	int y;	  //色つける四角の右下座標(y)
	float h;  //色つける四角の高さ
	float volume; //色の溜まり具合
	float ratio;  //ゲージの溜まり具合
	int maxFlg;   //CMYの場合(0:ゲージMAX未満 1:ゲージMAX),黒の場合(0:それ以外 1:ゲージが黒の状態)
};

class PowerGauge
{
private:
	GuegeBase magenta; //マゼンタ
	GuegeBase cyan;    //シアン
	GuegeBase yellow;  //イエロー
	GuegeBase black;   //黒
	

	int image[3];  //画像用変数

public: 
	PowerGauge();  //コンストラクタ
	~PowerGauge(); //デストラクタ

	void Update();
	void Draw()const;

	float VolumeCalculate(float volume, float h); //ゲージの溜まり具合を計算
};
