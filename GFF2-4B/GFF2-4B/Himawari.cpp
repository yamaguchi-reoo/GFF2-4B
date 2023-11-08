#include "Himawari.h"
#include "GameMain.h"

#define BULLET_INTERVAL 60
#define HIMAWARI_GRAVITY  10

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

	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	onfloor_flg = false;
	

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
	//�X�|�[�����Ă��邩�A�^�b�N�t���O�������Ă���Ƃ�
	if (spawn_flg == false && attack_flg == true)
	{
		//�U��
		Attack(main);
	}
	//���ɐG��Ă��Ȃ��Ȃ�
	if (apply_gravity == true)
	{
		//�d�͂�^����
		HimawariGiveGravity();
	}
	//�e�ړ��p�ϐ������Z�b�g
	HimawariReset();
}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, TRUE);
		//������	
		if (himawari_direction == true) 
		{
			DrawBoxAA(local_location.x + 40, local_location.y + 10, local_location.x, local_location.y + 40, 0x00ff00, true);
		}
		//�E����
		else if (himawari_direction == false) 
		{
			DrawBoxAA(local_location.x + erea.width - 40, local_location.y + 10, local_location.x + erea.width, local_location.y + 40, 0x00ff00, true);
		}
	}
}

void Himawari::HimawariReset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Himawari::HimawariGiveGravity()
{
	location.y += HIMAWARI_GRAVITY;
}

void Himawari::HimawariPush(int num, Location _sub_location, Erea _sub_erea)
{
	Location h_center = { 0 };
	h_center.x = location.x + (erea.width / 2);
	h_center.y = location.y + (erea.height / 2);

	//���ɐG�ꂽ��
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		onfloor_flg = true;
	}
	//�E�̕ǂɐG�ꂽ��
	else if (location.x + erea.width - 10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;

		//�E�̕ǂɐG�ꂽ�t���O�𗧂Ă�
		rightwall_flg = true;
	}
	//���̕ǂɐG�ꂽ��
	else if (location.x + 10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;

		//���̕ǂɐG�ꂽ�t���O�𗧂Ă�
		leftwall_flg = true;
	}
	//�ǂ����̕ǂɂ��G��Ă��Ȃ��Ƃ��̒n�ʂ��蔲���h�~
	else
	{
		location.y = _sub_location.y - erea.height;
		onfloor_flg = true;
	}
}

AttackData Himawari::CreateAttactData()
{

	AttackData attack_data;
	//�ǂ̒i�K�̍U���ł��ς��Ȃ����͂����Ŋi�[����
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = 0;
	attack_data.who_attack = who;
	attack_data.direction = himawari_direction;
	//�e�̑傫��
	attack_data.width = 40;
	attack_data.height = 40;
	//�U���Ɋւ�����
	attack_data.attack_time = 200;
	attack_data.damage = 1;
	attack_data.delay = 5;
	attack_data.attack_type = BULLET;//MELEE;

	//�E�Ɍ����Ă�����A���O���͂��̂܂�
	if (himawari_direction == false)
	{
		attack_data.angle = 0.0f;
	}
	//���Ɍ����Ă�����A���O����180��]
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
		//�U���𐶐�����
		main->SpawnAttack(CreateAttactData());
		attack_interval_count = 0;
	}
}

void Himawari::ApplyDamage(int num)
{
	hp -= num;
	spawn_flg = true;
}

void Himawari::ReverseDirection()
{
		himawari_direction = false;
}

void Himawari::ObverseDirection()
{
	himawari_direction =true ;
}

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

