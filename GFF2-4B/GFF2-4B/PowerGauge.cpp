#include "PowerGauge.h"
#include "PadInput.h"
#include "GameMain.h"

//コンストラクタ
PowerGauge::PowerGauge()
{
	location.x = 5;
	location.y = 3;
	erea.height = 140;
	erea.width = 150;

	magenta.x = 112.0f;
	magenta.y = 70.0f;
	magenta.h = 65.0f;
	magenta.volume = 0.0f;
	magenta.ratio = 0.0f;
	magenta.maxFlg = 0;

	cyan.x = 152.0f;
	cyan.y = 130.0f;
	cyan.h = 115.0f;
	cyan.volume = 0.0f;
	cyan.ratio = 0.0f;
	cyan.maxFlg = 0;

	yellow.x = 103.0f;
	yellow.y = 150.0f;
	yellow.h = 84.0f;
	yellow.volume = 0.0f;
	yellow.ratio = 0.0f;
	yellow.maxFlg = 0;

	black.x = 147.0f;
	black.y = 138.0f;
	black.h = 131.0f;
	black.volume = 0.0f;
	black.ratio = 0.0f;
	black.maxFlg = 0;

	power_flg = 0;

	image[0] = LoadGraph("resource/images/koban.png");
	image[1] = LoadGraph("resource/images/black.png");
	image[2] = LoadGraph("resource/images/magatama_max.png");

	mask_handle[0] = LoadMask("resource/images/Magatama_mask1.png");
	mask_handle[1] = LoadMask("resource/images/black_mask.png");

	num = 0.0f;
	rota_flg = 0;
	i = 0;
	j = 0;

	remainder = 0;
}

//デストラクタ
PowerGauge::~PowerGauge()
{
	// マスクデータを削除
	DeleteMask(mask_handle[0]);
	DeleteMask(mask_handle[1]);
}

//更新処理
void PowerGauge::Update(GameMain* main)
{
	if ((black.maxFlg == 0) && (rota_flg == 0))
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
			rota_flg = 1;
		}

	}
	else if(rota_flg == 1)
	{
		RotaGauge();
	}
	else if(black.maxFlg == 1)
	{
		//強化ゲージがMAXかつ、Xボタンが押されたら強化状態フラグを1に
		if ((black.maxFlg == 1) && (PadInput::OnButton(XINPUT_BUTTON_Y) == true))
		{
			power_flg = 1;
		}
	}

	//強化状態フラグが1だったら強化ゲージを減らす
	if (power_flg == 1)
	{
		BlackGauge();
		VolumeSet();
	}
}

