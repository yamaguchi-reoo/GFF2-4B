#include "Player.h"
#include "PadInput.h"

#define ACS_MAX 6	//�ő�����x
#define DOWN 0	//�������x�p
#define UP 1	//������x�p
#define RIGHT 2	//�E�����x�p
#define LEFT 3	//�������x�p

#define DEFAULT_MOVE_SPEED 0.3f			//��{�ړ����x(���E)
#define DEFAULT_JUMP_POWER 26			//��{�ő咵����
#define GRAVITY_POWER  (ACS_MAX * 2.5f) //�d�͂̋���

Player::Player()
{
	location.x = 100;
	location.y = 400;
	erea.height = 150;
	erea.width = 75;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
}

Player::~Player() 
{

}

void Player::Update(GameMain* main)
{
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (onfloor_flg[i] == true)
		{
			apply_gravity = false;
		}
	}
	//���ɐG��Ă��Ȃ��Ȃ�
	if (apply_gravity == true)
	{
		GiveGravity();
	}

	//���ړ�
	if (PadInput::TipLeftLStick(STICKL_X) <= -0.5)
	{
		if (acs[LEFT] <= ACS_MAX && rightwall_flg == false)
		{
			acs[LEFT] += move_speed;
		}
	}
	else
	{
		DecAcs(LEFT);
	}

	//�E�ړ�
	if (PadInput::TipLeftLStick(STICKL_X) >= 0.5)
	{	
		if (acs[RIGHT] <= ACS_MAX && leftwall_flg == false)
		{
			acs[RIGHT] += move_speed;
		}
	}
	else
	{
		DecAcs(RIGHT);
	}
	//�W�����v
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true && jump_flg == false)
	{
		acs[UP] = jump_power;
		jump_flg = true;
	}
	else
	{
		//�W�����v���Ă��Ȃ����͏�ɉ�������͂���߂�
		DecAcs(UP);
	}
	//�ʏ�U��
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true)
	{
		main->SpawnAttack(location);
	}

	//�ړ�����
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];
	//��̕�������
	if (acs[LEFT] + acs[RIGHT] > 0)
	{
		direction = false;
	}
	else
	{
		direction = true;
	}
	Reset();
}

void Player::Draw()const
{
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff0000, true);
	for (int i = 0; i < 4; i++)
	{
		DrawFormatString(100, 100+i*30, 0x00ff00, "%f", acs[i]);
	}

}

void Player::GiveGravity()
{
	if (acs[DOWN] <= GRAVITY_POWER)
	{
		acs[DOWN] += 1.5f;
	}
}

void Player::DecAcs(int num)
{
	if (acs[num] > 0)
	{
		acs[num] -= 0.5f;
	}
	else
	{
		acs[num] = 0;
	}
}

void Player::OnFloor(int num,Location _sub)
{
	acs[DOWN] = 0;
	acs[UP] = 0.05f;
	onfloor_flg[num] = true;
	jump_flg = false;
}

void Player::TouchCeiling()
{
	acs[UP] = 0;
	touch_ceil_flg = true;
}

void Player::TouchRightWall()
{
	acs[RIGHT] = 0;
	rightwall_flg = true;
}

void Player::TouchLeftWall()
{
	acs[LEFT] = 0;
	leftwall_flg = true;
}


void Player::Push(int num,Location _sub_location, Erea _sub_erea)
{
	Location p_center = { 0 };
	p_center.x = location.x + (erea.width / 2);
	p_center.y = location.y + (erea.height / 2);

	//���ɐG�ꂽ��
	if (location.y +erea.height-12 < _sub_location.y)
	{
		location.y = _sub_location.y- erea.height;
		OnFloor(num, _sub_location);
	}
	//�V��ɐG�ꂽ��
	else if (location.y +20> _sub_location.y + _sub_erea.height)
	{
		location.y = _sub_location.y + _sub_erea.height;
		TouchCeiling();
	}
	//�E�̕ǂɐG�ꂽ��
	else if (location.x +erea.width-10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;
		TouchRightWall();
	}
	//���̕ǂɐG�ꂽ��
	else if (location.x+10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;
		TouchLeftWall();
	}
	//�ǂ����̕ǂɂ��G��Ă��Ȃ��Ƃ��̒n�ʂ��蔲���h�~
	else
	{
		location.y = _sub_location.y - erea.height;
		OnFloor(num, _sub_location);
	}
}

void Player::Reset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		external_move[i] = 0;
	}
}

void Player::MovePlayer(bool _direction, float _move)
{
	if (_direction == false)
	{
		external_move[RIGHT] += _move;
	}
	else
	{
		external_move[LEFT] += _move;
	}
}