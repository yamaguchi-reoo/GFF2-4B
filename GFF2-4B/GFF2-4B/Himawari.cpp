#include "Himawari.h"
#include "GameMain.h"

#define BULLET_INTERVAL 60

Himawari::Himawari(float pos_x, float pos_y, bool direction, int _who)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.height = 100;
	erea.width = 50;
	who = _who;

	himawari_direction = direction;

	attack_flg = true;
	spawn_flg = false;

	attack_interval_count = 0;

	Date.magenta = 5.0f;
	Date.syan = 5.0f;
	Date.yellow = 15.0f;
}

Himawari::~Himawari()
{
}

void Himawari::Update(GameMain* main)
{
	//ƒXƒ|[ƒ“‚µ‚Ä‚¢‚é‚©‚ÂƒAƒ^ƒbƒNƒtƒ‰ƒO‚ª—§‚Á‚Ä‚¢‚é‚Æ‚«
	if (spawn_flg == false && attack_flg == true)
	{
		//UŒ‚
		Attack(main);
	}
}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, TRUE);
		//¶Œü‚«	
		if (himawari_direction == true) 
		{
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
		//‰EŒü‚«
		else if (himawari_direction == false) 
		{
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
	}
}

AttackData Himawari::CreateAttactData()
{

	AttackData attack_data;
	//‚Ç‚Ì’iŠK‚ÌUŒ‚‚Å‚à•Ï‚í‚ç‚È‚¢î•ñ‚Í‚±‚±‚ÅŠi”[‚·‚é
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = 0;
	attack_data.who_attack = who;
	attack_data.direction = himawari_direction;
	//’e‚Ì‘å‚«‚³
	attack_data.width = 40;
	attack_data.height = 40;
	//UŒ‚‚ÉŠÖ‚·‚éî•ñ
	attack_data.attack_time = 200;
	attack_data.damage = 1;
	attack_data.delay = 5;
	attack_data.attack_type = BULLET;//MELEE;

	//‰E‚ÉŒü‚¢‚Ä‚¢‚½‚çƒAƒ“ƒOƒ‹‚Í‚»‚Ì‚Ü‚Ü
	if (himawari_direction == false)
	{
		attack_data.angle = 0.0f;
	}
	//¶‚ÉŒü‚¢‚Ä‚¢‚½‚çƒAƒ“ƒOƒ‹‚ð180‰ñ“]
	else
	{
		attack_data.angle = 0.5f;
	}
	attack_data.speed = 5;

	return attack_data;
}

void Himawari::Attack(GameMain* main)
{
	//attack_interval_count = 60;

	if (++attack_interval_count >= BULLET_INTERVAL) {
		//UŒ‚‚ð¶¬‚·‚é
		main->SpawnAttack(CreateAttactData());
		attack_interval_count = 0;
	}
}

void Himawari::ApplyDamage(int num)
{
	hp -= num;
	spawn_flg = true;
}

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

