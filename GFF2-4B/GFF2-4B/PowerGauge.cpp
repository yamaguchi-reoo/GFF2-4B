#include "PowerGauge.h"

PowerGauge::PowerGauge()
{
	magenta.x = 109;
	magenta.y = 65;
	magenta.h = 45;
	magenta.volume = 0.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	yellow.x = 80;
	yellow.y = 110;
	yellow.h = 45;
	yellow.volume = 0.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	cyan.x = 140;
	cyan.y = 110;
	cyan.h = 45;
	cyan.volume = 0.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	black.x = 140;
	black.y = 130;
	black.h = 115;
	black.volume = 0.0f;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	powerFlg = 0;

	flamelate = 0;

	image[0] = LoadGraph("resource/images/強化ゲージ1.png");
	image[1] = LoadGraph("resource/images/強化ゲージ2.png");
	image[2] = LoadGraph("resource/images/強化ゲージ3.png");
}

PowerGauge::~PowerGauge()
{
}

void PowerGauge::Update()
{
	//デバック用
	flamelate++;

	if (flamelate == 1)
	{
		magenta.volume = 50.0f;
	}
	

	VolumeSet();

	if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == true))
	{
		black.volume = 100.0f;
		black.maxFlg = 1;
	}

	if ((black.maxFlg == 1) && (PadInput::OnButton(XINPUT_BUTTON_X) == true))
	{
		powerFlg = 1;
	}

	if (powerFlg == 1)
	{
		BlackGauge();
	}

	
}

void PowerGauge::Draw() const
{
	DrawGraph(5, 5, image[2], TRUE);

	if (black.maxFlg == 0)
	{
		if (magenta.volume != 0.0f) 
		{
			DrawBox(magenta.x - 50, magenta.y - (int)magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		}
		if (cyan.volume != 0.0f)
		{
			DrawBox(cyan.x - 50, cyan.y - (int)cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
		}
		if (yellow.volume != 0.0f)
		{
			DrawBox(yellow.x - 50, yellow.y - (int)yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		}

		DrawGraph(20, 12, image[1], TRUE);
	}
	else
	{
		DrawBox(black.x - 121, black.y - (int)black.ratio, black.x, black.y, 0x000000, TRUE);
	}
	
	
	DrawGraph(5, 5, image[0], TRUE);

}

//ゲージの溜まり具合を計算
float PowerGauge::VolumeCalculate(float volume, float h)
{
	float i = 0.0f;

	i = volume / 100.0f * h;

	return i;
}

//ゲージの溜まり具合を計算した値を代入
void PowerGauge::VolumeSet()
{
	magenta.ratio = VolumeCalculate(magenta.volume, magenta.h);
	yellow.ratio = VolumeCalculate(yellow.volume, yellow.h);
	cyan.ratio = VolumeCalculate(cyan.volume, cyan.h);
	black.ratio = VolumeCalculate(black.volume, black.h);
}

//時間経過で黒のゲージを減らす
void PowerGauge::BlackGauge()
{
	float i = 0;

	if (black.volume > 0.0f)
	{
		i = black.volume;
		black.volume = i - 0.17;
	}
	else
	{
		//強化状態が終わったら、強化ゲージを初期状態に戻す
		powerFlg = 2;
		black.maxFlg = 0;
		magenta.volume = 0.0f;
		yellow.volume = 0.0f;
		cyan.volume = 0.0f;
	}
}

//強化状態かどうか渡す
int PowerGauge::PowerGaugeState()
{
	if (powerFlg == 1)
	{
		return 1;
	}
	else if (powerFlg == 2)
	{
		return 2;
	}

	return 0;
}