#include "Scroll.h"

SceneScroll::SceneScroll() : state(ScrollState::INIT_POS_SCROLL)
{
	try
	{
		stage_image = LoadGraph("resource/images/SampleStage2.png");
		if (stage_image == -1)
		{
			throw "resource/images/SampleStage2.png";
		}
	}
	catch (int& err)
	{
		printf("エラーコード%d\n", err);
	}

	scroll_x = 0.0f;		//背景画像の左上頂点部のX座標
	scroll_y = 0.0f;		//背景画像の左上頂点部のY座標
}
SceneScroll::~SceneScroll()
{
}
void SceneScroll::Update(Location player, float acs_l, float acs_r)
{
	//左スクロール
	if ((player.x <= LEFT_END) && (state == ScrollState::MOVE_SCROLL))
	{
		scroll_x += 6.0f;
		ActionRangeBorder(player);
	}
	//右スクロール
	if (player.x >= RIGHT_END)
	{
		scroll_x -= 6.0f;
		ActionRangeBorder(player);
	}
	//スクロール状態の切り替え(スクロール状態をONにする)
	if (player.x >= LEFT_END)
	{
		state = ScrollState::MOVE_SCROLL;
	}
	//スクロール状態の切り替え(スクロール状態をOFFにする)
	/*if (scroll_x <= )
	{
		state = ScrollState::INIT_POS_SCROLL;
	}*/
}
void SceneScroll::Draw()
{
	DrawGraphF(scroll_x, 0.0f, stage_image, FALSE);
	DrawFormatString(800, 400, 0x00ff00, "%d", scroll_x);
}
ScrollData SceneScroll::PlayerScroll(Location player)
{
	ScrollData scroll_data{};
	//初期左スクロール
	if ((player.x <= SCREEN_LEFT_END + 1) && (state == ScrollState::INIT_POS_SCROLL))
	{
		scroll_data.direction = true;
		scroll_data.move += 0.01f;
	}
	if ((player.x <= LEFT_END + 1) && (state == ScrollState::MOVE_SCROLL))
	{
		//スクロール処理発生X座標の左端にプレイヤーが到着した場合、座標を加速度分後ろにする
		scroll_data.direction = true;
		scroll_data.move += 0.01f;
	}
	if (player.x >= RIGHT_END + 1)
	{
		//スクロール処理発生X座標の右端にプレイヤーが到着した場合、座標を加速度分後ろにする
		scroll_data.direction = false;
		scroll_data.move += 0.01f;
	}
	return scroll_data;
}
int SceneScroll::ActionRangeBorder(Location player)
{
	if ((player.x <= LEFT_END && state == ScrollState::MOVE_SCROLL) || ((player.x >= RIGHT_END))
		|| (player.x <= SCREEN_LEFT_END + 1) && (state == ScrollState::INIT_POS_SCROLL))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void SceneScroll::ChangeScrollMode()
{

}