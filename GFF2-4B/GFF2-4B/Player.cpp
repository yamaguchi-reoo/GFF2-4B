#include "Player.h"
#include "PadInput.h"

#define ACS_MAX 10	//�ő�����x
#define DOWN 0	//�������x�p
#define UP 1	//������x�p
#define RIGHT 2	//�E�����x�p
#define LEFT 3	//�������x�p

Player::Player()
{
	location.x = 100;
	location.y = 400;
	erea.height = 100;
	erea.width = 50;
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
	}
	onfloor_flg = false;
}

Player::~Player() 
{

}

void Player::Update()
{
	//���ɐG��Ă��Ȃ��Ȃ�
	if (onfloor_flg == false)
	{
		GiveGravity();
	}
	//���ړ�
	if (PadInput::TipLeftLStick(STICKL_X) <= 0.5)
	{
		if (acs[LEFT] <= ACS_MAX)
		{
			acs[LEFT] += 0.2f;
		}
	}
	else
	{
		DecAcs(LEFT);
	}
	//�E�ړ�
	if (PadInput::TipLeftLStick(STICKL_X) >= -0.5)
	{	
		if (acs[RIGHT] <= ACS_MAX)
		{
			acs[RIGHT] += 0.2f;
		}
	}
	else
	{
		DecAcs(RIGHT);
	}
	//�W�����v
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true)
	{
		acs[UP] = 15;
	}
	//�ʏ�U��
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true)
	{
	}

	//�ړ�����
	location.x = location.x - acs[LEFT] + acs[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN];
	DecAcs(UP);
}

void Player::Draw()const
{
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff0000, true);

}

void Player::GiveGravity()
{
	if (acs[DOWN] <= ACS_MAX)
	{
		acs[DOWN] += 0.2f;
	}
}

void Player::DecAcs(int num)
{
	if (acs[num] > 0)
	{
		acs[num] -= 0.4f;
	}
}

void Player::OnFloor()
{
	acs[DOWN] = 0;
	acs[UP] = 0;
	onfloor_flg = true;
}

void Player::NotOnFloor()
{
	onfloor_flg = false;
}

void Player::Push(int num)
{
	acs[num] += 10;
}