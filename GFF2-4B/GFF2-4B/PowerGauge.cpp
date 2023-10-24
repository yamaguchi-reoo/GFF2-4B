#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 0.0f;
	magenta.y = 0.0f;
	magenta.volume = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 0.0f;
	cyan.y = 0.0f;
	cyan.volume = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 0.0f;
	yellow.y = 0.0f;
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
	DrawGraph(285, 10, image[0], TRUE);
	DrawBox(347, 18, 392, 65, 0xe4007f, TRUE);
	DrawGraph(300, 3, image[1], TRUE);
	//DrawGraph(300, 0, image[2], TRUE);
}