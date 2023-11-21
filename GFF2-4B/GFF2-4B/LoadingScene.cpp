#include "LoadingScene.h"
#include "PadInput.h"
#include "GameClear.h"
#include "GameMain.h"

Loading::Loading()
{
	try
	{
		loading_image = LoadGraph("resource/font/LoadingFont.png");
		if(loading_image == -1)
		{
			throw "resource/images/LoadImage.png";
		}
	}
	catch (int& err)
	{
		printf("エラーコード%d\n", err);
	}
	loading_time = 0;
	loading_mark_time = 0;
}
Loading::~Loading()
{

}
AbstractScene* Loading::Update()
{
	while (loading_time < 100)
	{
		loading_time += 1;
		loading_mark_time = (loading_time / 30);
		return this;
	}
	return new GameClear;
}
void Loading::Draw()const
{
	DrawGraph(950, 620, loading_image, FALSE);
	DrawCircle(1170 + (loading_mark_time * 25), 655, 7, 0xffffff, TRUE);
}