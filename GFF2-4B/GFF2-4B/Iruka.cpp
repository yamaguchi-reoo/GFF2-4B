#include "Iruka.h"


Iruka::Iruka()
{
	location.x = 900;
	location.y = 300;
	erea.width = 120;
	erea.height = 50;
	speed = 3;

	fpscount = 0;

	iruka_flg = false;
	fall_flg = false;
}

Iruka::~Iruka()
{
}

void Iruka::Update(GameMain* main)
{
	//—‰º‚µ‚Ä‚¢‚È‚¢‚Æ‚«
	if (fall_flg == false) {
		//¶ˆÚ“®
		if (iruka_flg == false) {
			location.x--;
			if (location.x < 0) {
				iruka_flg = true;
			}
		}
		//‰EˆÚ“®
		if (iruka_flg == true) {
			location.x++;
			if (location.x > 500) {
				iruka_flg = false;
			}
		}
	}

	//—‰º’†
	if (fall_flg == true) {
		erea.width = 50;
		erea.height = 120;
		location.y+=speed;
		if (location.y >= 570) {
			location.y = 570;
		}
		
	}

	if (fall_flg == true && location.y == 570) {
		if (++fpscount > 60) {
			fall_flg = false;
			location.y = 300;
			erea.width = 120;
			erea.height = 50;
			fpscount = 0;
		}
	}

}

void Iruka::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ffff, TRUE);
}
