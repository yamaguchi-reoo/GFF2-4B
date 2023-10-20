#include "Iruka.h"

Iruka::Iruka()
{
	location.x = 900;
	location.y = 40;
	erea.width = 120;
	erea.height = 50;
}

Iruka::~Iruka()
{
}

void Iruka::Update(GameMain* main)
{
}

void Iruka::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ffff, TRUE);
}
