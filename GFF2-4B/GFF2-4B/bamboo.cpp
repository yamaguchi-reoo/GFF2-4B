#include "bamboo.h"

Bamboo::Bamboo(float pos_y)
{
	location.x = 900;
	location.y = 700 + pos_y;
	erea.width = 40;
	erea.height = 60;
}

Bamboo::~Bamboo()
{
}

void Bamboo::Update()
{
}

void Bamboo::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);

}
