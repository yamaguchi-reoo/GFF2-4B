#include "Scroll.h"

SceneScroll::SceneScroll()
{
	stage_image = LoadGraph("resource/images/SampleStage2.png");
	try 
	{
		if (stage_image == -1)
		{
			throw"resource/images/SampleStage2.png";
		}
	}
	catch (int& err)
	{
		printf("エラーコード%d\n", err);
	}

	scroll_x = 0.0;		//背景画像の左上頂点部のX座標
	scroll_y = 0.0;		//背景画像の左上頂点部のY座標
}
SceneScroll::~SceneScroll()
{
}
void SceneScroll::Update(Location player, float acs_l, float acs_r)
{
	//左スクロール
	if (player.x >= LEFT_END)
	{
		//スクロール発生座標の左端にプレイヤーが到着した場合、座標を加速度分後ろにする
		player.x = LEFT_END - acs_l;

		scroll_x -= acs_l;
	}
	//右スクロール
	if (player.x <= RIGHT_END)
	{
		//スクロール処理発生X座標の左端にプレイヤーが到着した場合、座標を加速度分後ろにする
		player.x = RIGHT_END + acs_r;

		scroll_x += acs_r;
	}
}
void SceneScroll::Draw()
{
	DrawGraph((int)scroll_x, 0, stage_image, FALSE);
}