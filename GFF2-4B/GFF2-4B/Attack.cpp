#include"Attack.h"

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
}

Attack::~Attack()
{

}

void Attack::Update(Location _location, Erea _erea)
{
	//ƒvƒŒƒCƒ„[‚ÌUŒ‚ˆ—
	if (attack_flg == true && --attack_data.delay < 0)
	{
		//UŒ‚‰Â”\
		can_apply_damage = true;
		//‰E•ûŒü‚ÉUŒ‚‚·‚é
		if (attack_data.direction == false)
		{
			location.x = _location.x + (_erea.width / 2) + attack_data.shift_x;
			location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

		}
		//¶•ûŒü‚ÉUŒ‚‚·‚é
		else
		{
			location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x;
			location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;
	
		}
		//Œˆ‚ß‚ç‚ê‚½ŠÔ‚ªŒo‚Á‚½‚çUŒ‚‚ğÁ‚·
		if (--attack_data.attack_time <= 0)
		{
			attack_flg = false;
		}
	}
	else
	{
		//UŒ‚•s”\
		can_apply_damage = false;
	}
}

void Attack::Draw()const
{
	if (can_apply_damage)
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, false);
	}
}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
}
