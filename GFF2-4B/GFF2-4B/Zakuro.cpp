#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"
#include"GameMain.h"

#define MOVE_SPEED  5

Zakuro::Zakuro()
{
	zakuro_state = ZakuroState::LEFT;

	location.x = 400;
	location.y = 200;
	erea.height = 50;
	erea.width = 50;
	speed = MOVE_SPEED;
	who = 1;
	hp = 1;

	stop_count = 120;


	zakuro_direction = true;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	attack_flg = true;
	spawn_flg = false;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;



	Date.magenta = 15.0f;
	Date.syan = 5.0f;
	Date.yellow = 5.0f;
}
Zakuro::~Zakuro()
{
}
void Zakuro::Update(GameMain* main)
{
	if (spawn_flg == false) 
	{
		if (attack_flg == true) 
		{
			//çUåÇ
			Attack(main);
			//ç∂âEà⁄ìÆ
			Move();
		}
		else 
		{
			//ÉmÉbÉNÉoÉbÉN
			MoveNockBack();
		}
	}
	//èdóÕÇâ¡Ç¶ÇÈÇ©ÇÃèàóù
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (onfloor_flg[i] == true)
		{
			apply_gravity = false;
			if (zakuro_direction == true)
			{
				zakuro_state = ZakuroState::LEFT;
			}
			else
			{
				zakuro_state = ZakuroState::RIGHT;
			}
		}
	}
	//è∞Ç…êGÇÍÇƒÇ¢Ç»Ç¢Ç»ÇÁ
	if (apply_gravity == true)
	{
		//èdóÕÇó^Ç¶ÇÈ
		ZakuroGiveGravity();
	}
	if (leftwall_flg == true) {
		zakuro_state = ZakuroState::RIGHT;
		zakuro_direction = false;
		leftwall_flg = false;
	}
	if (rightwall_flg == true) {
		zakuro_state = ZakuroState::LEFT;
		zakuro_direction = true;
		rightwall_flg = false;
	}
	if (KeyInput::OnKey(KEY_INPUT_Z)) 
	{
		spawn_flg = false;
	}

	ZakuroReset();
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	if (spawn_flg == false) 
	{
		//DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
		if (zakuro_state == ZakuroState::RIGHT)
		{
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		else
		{
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
	}
}

void Zakuro::Move()
{
	//ç∂à⁄ìÆ
	if (zakuro_state == ZakuroState::LEFT) 
	{
		location.x -= MOVE_SPEED;
		zakuro_direction = true;
		if (location.x < 0) 
		{
			zakuro_state = ZakuroState::RIGHT;
			zakuro_direction = false;
		}
	}
	//âEà⁄ìÆ
	if (zakuro_state == ZakuroState::RIGHT) 
	{
		location.x += MOVE_SPEED;
		zakuro_direction = false;
		if (location.x > SCREEN_WIDTH - 50) 
		{
			zakuro_state = ZakuroState::LEFT;
			zakuro_direction = true;
		}
	}
}
void Zakuro::MoveNockBack()
{
	//ç∂à⁄ìÆ
	if (zakuro_state == ZakuroState::LEFT) 
	{
		location.x += speed * 0.3;
	}
	//âEà⁄ìÆ
	if (zakuro_state == ZakuroState::RIGHT) 
	{
		location.x -= speed * 0.3;
	}

	if (--stop_count <= 0) 
	{
		attack_flg = true;
		stop_count = 120;
	}
}

void Zakuro::ZakuroReset()
{
	//èdóÕÇ™ì≠Ç≠Ç©ÇÃîªíËÇÉäÉZÉbÉg
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
}

void Zakuro::ZakuroGiveGravity()
{
	zakuro_state = ZakuroState::IDLE;
	location.y += MOVE_SPEED;
}

void Zakuro::ZakuroOnFloor(int num, Location _sub)
{
	onfloor_flg[num] = true;
}

void Zakuro::ZakuroPush(int num, Location _sub_location, Erea _sub_erea)
{
	Location z_center = { 0 };
	z_center.x = location.x + (erea.width / 2);
	z_center.y = location.y + (erea.height / 2);

	//è∞Ç…êGÇÍÇΩéû
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		ZakuroOnFloor(num, _sub_location);
	}
	//âEÇÃï«Ç…êGÇÍÇΩéû
	else if (location.x + erea.width - 10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;

		//âEÇÃï«Ç…êGÇÍÇΩÉtÉâÉOÇóßÇƒÇÈ
		rightwall_flg = true;
	}
	//ç∂ÇÃï«Ç…êGÇÍÇΩéû
	else if (location.x + 10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;

		//ç∂ÇÃï«Ç…êGÇÍÇΩÉtÉâÉOÇóßÇƒÇÈ
		leftwall_flg = true;
	}
	//Ç«Ç¡ÇøÇÃï«Ç…Ç‡êGÇÍÇƒÇ¢Ç»Ç¢Ç∆Ç´ÇÃínñ Ç∑ÇËî≤ÇØñhé~
	else
	{
		location.y = _sub_location.y - erea.height;
		ZakuroOnFloor(num, _sub_location);
	}
}

AttackData Zakuro::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = erea.height / 2;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 2;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = MELEE;

	if (zakuro_state == ZakuroState::RIGHT) 
	{
		attack_data.direction = 0;
	}
	else if (zakuro_state == ZakuroState::LEFT) 
	{
		attack_data.direction = 1;
	}

	return attack_data;
}

void Zakuro::Attack(GameMain* main)
{
	//çUåÇÇê∂ê¨Ç∑ÇÈ
	main->SpawnAttack(CreateAttactData());
}

void Zakuro::ApplyDamage(int num)
{
	hp -= num;
	spawn_flg = true;
}

ColorDate Zakuro::GetColorDate()
{
	return Date;
}




