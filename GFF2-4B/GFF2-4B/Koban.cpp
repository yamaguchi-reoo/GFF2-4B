#include "Koban.h"

Koban::Koban(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.height = 40;
	erea.width = 40;

	KobanImg = LoadGraph("resource/images/koban.png");
}

Koban::~Koban()
{
}

void Koban::Update()
{
}

void Koban::Draw() const
{
	DrawGraphF(location.x, location.y, KobanImg, TRUE);
}