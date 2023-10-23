#include"Attack.h"

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
}

Attack::~Attack()
{

}

void Attack::Update(Location _location, Erea _erea)
{
	//プレイヤーの攻撃処理
	if (attack_flg == true)
	{
		//右方向に攻撃する
		if (attack_data.direction == false)
		{
			//location.x = _location.x +(_erea.width / 2);
			//location.y = _location.y + ATTACK_EREA_SHIFT_Y;
		}
		else
		{
			//location.x = _location.x - erea.width - (_erea.width / 2);
			//location.y = _location.y + ATTACK_EREA_SHIFT_Y;
		}
		if (--attack_data.attack_time <= 0)
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

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	location.x = attack_data.center_x;
	location.y = attack_data.center_y;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
}