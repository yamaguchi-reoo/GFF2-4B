#include "Stage.h"

Stage::Stage()
{
	location.x = 100;
	location.y = 600;
	erea.height = 200;
	erea.width = 300;
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