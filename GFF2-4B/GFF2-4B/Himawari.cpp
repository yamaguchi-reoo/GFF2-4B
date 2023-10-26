#include "Himawari.h"
#include"GameMain.h"

Himawari::Himawari()
{
	location.x = 960;
	location.y = 640;
	erea.height = 100;
	erea.width = 50;


	direction = false;
	attack_interval_count = 0;
}

Himawari::~Himawari()
{
}

void Himawari::Update(GameMain* main)
{
}

void Himawari::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, TRUE);

}

AttackData Himawari::CreateAttactData()
{
	AttackData attack_data;
	//‚Ç‚Ì’iŠK‚ÌUŒ‚‚Å‚à•Ï‚í‚ç‚È‚¢î•ñ‚Í‚±‚±‚ÅŠi”[‚·‚é
	attack_data.shift_x = location.x + (erea.width / 2);
	attack_data.shift_y = location.y + (erea.height / 2);
	attack_data.who_attack = 3;
	attack_data.direction = direction;

	//’e‚Ì‘å‚«‚³
	attack_data.width = 100;
	attack_data.height = 100;
	//UŒ‚‚ÉŠÖ‚·‚éî•ñ
	attack_data.attack_time = 10;
	attack_data.damage = 1;
	attack_data.delay = 10;
	return attack_data;
}

void Himawari::Attack(GameMain* main)
{
	attack_interval_count = 60;

	if (attack_interval_count <= 0) {
		//UŒ‚‚ğ¶¬‚·‚é
		main->SpawnAttack(CreateAttactData());
	}

	//UŒ‚ŠÔŠu—p•Ï”
	if (attack_interval_count > 0)
	{
		attack_interval_count--;
	}


}

