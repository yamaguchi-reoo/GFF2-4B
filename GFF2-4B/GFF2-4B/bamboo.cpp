#include "bamboo.h"
#include "PadInput.h"

#define BAMBOO_GRAVITY  10

Bamboo::Bamboo(float pos_x, float pos_y)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.width = 40;
	erea.height = 60;

	hp = 1;

	apply_gravity = true;
	onfloor_flg = false;
	spawn_flg = false;
}

Bamboo::~Bamboo()
{
}

void Bamboo::Update(GameMain* main)
{
	if (PadInput::OnButton(XINPUT_BUTTON_START))
	{
		spawn_flg = true;
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		//重力を与える
		BambooGiveGravity();
	}
	//各移動用変数をリセット
	BambooReset();
}

void Bamboo::Draw() const
{
	if (spawn_flg == false)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffffff, FALSE);
	}
	DrawFormatString(200, 400, 0xfffff, "%d", spawn_flg);
}
	

void Bamboo::BambooReset()
{	//重力が働くかの判定をリセット
	apply_gravity = true;
	onfloor_flg = false;
}

void Bamboo::BambooGiveGravity()
{
	location.y += BAMBOO_GRAVITY;
}

void Bamboo::BambooPush(int num, Location _sub_location, Erea _sub_erea)
{
	Location b_center = { 0 };
	b_center.x = location.x + (erea.width / 2);
	b_center.y = location.y + (erea.height / 2);
	//床に触れた時
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
		spawn_flg = true;
	}
}
void Bamboo::ReverseFlg()
{
	apply_gravity = false;
	onfloor_flg = true;
}
