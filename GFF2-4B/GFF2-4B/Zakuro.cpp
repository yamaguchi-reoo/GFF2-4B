#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"
#include"GameMain.h"


Zakuro::Zakuro()
{
	location.x = 290;
	location.y = 570;
	erea.height = 50;
	erea.width = 50;
	speed = 2;
	who = 1;
	direction = false;
	attack_flg = true;
	stop_count = 120;

	spawn_flg = false;

	hp = 1;
}
Zakuro::~Zakuro()
{
	
}
void Zakuro::Update(GameMain* main)
{
	if (spawn_flg == false) {

		if (attack_flg == true) {
			Attack(main);
			//¶ˆÚ“®
			if (direction == true) {
				location.x -= speed;
				if (location.x < 0) {


					direction = false;
				}
			}
			//‰EˆÚ“®
			if (direction == false) {
				location.x += speed;
				if (location.x > SCREEN_WIDTH) {
					direction = true;
				}
			}
		}
		else {

			//¶ˆÚ“®
			if (direction == true) {
				location.x += speed*0.3;
			}
			//‰EˆÚ“®
			if (direction == false) {
				location.x -= speed*0.3;
			}

			if (--stop_count <= 0) {
				attack_flg = true;
				stop_count = 120;
			}
		}
	}
	if (KeyInput::OnKey(KEY_INPUT_Z)) {
		spawn_flg = false;
	}
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	//DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	if (spawn_flg == false) {
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
		if (direction == false)
		{
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		else
		{
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
	}
	
}

AttackData Zakuro::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = erea.height;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 3;
	attack_data.direction = direction;
	attack_data.delay = 0;
	attack_data.damage = 1;

	return attack_data;
}


void Zakuro::Attack(GameMain* main)
{
	//UŒ‚‚ğ¶¬‚·‚é
	main->SpawnAttack(CreateAttactData());
}

void Zakuro::ApplyDamage(int num)
{
	hp -= num;
	spawn_flg = true;
}




