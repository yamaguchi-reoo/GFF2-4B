#include "Stage.h"

Stage::Stage(float _x, float _y, float _width, float _height,int _type)
{
	location.x = _x;
	location.y = _y;
	erea.height = _height;
	erea.width = _width;
	type = _type;
	debug_flg = false;
}

Stage::~Stage()
{

}

void Stage::Update()
{

}

void Stage::Draw()const
{
	switch (type)
	{
		//–³
	case 0:
		break;
		//’n–Ê
	case 1:
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, true);
		break;
		//–Ø
	case 2:
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, true);
		break;
		//Šâ
	case 3:
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x333333, true);
		break;
	default:
		break;
	}
	if (debug_flg == true)
	{
		DrawFormatStringF(location.x, location.y, 0xff0000, "%d", type);
	}
}

void Stage::MoveStage(float _x)
{
	location.x += _x;
}