#include "PowerGauge.h"
#include "PadInput.h"

PowerGauge::PowerGauge()
{
	magenta.x = 112.0f;
	magenta.y = 70.0f;
	magenta.h = 65.0f;
	magenta.volume = 0.0f;
	magenta.remainder = 0;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 152.0f;
	cyan.y = 130.0f;
	cyan.h = 115.0f;
	cyan.volume = 0.0f;
	cyan.remainder = 0;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 103.0f;
	yellow.y = 150.0f;
	yellow.h = 84.0f;
	yellow.volume = 0.0f;
	yellow.remainder = 0;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	black.x = 147.0f;
	black.y = 138.0f;
	black.h = 131.0f;
	black.volume = 0.0f;
	black.remainder = 0;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	powerFlg = 0;

	image[0] = LoadGraph("resource/images/koban.png");
	image[1] = LoadGraph("resource/images/black.png");
	image[2] = LoadGraph("resource/images/magatama_max.png");
	
	MaskHandle[0] = LoadMask("resource/images/Magatama_mask1.png");
	MaskHandle[1] = LoadMask("resource/images/black_mask.png");

	num = 0.0f;
	rotaFlg = 0;
	i = 0;
	j = 0;

}

PowerGauge::~PowerGauge()
{
	// マスクデータを削除
	DeleteMask(MaskHandle[0]);
	DeleteMask(MaskHandle[1]);
}

void PowerGauge::Update()
{
	if ((black.maxFlg == 0) && (rotaFlg == 0))
	{
		//デバック用(LBをおしたら強化ゲージが溜まる)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) == true))
		{
			if (magenta.maxFlg == 0)
			{
				magenta.volume += 40.0f;
			}
			if (cyan.maxFlg == 0)
			{
				cyan.volume += 40.0f;
			}
			if (yellow.maxFlg == 0)
			{
				yellow.volume += 40.0f;
			}
		}

		CheckVolumeMax();

		VolumeSet();

		//デバック用(RBをおしたら強化ゲージがMAXになる)
		if ((black.maxFlg == 0) && (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == true))
		{
			rotaFlg = 1;
		}

	}
	else if(rotaFlg == 1)
	{
		RotaGauge();
	}
	else if(black.maxFlg == 1)
	{
		//強化ゲージがMAXかつ、Xボタンが押されたら強化状態フラグを1に
		if ((black.maxFlg == 1) && (PadInput::OnButton(XINPUT_BUTTON_Y) == true))
		{
			powerFlg = 1;
		}
	}

	//強化状態フラグが1だったら強化ゲージを減らす
	if (powerFlg == 1)
	{
		BlackGauge();
		VolumeSet();
	}
}

void PowerGauge::Draw() const
{
#ifdef _DEBUG

	//デバック表示
	/*DrawFormatString(300, 10, 0xffffff, "%d", magenta.remainder);
	DrawFormatString(300, 30, 0xffffff, "%f", magenta.volume);
	DrawFormatString(300, 50, 0xffffff, "%d", cyan.remainder);
	DrawFormatString(300, 70, 0xffffff, "%f", cyan.volume);
	DrawFormatString(300, 90, 0xffffff, "%d", yellow.remainder);
	DrawFormatString(300, 100, 0xffffff, "%f", yellow.volume);*/


#endif // _DEBUG
	
	//マスク画面を作成
	CreateMaskScreen();

	if ((black.maxFlg == 0) && (rotaFlg == 0))
	{
		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, MaskHandle[0], DX_MASKTRANS_NONE);

		//勾玉の背景を白に
		DrawBox(5, 3, 155, 153, 0xffffff, TRUE);

		//強化ゲージが0%以上の時に表示
		if (yellow.volume != 0.0f)
		{
			DrawBoxAA(yellow.x - 92, yellow.y - yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		}
		if (cyan.volume != 0.0f)
		{
			DrawBoxAA(cyan.x - 65, cyan.y - cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
		}
		if (magenta.volume != 0.0f)
		{
			DrawBoxAA(magenta.x - 107, magenta.y - magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		}
		
		/**図形描画の重なりを隠す(ここから)**/
		DrawBox(87, 70, 112, 130, 0xffffff, TRUE);

		if (cyan.volume >= 2.0f)
		{
			DrawBoxAA(87, 130 - ((cyan.volume * 2.0f) / 100.0f * 57.5f), 112.0f, 130.0f, 0x00ffff, TRUE);
		}

		if (magenta.volume >= 2.0f)
		{
			DrawBox(15, 66, 70, 70, 0xffffff, TRUE);

			if (yellow.volume > 95.0f)
			{
				DrawBoxAA(15.0f, 70.0f - (yellow.volume / 100.0f * 4), 70.0f, 70.0f, 0xffff00, TRUE);
		    }
		}

		DrawBox(80, 10, 112, 70, 0xffffff, TRUE);

		if (magenta.volume >= 14.0f)
		{
			DrawBoxAA(80.0f, 70.0f - ((magenta.volume * 1.1f) / 100.0f * 59.5f ), 112.0f, 70.0f, 0xe4007f, TRUE);
		}
		/**図形描画の重なりを隠す(ここまで)**/
	}
	else if ((rotaFlg == 1) && (black.maxFlg == 0))
	{
		//強化ゲージを回転描画
		DrawRotaGraph(80, 80, 1.0f, PI / 180 * num, image[2], TRUE, FALSE);
	}
	else if ((black.maxFlg == 1) && (powerFlg == 0))
	{//強化ゲージがMAX(黒)のとき

		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, MaskHandle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 155, 138, 0xffffff, TRUE);
		
		DrawBoxAA(black.x - 135.0f, black.y - 131.0f, black.x, black.y, 0x000000, TRUE);
	}
	else if(powerFlg == 1)
	{//強化ゲージがMAXでXボタンが押されたとき

		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, MaskHandle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 150, 138, 0xffffff, TRUE);

		DrawBoxAA(black.x - 135.0f, black.y - black.ratio, black.x, black.y, 0x000000, TRUE);
	}

	// マスク画面を削除
	DeleteMaskScreen();
}