//描画処理
void PowerGauge::Draw() const
{
#ifdef _DEBUG

	//デバック表示
	//DrawFormatString(400, 10, 0xffffff, "%d", remainder);

#endif // _DEBUG
	
	//マスク画面を作成
	CreateMaskScreen();

	if ((black.maxFlg == 0) && (rota_flg == 0))
	{
		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, mask_handle[0], DX_MASKTRANS_NONE);

		//勾玉の背景を白に
		DrawBox(5, 3, 155, 153, 0x7d7d7d, TRUE);

		//強化ゲージが0%以上の時に表示
		
		
		//マゼンタ
		DrawBox(80, 10, 112, 70, 0x7d7d7d, TRUE);
		DrawBoxAA(magenta.x - 107, magenta.y - magenta.ratio, magenta.x, magenta.y, 0xe4007f, TRUE);
		
		
		//イエロー
		DrawBox(15, 66, 70, 70, 0x7d7d7d, TRUE);
		DrawBoxAA(yellow.x - 92, yellow.y - yellow.ratio, yellow.x, yellow.y, 0xffff00, TRUE);
		
		
		//シアン
		DrawBox(87, 70, 112, 130, 0x7d7d7d, TRUE);
		DrawBoxAA(cyan.x - 65, cyan.y - cyan.ratio, cyan.x, cyan.y, 0x00ffff, TRUE);
	
		
		/**図形描画の重なりを隠す(ここから)**/
		DrawBox(87, 70, 112, 130, 0x7d7d7d, TRUE);

		if (cyan.volume >= 2.0f)
		{
			DrawBoxAA(87, 130 - ((cyan.volume * 2.0f) / 100.0f * 57.5f), 112.0f, 130.0f, 0x00ffff, TRUE);
		}

		if (magenta.volume >= 2.0f)
		{

			if (yellow.volume > 95.0f)
			{
				DrawBoxAA(15.0f, 70.0f - (yellow.volume / 100.0f * 4), 70.0f, 70.0f, 0xffff00, TRUE);
		    }
		}

		DrawBox(80, 10, 112, 70, 0x7d7d7d, TRUE);

		if (magenta.volume >= 14.0f)
		{
			DrawBoxAA(80.0f, 70.0f - ((magenta.volume * 1.1f) / 100.0f * 59.5f ), 112.0f, 70.0f, 0xe4007f, TRUE);
		}
		/**図形描画の重なりを隠す(ここまで)**/
	}
	else if ((rota_flg == 1) && (black.maxFlg == 0))
	{
		//強化ゲージを回転描画
		DrawRotaGraph(80, 80, 1.0f, PI / 180 * num, image[2], TRUE, FALSE);
	}
	else if ((black.maxFlg == 1) && (power_flg == 0))
	{//強化ゲージがMAX(黒)のとき

		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, mask_handle[1], DX_MASKTRANS_NONE);

		DrawBox(5, 3, 155, 138, 0xffffff, TRUE);
		
		DrawBoxAA(black.x - 135.0f, black.y - 131.0f, black.x, black.y, 0x000000, TRUE);
	}
	else if(power_flg == 1)
	{//強化ゲージがMAXでXボタンが押されたとき

		//ロードしたマスクデータを画面の左上に描画
		DrawMask(5, 3, mask_handle[1], DX_MASKTRANS_NONE);

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
		power_flg = 2;
		InitGauge();
	}
}

//強化状態かどうか渡す
int PowerGauge::PowerGaugeState()
{
	if (power_flg == 1)
	{
		//強化状態
		return 1;
	}
	else if (power_flg == 2)
	{
		//強化解除
		return 2;
	}

	return 0;
}

//強化状態かどうかを保存する変数の値を引数の値に変更
void PowerGauge::SetPowerFlg(int i)
{
	power_flg = i;
}

//敵が落とした色、量をゲージに加算
void PowerGauge::SetVolume(ColorDate color)
{
	//マゼンタ
	if (magenta.maxFlg == 0)
	{
		magenta.volume += color.magenta;
	}

	//シアン
	if (cyan.maxFlg == 0)
	{
		cyan.volume += color.syan;
	}
	
	//イエロー
	if (yellow.maxFlg == 0)
	{
		yellow.volume += color.yellow;
	}
}

//CMYKのゲージがMAXかチェックする
void PowerGauge::CheckVolumeMax()
{
	//マゼンタを集めた量が100%以上だったらマゼンタのMAXフラグを1に
	if (magenta.volume >= 100.0f)
	{
		remainder += (int)magenta.volume - 100;
		magenta.volume = 100.0f;
		magenta.maxFlg = 1;
	}

	//イエローを集めた量が100%以上だったらイエローのMAXフラグを1に
	if (yellow.volume >= 100.0f)
	{
		remainder += (int)yellow.volume - 100;
		yellow.volume = 100.0f;
		yellow.maxFlg = 1;
	}

	//シアンを集めた量が100%以上だったらシアンのMAXフラグを1に
	if (cyan.volume >= 100.0f)
	{
		remainder += (int)cyan.volume - 100;
		cyan.volume = 100.0f;
		cyan.maxFlg = 1;
	}

	//CMYが全て100%以上だったら画像回転アニメーションフラグを1に
	if ((magenta.maxFlg == 1) && (yellow.maxFlg == 1) && (cyan.maxFlg == 1))
	{
		rota_flg = 1;
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
			rota_flg = 0;
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

void PowerGauge::SetColorRem()
{
	remainder = 0;
}