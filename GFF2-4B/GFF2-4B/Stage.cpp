#include "Stage.h"

Stage::Stage(float _x, float _y, float _width, float _height)
{
	location.x = _x;
	location.y = _y;
	erea.height = _height;
	erea.width = _width;
}

Stage::~Stage()
{

}

void Stage::Update()
{

}

void Stage::Draw()const
{
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, true);
}

void Stage::MoveStage(ScrollData _scroll)
{
	if (_scroll.direction == true)
	{
		location.x += _scroll.move;
	}
	else
	{
		location.x -= _scroll.move;
	}
}