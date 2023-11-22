#include "LockPlayer.h"
#include "DxLib.h"

//コンストラクタ
LockPlayer::LockPlayer()
{
	lock_flg = false;
	grass_lx = -650;
	grass_rx = 1290;
	grass_flg = false;
	enemy_cnt = 0;
	create_en = 0;
	attack_en = 0;
	img = LoadGraph("resource/images/kusa.png");
}

//デストラクタ
LockPlayer::~LockPlayer()
{
}

//更新処理
void LockPlayer::Update()
{
	//蔓のアニメーション後、草のアニメーション
	if (grass_flg == false)
	{
		GrassAnim();
	}
}

//描画処理
void LockPlayer::Draw() const
{
	if (lock_flg == true)
	{
		//草
		DrawGraph(grass_lx, -5, img, TRUE);
		DrawGraph(grass_rx, -5, img, TRUE);

	}
}

//草のアニメーション
void LockPlayer::GrassAnim()
{
	//草を横からはやす
	if (grass_lx < 0)
	{
		grass_lx += 35;
		grass_rx -= 35;
	}
	else
	{
		grass_flg = true;
	}
}