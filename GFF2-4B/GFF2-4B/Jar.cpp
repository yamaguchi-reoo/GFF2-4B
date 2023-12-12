#include "Jar.h"
#define JAR_GRAVITY  10

Jar::Jar(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.height = 40;
	erea.width = 40;

	jar_image = LoadGraph("resource/images/sampleTubo.png");


	apply_gravity = true;
	onfloor_flg = false;
	spawn_flg = true;

	hp = 1;
	Date.cyan = 0;
	Date.magenta = 5;
	Date.yellow = 5;
}

Jar::~Jar()
{
}

void Jar::Update()
{
	if (spawn_flg == true)
	{
		//���ɐG��Ă��Ȃ��Ȃ�
		if (apply_gravity == true)
		{
			//�d�͂�^����
			JarGiveGravity();
		}
		//�e�ړ��p�ϐ������Z�b�g
		JarReset();
	}
}

void Jar::Draw() const
{
	if (spawn_flg == true)
	{
		DrawRotaGraph(local_location.x + 20, local_location.y + 15, 0.2f, 0, jar_image, TRUE, FALSE);
		//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xBB8B38, false);
	}
}

void Jar::JarReset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	onfloor_flg = false;
}

void Jar::JarGiveGravity()
{
	location.y += JAR_GRAVITY;
}

void Jar::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location b_center = { 0 };
	b_center.x = location.x + (erea.width / 2);
	b_center.y = location.y + (erea.height / 2);
	//���ɐG�ꂽ��
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		onfloor_flg = true;
	}
}

bool Jar::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0 && spawn_flg == true) {
		spawn_flg = false;
		return true;
	}
	return false;
}

