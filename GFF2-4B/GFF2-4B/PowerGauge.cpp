#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 387.0f;
	magenta.y = 68.0f;
	magenta.volume = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 419.0f;
	cyan.y = 114.0f;
	cyan.volume = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 360.0f;
	yellow.y = 114.0f;
	yellow.volume = 0.0f;
	yellow.maxFlg = 0;

	image[0] = LoadGraph("resource/images/ã≠âªÉQÅ[ÉW1.png");
	image[1] = LoadGraph("resource/images/ã≠âªÉQÅ[ÉW2.png");
	image[2] = LoadGraph("resource/images/ã≠âªÉQÅ[ÉW3.png");
}

PowerGauge::~PowerGauge()
{
}

void PowerGauge::Update()
{
}

void PowerGauge::Draw() const
{
	
	DrawGraph(285, 10, image[2], TRUE);
	DrawBox((int)magenta.x - 50, (int)magenta.y - 45, (int)magenta.x, (int)magenta.y, 0xe4007f, TRUE);
	DrawBox((int)yellow.x - 50, (int)yellow.y - 45, (int)yellow.x, (int)yellow.y, 0xffff00, TRUE);
	DrawBox((int)cyan.x - 50, (int)cyan.y - 45, (int)cyan.x, (int)cyan.y, 0x00FFFF, TRUE);
	DrawGraph(300, 17, image[1], TRUE);
	DrawGraph(285, 10, image[0], TRUE);
}