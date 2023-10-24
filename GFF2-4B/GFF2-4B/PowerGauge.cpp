#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 109.0f;
	magenta.y = 64.0f;
	magenta.volume = 0.0f;
	magenta.maxFlg = 0;

	yellow.x = 80.0f;
	yellow.y = 109.0f;
	yellow.volume = 0.0f;
	yellow.maxFlg = 0;

	cyan.x = 140.0f;
	cyan.y = 109.0f;
	cyan.volume = 0.0f;
	cyan.maxFlg = 0;

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
	DrawGraph(5, 5, image[2], TRUE);
	DrawBox((int)magenta.x - 50, (int)magenta.y - 45, (int)magenta.x, (int)magenta.y, 0xe4007f, TRUE);
	DrawBox((int)cyan.x - 50, (int)cyan.y - 45, (int)cyan.x, (int)cyan.y, 0x00ffff, TRUE);
	DrawBox((int)yellow.x - 50, (int)yellow.y - 45, (int)yellow.x, (int)yellow.y, 0xffff00, TRUE);
	DrawGraph(20, 12, image[1], TRUE);
	DrawGraph(5, 5, image[0], TRUE);
}