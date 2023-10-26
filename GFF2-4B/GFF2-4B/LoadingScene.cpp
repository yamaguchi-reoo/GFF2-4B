#include "LoadingScene.h"

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
	return this;
}
void Loading::Draw()const
{

}