#include "Koban.h"

//コンストラクタ
Koban::Koban(/*float pos_x, float pos_y*/)
{
	location.x = 0;
	location.y = 0;
	erea.height = 40;
	erea.width = 40;

	koban_img[0] = LoadGraph("resource/images/koban.png");
	koban_img[1] = LoadGraph("resource/images/UI/KobanScore.png");

	spawn_flg = false;
	score_flg = false;
	score_time = 0;
	score_x = 0.0f;
	score_y = 0.0f;
}

//デストラクタ
Koban::~Koban()
{
}

//更新処理
void Koban::Update()
{
	if (score_flg == true)
	{
		score_time++;

		if (score_time > 60)
		{
			score_flg = false;
			score_time = 0;
		}
	}
}

//描画処理
void Koban::Draw() const
{
	if (spawn_flg == true) 
	{
		DrawGraphF(local_location.x, local_location.y - 10, koban_img[0], TRUE);
	}
	
	if(score_flg == true)
	{
		DrawGraphF(score_x, score_y - 10, koban_img[1], TRUE);
	}
}

//表示位置を設定
void Koban::SetLocation(Location _location)
{
	location.x = _location.x;
	location.y = _location.y;
}

void Koban::SetScoreLocation()
{
	score_x = local_location.x;
	score_y = local_location.y;
}