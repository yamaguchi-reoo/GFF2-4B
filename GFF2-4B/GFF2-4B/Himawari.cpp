#include "Himawari.h"
#include "GameMain.h"


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
	if (spawn_flg == false && attack_flg == true)
	{
		//�U��
		Attack(main);
	}
}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, TRUE);
		//������	
		if (himawari_direction == true) 
		{
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
		//�E����
		else if (himawari_direction == false) 
		{
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
	}
}

AttackData Himawari::CreateAttactData()
{

	AttackData attack_data;
	//�ǂ̒i�K�̍U���ł��ς��Ȃ����͂����Ŋi�[����
	attack_data.shift_x = -erea.width;//location.x + (erea.width / 2);
	attack_data.shift_y = 0;//erea.height/2;
	attack_data.who_attack = who;
	attack_data.direction = 1;//himawari_direction;
	//�e�̑傫��
	attack_data.width = 200;
	attack_data.height = 200;
	//�U���Ɋւ�����
	attack_data.attack_time = 10;
	attack_data.damage = 1;
	attack_data.delay = 5;
	attack_data.attack_type = BULLET;//MELEE;

	//
	if (himawari_direction == false)
	{
		attack_data.angle = 0.0f;
	}
	else
	{
		attack_data.angle = 0.5f;
	}
	attack_data.speed = 20;

	return attack_data;
}

void Himawari::Attack(GameMain* main)
{
	//attack_interval_count = 60;

	if (++attack_interval_count >= 60) {
		//�U���𐶐�����
		main->SpawnAttack(CreateAttactData());
		attack_interval_count = 0;
	}

	//�U���Ԋu�p�ϐ�
	//if (attack_interval_count > 0)
	//{
	//	attack_interval_count--;
	//}


}

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

