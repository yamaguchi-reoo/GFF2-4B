#include "Himawari.h"

Himawari::Himawari()
{
	location.x = 960;
	location.y = 640;
	erea.height = 200;
	erea.width = 100;
}

Himawari::~Himawari()
{
}

void Himawari::Update(GameMain* main)
{
}

void Himawari::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, TRUE);
}



