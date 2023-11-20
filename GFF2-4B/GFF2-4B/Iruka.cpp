#include "Iruka.h"
#include "GameMain.h"
#include "PadInput.h"

#define MOVE_SPEED  3
#define MOVE_FALL_SPEED  5

#define MAX_FALL_TIME 120

#define IRUKA_IMAGE_SHIFT_X 10		//画像ずらし用
#define IRUKA_IMAGE_SHIFT_Y 10		//画像ずらし用

#define TRUN_RAD 1.5708f		//90度回転用

Iruka::Iruka(float pos_x, float pos_y, bool direction, int _who)
{
	iruka_state = IrukaState::LEFT;

	location.x = pos_x;//1400;
	location.y = pos_y;// 100;
	spawn_location_y = pos_y;
	spawn_location_x = pos_x;
	erea.width = 100;
	erea.height = 50;
	speed = 5;
	who = _who;
	hp = 2;

	image = LoadGraph("resource/images/Enemy/Iruka.png");

	fps_count = 0;

	iruka_direction = direction;// true;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	return_flg = false;
	spawn_flg = false;
	attack_flg = true;
	fall_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;

	Date.magenta = 5.0f;
	Date.cyan = 15.0f;
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
			if (fall_flg == false && return_flg == false) {
				//左右移動
				Move();
			}
			//落下中
			else if (fall_flg == true) {
				//落下
				MoveFall();
			}
			//復帰
			if (return_flg == true /* && location.y == 570*/) {
				MoveReturn();
			}
		}
	}
	//左の壁にぶつかったら右に移動
	if (leftwall_flg == true) {
		iruka_state = IrukaState::RIGHT;
		iruka_direction = false;
		leftwall_flg = false;
	}
	//右の壁にぶつかったら左に移動
	if (rightwall_flg == true) {
		iruka_state = IrukaState::LEFT;
		iruka_direction = true;
		rightwall_flg = false;
	}

	IrukaReset();
	if (KeyInput::OnKey(KEY_INPUT_I)) {
		spawn_flg = false;
		hp = 2;
	}
}

void Iruka::Draw() const
{
	if (spawn_flg == false) {
		//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ffff, TRUE);
		switch (iruka_state)
		{
		case IrukaState::IDLE:
			break;
		case IrukaState::RIGHT:
			DrawTurnGraphF(local_location.x + IRUKA_IMAGE_SHIFT_X, local_location.y + IRUKA_IMAGE_SHIFT_Y, image, true);
			break;
		case IrukaState::LEFT:
			DrawGraphF(local_location.x, local_location.y + IRUKA_IMAGE_SHIFT_Y, image, true);
			break;
		case IrukaState::RIGHT_FALL:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 4), 1, TRUN_RAD, image, true, true);
			break;
		case IrukaState::LEFT_FALL:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 4), 1, -TRUN_RAD, image, true, false);
			break;
		case IrukaState::RIGHT_RETURN:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 5), 1, -TRUN_RAD, image, true, true);
			break;
		case IrukaState::LEFT_RETURN:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 5), 1, TRUN_RAD, image, true, false);
			break;
		default:
			break;
		}
	}
}

void Iruka::Move()
{
	//左移動
	if (iruka_state == IrukaState::LEFT)
	{
		location.x -= MOVE_SPEED;
		iruka_direction = true;
		if (location.x <= spawn_location_x - 640) {
			iruka_state = IrukaState::RIGHT;
		}
	/*	if (location.x < -100)
		{
			iruka_state = IrukaState::RIGHT;
			iruka_direction = false;
		}*/
	}
	//右移動
	if (iruka_state == IrukaState::RIGHT)
	{
		location.x += MOVE_SPEED;
		iruka_direction = false;
		if (location.x >= spawn_location_x + 640) {
			iruka_state = IrukaState::LEFT;

		}
	/*	if (location.x > SCREEN_WIDTH + 100) 
		{
			iruka_state = IrukaState::LEFT;
			iruka_direction = true;
		}*/
	}
}

void Iruka::MoveFall()
{
	erea.width = 50;
	erea.height = 120;
	location.y += MOVE_FALL_SPEED;
	if (iruka_state == IrukaState::RIGHT) 
	{
		iruka_state = IrukaState::RIGHT_FALL;
	}
	if (iruka_state == IrukaState::LEFT) 
	{
		iruka_state = IrukaState::LEFT_FALL;
	}
	if (location.y >= 570) 
	{
		location.y = 570;
	}
}

void Iruka::MoveReturn()
{
	
	if (++fps_count > MAX_FALL_TIME)
	{
		if (return_flg == true) {
			location.y -= speed;
			if (spawn_location_y >= location.y) {

				location.y = spawn_location_y;
				erea.width = 120;
				erea.height = 50;
				return_flg = false;
				fps_count = 0;
				if (iruka_state == IrukaState::RIGHT_RETURN)
				{
					iruka_state = IrukaState::RIGHT;
				}
				if (iruka_state == IrukaState::LEFT_RETURN)
				{
					iruka_state = IrukaState::LEFT;
				}
			}
		}
		
		if (iruka_state == IrukaState::RIGHT_FALL) 
		{
			iruka_state = IrukaState::RIGHT_RETURN;
		}
		if (iruka_state == IrukaState::LEFT_FALL) 
		{
			iruka_state = IrukaState::LEFT_RETURN;
		}		
	}
}

void Iruka::IrukaOnFloor(int num, Location _sub)
{
	onfloor_flg[num] = true;
	if (fall_flg == true) {
		return_flg = true;
		fall_flg = false;
	}
	
}

void Iruka::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location i_center = { 0 };
	i_center.x = location.x + (erea.width / 2);
	i_center.y = location.y + (erea.height / 2);

	//床に触れた時
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		IrukaOnFloor(num, _sub_location);
	}
	//右の壁に触れた時
	else if (location.x + erea.width - 10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;

		//右の壁に触れたフラグを立てる
		rightwall_flg = true;
	}
	//左の壁に触れた時
	else if (location.x + 10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;

		//左の壁に触れたフラグを立てる
		leftwall_flg = true;
	}
	//どっちの壁にも触れていないときの地面すり抜け防止
	else
	{
		location.y = _sub_location.y - erea.height;
		IrukaOnFloor(num, _sub_location);
	}
}

void Iruka::IrukaReset()
{
	//重力が働くかの判定をリセット
	rightwall_flg = false;
	leftwall_flg = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
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

	if (return_flg == true) {
		attack_data.shift_y = -6.5;
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
