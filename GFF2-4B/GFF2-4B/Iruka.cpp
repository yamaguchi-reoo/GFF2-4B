#include "Iruka.h"
#include "GameMain.h"
#include "PadInput.h"

#define MOVE_SPEED  5
#define MOVE_FALL_SPEED  7

#define MAX_FALL_TIME 60


Iruka::Iruka()
{
	iruka_state = IrukaState::LEFT;

	location.x = 1400;
	location.y = 100;
	erea.width = 120;
	erea.height = 50;
	speed = 5;
	who = 2;
	hp = 2;

	fps_count = 0;

	spawn_flg = false;
	attack_flg = true;
	fall_flg = false;

	Date.magenta = 5.0f;
	Date.syan = 15.0f;
	Date.yellow = 5.0f;
}

Iruka::~Iruka()
{
}

void Iruka::Update(GameMain* main)
{
	if (spawn_flg == false) {
		if (attack_flg == true) {
			Attack(main);
			//落下していないとき
			if (fall_flg == false) {
				//左右移動
				Move();
			}
			//落下中
			else if (fall_flg == true) {
				//落下
				MoveFall();
			}
			//復帰
			if (fall_flg == true && location.y == 570) {
				MoveReturn();
			}
		}
	}
	if (KeyInput::OnKey(KEY_INPUT_I)) {
		spawn_flg = false;
		hp = 2;
	}
}

void Iruka::Draw() const
{
	if (spawn_flg == false) {
		//DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ffff, TRUE);
		//左向き	
		if (iruka_state == IrukaState::LEFT) {
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
		//右向き
		else if (iruka_state == IrukaState::RIGHT) {
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		//右向き落下
		else if (iruka_state == IrukaState::RIGHT_FALL) {
			DrawBoxAA(location.x + erea.width, location.y + erea.height - 40, location.x + 30, location.y + erea.height, 0x00ff00, true);
		}
		//左向き落下
		else if (iruka_state == IrukaState::LEFT_FALL) {
			DrawBoxAA(location.x + 30, location.y + erea.height - 40, location.x, location.y + erea.height, 0x00ff00, true);
		}
	}
	DrawFormatString(600, 0, 0xffffff, "%d", hp);
}

void Iruka::Move()
{
	//右移動
	if (iruka_state == IrukaState::RIGHT) {
		location.x += MOVE_SPEED;
		if (location.x > SCREEN_WIDTH + 100) {
			iruka_state = IrukaState::LEFT;
		}
	}
	//左移動
	if (iruka_state == IrukaState::LEFT) {
		location.x -= MOVE_SPEED;
		if (location.x < -100){
			iruka_state = IrukaState::RIGHT;
		}
	}
}

void Iruka::MoveFall()
{
	erea.width = 50;
	erea.height = 120;
	location.y += MOVE_FALL_SPEED;
	if (iruka_state == IrukaState::RIGHT) {
		iruka_state = IrukaState::RIGHT_FALL;
	}
	if (iruka_state == IrukaState::LEFT) {
		iruka_state = IrukaState::LEFT_FALL;
	}
	if (location.y >= 570) {
		location.y = 570;
	}
}

void Iruka::MoveReturn()
{
	if (++fps_count > MAX_FALL_TIME) {
		fall_flg = false;
		location.y = 100;
		erea.width = 120;
		erea.height = 50;
		fps_count = 0;
		if (iruka_state == IrukaState::RIGHT_FALL) {
			iruka_state = IrukaState::RIGHT;
		}
		if (iruka_state == IrukaState::LEFT_FALL) {
			iruka_state = IrukaState::LEFT;
		}
	}
}

AttackData Iruka::CreateAttactData()
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
	if (iruka_state == IrukaState::RIGHT) {
		attack_data.direction = 0;
	}
	else if (iruka_state == IrukaState::LEFT) {
		attack_data.direction = 1;
	}
	
	if (fall_flg == true) {
		attack_data.shift_y = -12;
	}

	return attack_data;
}

void Iruka::Attack(GameMain* main)
{
	//攻撃を生成する
	main->SpawnAttack(CreateAttactData());
}

void Iruka::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		spawn_flg = true;
	}
}

ColorDate Iruka::GetColorDate()
{
	return Date;
}
