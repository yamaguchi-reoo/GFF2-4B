#include"Attack.h"

Attack::Attack()
{
	attack_flg = false;
	who_attack = false;
	attack_time = 0;
}

Attack::~Attack()
{

}

void Attack::Update(Location _location)
{
	if (attack_flg == true)
	{
		location = _location;
		if (--attack_time <= 0)
		{
			attack_flg = false;
		}
	}
}

void Attack::Draw()const
{
	if (attack_flg == true)
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, false);
	}
}

void Attack::SpawnAttack(Location _location)
{
	attack_flg = true;
	attack_time = 10;
	location = _location;
	erea.width = 100;
	erea.height = 100;
}