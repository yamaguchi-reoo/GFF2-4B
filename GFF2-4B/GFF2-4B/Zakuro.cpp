#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"
#include"GameMain.h"

#define MOVE_SPEED  5

Zakuro::Zakuro()
{
	direction = Direction::LEFT;

	location.x = 900;
	location.y = 570;
	erea.height = 50;
	erea.width = 50;
	speed = 2;
	who = 1;
	//direction = true;
	attack_flg = true;
	stop_count = 120;

	spawn_flg = false;

	hp = 1;


	Date.magenta = 15.0f;
	Date.syan = 5.0f;
	Date.yellow = 5.0f;
}
Zakuro::~Zakuro()
{
	
}
void Zakuro::Update(GameMain* main)
{
	if (spawn_flg == false) {

		if (attack_flg == true) {
			Attack(main);
			//左右移動
			Move();
		}
		else {
			//ノックバック
			MoveNockBack();
		}
	}
	if (KeyInput::OnKey(KEY_INPUT_Z)) {
		spawn_flg = false;
	}
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	if (spawn_flg == false) {
		//DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
		if (direction == Direction::RIGHT){
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		else{
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
	}
}

void Zakuro::Move()
{
	//左移動
	if (direction == Direction::LEFT) {
		location.x -= MOVE_SPEED;
		if (location.x < 0) {
			direction = Direction::RIGHT;
		}
	}
	//右移動
	if (direction == Direction::RIGHT) {
		location.x += MOVE_SPEED;
		if (location.x > SCREEN_WIDTH - 80) {
			direction = Direction::LEFT;
		}
	}
}

void Zakuro::MoveNockBack()
{
	//左移動
	if (direction == Direction::LEFT) {
		location.x += speed * 0.3;
	}
	//右移動
	if (direction == Direction::RIGHT) {
		location.x -= speed * 0.3;
	}

	if (--stop_count <= 0) {
		attack_flg = true;
		stop_count = 120;
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

	if (direction == Direction::RIGHT) {
		attack_data.direction = 0;
	}
	else if (direction == Direction::LEFT) {
		attack_data.direction = 1;
	}

	return attack_data;
}

void Zakuro::Attack(GameMain* main)
{
	//攻撃を生成する
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




