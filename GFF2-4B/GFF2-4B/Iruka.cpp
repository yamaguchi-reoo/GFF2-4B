#include "Iruka.h"
#include "GameMain.h"
#include "PadInput.h"

#define MOVE_SPEED  5
#define MOVE_FALL_SPEED  7

#define MAX_FALL_TIME 60


Iruka::Iruka(float pos_x, float pos_y, bool direction)
{
	iruka_state = IrukaState::LEFT;

	location.x = pos_x;//1400;
	location.y = pos_y;// 100;
	erea.width = 120;
	erea.height = 50;
	speed = 5;
	who = 2;
	hp = 2;

	fps_count = 0;

	iruka_direction = direction;// true;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	spawn_flg = false;
	attack_flg = true;
	fall_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;

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
			//�������Ă��Ȃ��Ƃ�
			if (fall_flg == false) {
				//���E�ړ�
				Move();
			}
			//������
			else if (fall_flg == true) {
				//����
				MoveFall();
			}
			//���A
			//if (fall_flg == true /* && location.y == 570*/) {
			//	MoveReturn();
			//}
		}
	}
	//���̕ǂɂԂ�������E�Ɉړ�
	if (leftwall_flg == true) {
		iruka_state = IrukaState::RIGHT;
		iruka_direction = false;
		leftwall_flg = false;
	}
	//�E�̕ǂɂԂ������獶�Ɉړ�
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
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ffff, TRUE);
		
		//������	
		if (iruka_state == IrukaState::LEFT) {
			DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
		//�E����
		else if (iruka_state == IrukaState::RIGHT) {
			DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
			DrawBoxAA(location.x + erea.width - 35, location.y, location.x + erea.width, location.y, 0x0000ff, FALSE);
		}
		//�E��������
		else if (iruka_state == IrukaState::RIGHT_FALL) {
			DrawBoxAA(location.x + erea.width, location.y + erea.height - 40, location.x + 30, location.y + erea.height, 0x00ff00, true);
		}
		//����������
		else if (iruka_state == IrukaState::LEFT_FALL) {
			DrawBoxAA(location.x + 30, location.y + erea.height - 40, location.x, location.y + erea.height, 0x00ff00, true);
		}
	}
	DrawFormatString(600, 0, 0xffffff, "%d", hp);
}

void Iruka::Move()
{
	//���ړ�
	if (iruka_state == IrukaState::LEFT) 
	{
		location.x -= MOVE_SPEED;
		iruka_direction = true;
		if (location.x < -100)
		{
			iruka_state = IrukaState::RIGHT;
			iruka_direction = false;
		}
	}
	//�E�ړ�
	if (iruka_state == IrukaState::RIGHT) 
	{
		location.x += MOVE_SPEED;
		iruka_direction = false;
		if (location.x > SCREEN_WIDTH + 100) 
		{
			iruka_state = IrukaState::LEFT;
			iruka_direction = true;
		}
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
		fall_flg = false;
		location.y = 50;
		erea.width = 120;
		erea.height = 50;
		fps_count = 0;
		if (iruka_state == IrukaState::RIGHT_FALL) 
		{
			iruka_state = IrukaState::RIGHT;
		}
		if (iruka_state == IrukaState::LEFT_FALL) 
		{
			iruka_state = IrukaState::LEFT;
		}
	}
}

void Iruka::IrukaOnFloor(int num, Location _sub)
{
	onfloor_flg[num] = true;
	if (fall_flg == true) {
		MoveReturn();
	}
	
}

void Iruka::IrukaPush(int num, Location _sub_location, Erea _sub_erea)
{
	Location i_center = { 0 };
	i_center.x = location.x + (erea.width / 2);
	i_center.y = location.y + (erea.height / 2);

	//���ɐG�ꂽ��
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		IrukaOnFloor(num, _sub_location);
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
		IrukaOnFloor(num, _sub_location);
	}
}

void Iruka::IrukaReset()
{
	//�d�͂��������̔�������Z�b�g
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

	return attack_data;
}

void Iruka::Attack(GameMain* main)
{
	//�U���𐶐�����
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
