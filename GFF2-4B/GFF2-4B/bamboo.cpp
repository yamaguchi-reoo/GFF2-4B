#include "bamboo.h"
#include "PadInput.h"

#define BAMBOO_GRAVITY  10

Bamboo::Bamboo(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.width = 100;
	erea.height = 200;

	hp = 1;
	image = LoadGraph("resource/images/Enemy/Bamboo.png");

	apply_gravity = true;
	onfloor_flg = false;
	spawn_flg = true;
}

Bamboo::~Bamboo()
{
}

void Bamboo::Update(GameMain* main)
{
	if (spawn_flg == true)
	{
		//���ɐG��Ă��Ȃ��Ȃ�
		if (apply_gravity == true)
		{
			//�d�͂�^����
			BambooGiveGravity();
		}
		//�e�ړ��p�ϐ������Z�b�g
		BambooReset();
	}
}

void Bamboo::Draw() const
{
	if (spawn_flg == true)
	{
		DrawGraphF(local_location.x, local_location.y, image, FALSE);
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffffff, FALSE);
	}
	//DrawFormatString(200, 400, 0xfffff, "%d", spawn_flg);
}
	

void Bamboo::BambooReset()
{	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	onfloor_flg = false;
}

void Bamboo::BambooGiveGravity()
{
	location.y += BAMBOO_GRAVITY;
}

void Bamboo::Push(int num, Location _sub_location, Erea _sub_erea)
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
void Bamboo::ApplyDamage(int num)
{
	hp = -num;
	if (hp <= 0) {
		spawn_flg = false;
	}
}
void Bamboo::FalseGravity()
{
	apply_gravity = false;
}

