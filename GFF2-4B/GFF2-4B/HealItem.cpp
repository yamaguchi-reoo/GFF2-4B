#include "HealItem.h"

HealItem::HealItem(/*float pos_x, float pos_y*/)
{
	location.x = 0; //pos_x;
	location.y = 0; //pos_y;
	erea.height = 40;
	erea.width = 40;

	spawn_flg = false;
}
HealItem::~HealItem()
{

}
void HealItem::Update()
{

}
void HealItem::Draw()const
{
	if (spawn_flg == true) {
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, TRUE);
	}
	DrawFormatString(600, 150, 0xff000f, "%d", spawn_flg);
}

float HealItem::SetLocation(Location _location)
{
	location.x = _location.x;
	location.y = _location.y;

	return location.x, location.y;
}
