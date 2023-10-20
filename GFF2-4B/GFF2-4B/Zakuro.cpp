#include "Zakuro.h"
#include "DxLib.h"

Zakuro::Zakuro()
{
	location.x = 290;
	location.y = 640;
	erea.height = 50;
	erea.width = 50;

}
Zakuro::~Zakuro()
{
	
}
void Zakuro::Update(GameMain* main)
{

}

void Zakuro::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
}



