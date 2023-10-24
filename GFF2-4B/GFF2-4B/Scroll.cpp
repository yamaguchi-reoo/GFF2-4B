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
	if (player.x <= LEFT_END && scroll_x >= 0.01)
	{
		scroll_x += 6.0;
		ActionRangeBorder(player);
	}
	//右スクロール
	if (player.x >= RIGHT_END)
	{
		scroll_x -= 6.0;
		ActionRangeBorder(player);
	}
	PlayerScroll(player);
}
void SceneScroll::Draw()
{
	DrawGraph((int)scroll_x, 0, stage_image, FALSE);
}
ScrollData SceneScroll::PlayerScroll(Location player)
{
	ScrollData scroll_data{};
	if (player.x <= LEFT_END + 1)
	{
		//スクロール処理発生X座標の左端にプレイヤーが到着した場合、座標を加速度分後ろにする
		scroll_data.direction = true;
		scroll_data.move += 0.01;
	}
	if (player.x >= RIGHT_END + 1)
	{
		//スクロール処理発生X座標の右端にプレイヤーが到着した場合、座標を加速度分後ろにする
		scroll_data.direction = false;
		scroll_data.move += 0.01;
	}
	return scroll_data;
}
int SceneScroll::ActionRangeBorder(Location player)
{
	if (player.x <= LEFT_END || player.x >= RIGHT_END)
	{
		return true;
	}
	else
	{
		return false;
	}
}