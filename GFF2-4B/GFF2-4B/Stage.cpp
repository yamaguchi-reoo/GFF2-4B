#include "Stage.h"

Stage::Stage()
{
	location.x = 0;
	location.y = 700;
	erea.height = 200;
	erea.width = SCREEN_WIDTH;
}

Stage::~Stage()
{

}

void Stage::Update()
{

}

void Stage::Draw()const
{
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, true);
}