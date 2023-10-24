#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 109;
	magenta.y = 63;
	magenta.h = 45;
	magenta.volume = 50.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	yellow.x = 80;
	yellow.y = 110;
	yellow.h = 45;
	yellow.volume = 50.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	cyan.x = 140;
	cyan.y = 110;
	cyan.h = 45;
	cyan.volume = 50.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	image[0] = LoadGraph("resource/images/強化ゲージ1.png");
	image[1] = LoadGraph("resource/images/強化ゲージ2.png");
	image[2] = LoadGraph("resource/images/強化ゲージ3.png");
}

PowerGauge::~PowerGauge()
{
}

void PowerGauge::Update()
{
	//ゲージの溜まり具合を計算して代入
	magenta.ratio = VolumeCalculate(magenta.volume, magenta.h);
	yellow.ratio = VolumeCalculate(yellow.volume, yellow.h);
	cyan.ratio = VolumeCalculate(cyan.volume, cyan.h);

}

void PowerGauge::Draw() const
{
	DrawGraph(5, 5, image[2], TRUE);


	DrawBox(magenta.x - 50, magenta.y - (int)magenta.ratio - 2, magenta.x, magenta.y, 0xe4007f, TRUE);
	DrawBox(cyan.x - 50, cyan.y - (int)cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
	DrawBox(yellow.x - 50, yellow.y - (int)yellow.ratio, yellow.x,yellow.y, 0xffff00, TRUE);
	DrawGraph(20, 12, image[1], TRUE);


	DrawGraph(5, 5, image[0], TRUE);

	//デバック表示
	DrawFormatString(200,10,0x000000,"%f",magenta.volume / 100 * 45);
}

float PowerGauge::VolumeCalculate(float volume, float h)
{
	float i = 0.0f;

	i = volume / 100.0f * h;

	return i;
}