#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"

Zakuro::Zakuro()
{
	location.x = 290;
	location.y = 570;
	erea.height = 50;
	erea.width = 50;
	speed = 2;

	direction = false;
	zakuro_flg = false;
}
Zakuro::~Zakuro()
{
	
}
void Zakuro::Update(GameMain* main)
{
	
	//‰EˆÚ“®
	if (zakuro_flg == true) {
		location.x += speed;
		if (location.x > 500) {
			zakuro_flg = false;
			direction = false;
		}
	}
	//¶ˆÚ“®
	if (zakuro_flg == false) {
		location.x -= speed;
		if (location.x < 0) {
			zakuro_flg = true;
			direction = true;
		}
	}
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
	if (direction == true)
	{
		DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
	}
	else
	{
		DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
	}
}

AttackData Zakuro::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = 0;
	attack_data.shift_y = 0;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = false;
	attack_data.attack_time = 0;
	attack_data.direction = direction;
	attack_data.delay = 0;
	return attack_data;
}


