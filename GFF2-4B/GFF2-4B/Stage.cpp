#include "Stage.h"

Stage::Stage(float _x, float _y, float _width, float _height,int _type)
{
	location.x = _x;
	location.y = _y;
	erea.height = _height;
	erea.width = _width;
	type = _type;
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
		//��
	case 0:
		break;
		//�n��
	case 1:
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, true);
		break;
		//��
	case 2:
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, true);
		break;
		//��
	case 3:
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x333333, true);
		break;
	default:
		break;
	}
}

void Stage::MoveStage(float _x)
{
	location.x += _x;
}