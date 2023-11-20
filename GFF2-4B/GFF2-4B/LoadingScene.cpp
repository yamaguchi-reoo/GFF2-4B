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
}
Loading::~Loading()
{

}
AbstractScene* Loading::Update()
{
	while (loading_time < 100)
	{
		loading_time += 1;
		return this;
	}
	return new GameClear;
}
void Loading::Draw()const
{
	DrawGraph(950, 620, loading_image, FALSE);
	DrawCircle(1170, 655, 5, 0xffffff, TRUE);
	DrawCircle(1195, 655, 5, 0xffffff, TRUE);
	DrawCircle(1220, 655, 5, 0xffffff, TRUE);
}