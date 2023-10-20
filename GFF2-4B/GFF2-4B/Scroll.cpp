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
		scroll_x -= acs_l;

		//左端到着処理
		player.x = LEFT_END - 1;
	}
	//右スクロール
	if (player.x <= RIGHT_END)
	{
		scroll_x += acs_r;

		//右端到着処理
		player.x = RIGHT_END + 1;
	}
}
void SceneScroll::Draw()
{
	DrawGraph(0, 0, stage_image, FALSE);
}