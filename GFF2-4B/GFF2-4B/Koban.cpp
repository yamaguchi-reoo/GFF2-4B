#include "Koban.h"

Koban::Koban(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.height = 40;
	erea.width = 40;

	KobanImg = 0;
}

Koban::~Koban()
{
}

void Koban::Update()
{
}

void Koban::Draw() const
{
	DrawBoxAA(190.0f, 580.0f, 230.0f, 620.0f, 0xffff00, TRUE);
}