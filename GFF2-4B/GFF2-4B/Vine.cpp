#include "Vine.h"

//コンストラクタ
Vine::Vine(int x)
{
	location.x = x;
	location.y = 0;
	erea.height = 650;
	erea.width = 120;
	vine_flg = false;
	img = LoadGraph("resource/images/KUKYOTR.png");
}

//デストラクタ
Vine::~Vine()
{
}

//更新処理
void Vine::Update()
{
	////蔓のアニメーション
	//if (vine_flg == false)
	//{//はじめ
	//	VineAnimStart();
	//}
	//else
	//{//おわり
	//	VineAnimEnd();
	//}

}

//描画処理
void Vine::Draw() const
{
	//蔓
	DrawGraph(local_location.x, local_location.y, img, TRUE);
}

//蔓のアニメーション(下から上に)
void Vine::VineAnimStart()
{
	//蔓を下からはやす
	if (location.y > 70)
	{
		location.y -= 35;
	}
	else
	{
		vine_flg = true;
	}
}

//蔓のアニメーション(上から下に)
void Vine::VineAnimEnd()
{
	if(location.y > 1290)
	{
		location.y += 35;
	}
	else
	{
		vine_flg = false;
	}
}