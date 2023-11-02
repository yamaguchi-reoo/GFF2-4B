#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"
#include"GameMain.h"

#define MOVE_SPEED  4
#define ZAKURO_GRAVITY  10

Zakuro::Zakuro(float pos_x, float pos_y, bool direction)
{
	zakuro_state = ZakuroState::IDLE;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 50;
	erea.width = 50;
	speed = MOVE_SPEED;
	who = 1;
	hp = 1;

	stop_count = 120;

	zakuro_direction = true;
	onfloor_flg = false;
	attack_flg = true;
	spawn_flg = false;
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
			//�U��
			Attack(main);
			//���E�ړ�
			Move();
		}
		else 
		{
			//�m�b�N�o�b�N
			MoveNockBack();
		}
	}
		//���ɏ���Ă�����d��OFF
	if (onfloor_flg == true)
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
	//���ɐG��Ă��Ȃ��Ȃ�
	if (apply_gravity == true)
	{
		//�d�͂�^����
		ZakuroGiveGravity();
	}
	//���̕ǂɂԂ�������E�Ɉړ�
	if (leftwall_flg == true) {
		zakuro_state = ZakuroState::RIGHT;
		zakuro_direction = false;
		leftwall_flg = false;
	}
	//�E�̕ǂɂԂ������獶�Ɉړ�
	if (rightwall_flg == true) {
		zakuro_state = ZakuroState::LEFT;
		zakuro_direction = true;
		rightwall_flg = false;
	}
	if (KeyInput::OnKey(KEY_INPUT_Z)) 
	{
		spawn_flg = false;
	}
	//�e�ړ��p�ϐ������Z�b�g
	ZakuroReset();
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	if (spawn_flg == false) 
	{
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
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
	//���ړ�
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
	//�E�ړ�
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
	//���ړ�
	if (zakuro_state == ZakuroState::LEFT) 
	{
		location.x += speed * 0.3;
	}
	//�E�ړ�
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
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Zakuro::ZakuroGiveGravity()
{
	zakuro_state = ZakuroState::IDLE;
	location.y += ZAKURO_GRAVITY;
}

void Zakuro::ZakuroPush(int num, Location _sub_location, Erea _sub_erea)
{
	Location z_center = { 0 };
	z_center.x = location.x + (erea.width / 2);
	z_center.y = location.y + (erea.height / 2);

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
	attack_data.direction = zakuro_direction;


	return attack_data;
}

void Zakuro::Attack(GameMain* main)
{
	//�U���𐶐�����
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




