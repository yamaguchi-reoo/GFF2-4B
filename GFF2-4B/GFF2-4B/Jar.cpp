#include "Jar.h"

Jar::Jar(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.height = 40;
	erea.width = 40;

	spawn_flg = true;
}

Jar::~Jar()
{
}

void Jar::Update()
{
}

void Jar::Draw() const
{
	/*if (spawn_flg == true)
	{*/
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xf000ff, TRUE);
	//}	
}
