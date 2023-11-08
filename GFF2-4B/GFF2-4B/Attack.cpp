#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
	once = false;
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
		//UŒ‚‚Ìí—Ş‚É‰‚¶‚Ä‹““®‚ğ•Ï‚¦‚é
		switch (attack_data.attack_type)
		{
		case MELEE:
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
			break;
		case BULLET:
			//ˆê‰ñ‚¾‚¯À•W‚ğ“Ç‚İ‚Ş
			if (once == false)
			{
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
				once = true;
			}
			//’e‚ÌŠp“x‚É‰‚¶‚½ˆÚ“®—Ê‚ğİ’è
			float rad = attack_data.angle * (float)M_PI * 2;

			location.x += attack_data.speed * cosf(rad);
			location.y += attack_data.speed * sinf(rad);
			break;
		}
		//Œˆ‚ß‚ç‚ê‚½ŠÔ‚ªŒo‚Á‚½‚çUŒ‚‚ğÁ‚·
		if (--attack_data.attack_time <= 0)
		{
			attack_flg = false;
			//UŒ‚•s”\
			can_apply_damage = false;
			//ƒŠƒZƒbƒg
			once = false;
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
	if (can_apply_damage == true)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, false);
	}

}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
}