//ゲージの溜まり具合を計算
float PowerGauge::CalculateVolume(float volume, float h)
{
	float i = 0.0f;

	i = volume / 100.0f * h;

	return i;
}

//ゲージの溜まり具合を計算した値を代入
void PowerGauge::VolumeSet()
{
	magenta.ratio = CalculateVolume(magenta.volume, magenta.h);
	yellow.ratio = CalculateVolume(yellow.volume, yellow.h);
	cyan.ratio = CalculateVolume(cyan.volume, cyan.h);
	black.ratio = CalculateVolume(black.volume, black.h);
}

//時間経過で黒のゲージを減らす
void PowerGauge::BlackGauge()
{
	float i = 0;

	if (black.volume > 0.0f)
	{
		//強化状態で、ゲージが0%になるまで徐々に減らす
		i = black.volume;
		black.volume = i - 0.17f;
	}
	else
	{
		//強化状態が終わったら、強化状態を解除して強化ゲージを初期状態に戻す
		powerFlg = 2;
		InitGauge();
	}
}

//強化状態かどうか渡す
int PowerGauge::PowerGaugeState()
{
	if (powerFlg == 1)
	{
		//強化状態
		return 1;
	}
	else if (powerFlg == 2)
	{
		//強化解除
		return 2;
	}

	return 0;
}

//強化状態かどうかを保存する変数の値を引数の値に変更
void PowerGauge::SetPowerFlg(int i)
{
	powerFlg = i;
}

//敵が落とした色、量をゲージに加算
void PowerGauge::SetVolume(ColorDate color)
{
	//マゼンタ
	if (magenta.maxFlg == 0)
	{
		magenta.volume += color.magenta;
	}
	else
	{
		magenta.remainder += (int)color.magenta;
	}

	//シアン
	if (cyan.maxFlg == 0)
	{
		cyan.volume += color.syan;
	}
	else
	{
		cyan.remainder += (int)color.syan;
	}
	
	//イエロー
	if (yellow.maxFlg == 0)
	{
		yellow.volume += color.yellow;
	}
	else
	{
		yellow.remainder += (int)color.yellow;
	}
}

//CMYKのゲージがMAXかチェックする
void PowerGauge::CheckVolumeMax()
{
	//マゼンタを集めた量が100%以上だったらマゼンタのMAXフラグを1に
	if (magenta.volume >= 100.0f)
	{
		magenta.remainder += (int)magenta.volume - 100;
		magenta.volume = 100.0f;
		magenta.maxFlg = 1;
	}

	//イエローを集めた量が100%以上だったらイエローのMAXフラグを1に
	if (yellow.volume >= 100.0f)
	{
		yellow.remainder += (int)yellow.volume - 100;
		yellow.volume = 100.0f;
		yellow.maxFlg = 1;
	}

	//シアンを集めた量が100%以上だったらシアンのMAXフラグを1に
	if (cyan.volume >= 100.0f)
	{
		cyan.remainder += (int)cyan.volume - 100;
		cyan.volume = 100.0f;
		cyan.maxFlg = 1;
	}

	//CMYが全て100%以上だったら画像回転アニメーションフラグを1に
	if ((magenta.maxFlg == 1) && (yellow.maxFlg == 1) && (cyan.maxFlg == 1))
	{
		rotaFlg = 1;
	}
}

//強化ゲージの回転処理
void PowerGauge::RotaGauge()
{
	num += 2.5f * i++;

	if (num >= 360.0f)
	{
		//3回回転したら強化ゲージを黒(MAX)に
		if (j >= 6)
		{
			black.volume = 100.0f;
			black.maxFlg = 1;
			rotaFlg = 0;
		}

		j++;
		num = 0.0f;
	}
}

//強化状態が終わった後の初期化処理
void PowerGauge::InitGauge()
{
	black.volume = 0.0f;
	magenta.volume = 0.0f;
	yellow.volume = 0.0f;
	cyan.volume = 0.0f;
	black.maxFlg = 0;
	magenta.maxFlg = 0;
	cyan.maxFlg = 0;
	yellow.maxFlg = 0;
	num = 0.0f;
	i = 0;
	j = 0;
}