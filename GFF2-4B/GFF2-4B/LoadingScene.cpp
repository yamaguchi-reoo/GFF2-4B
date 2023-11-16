#include "LoadingScene.h"
#include "PadInput.h"
#include "Title.h"
#include "GameMain.h"

Loading::Loading()
{
	try
	{
		loading_image = LoadGraph("resource/images/LoadImage.png");
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
	return new Title;
}
void Loading::Draw()const
{
	DrawGraph(0, 0, loading_image, FALSE);
}