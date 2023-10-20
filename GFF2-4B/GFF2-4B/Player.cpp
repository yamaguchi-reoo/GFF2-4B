#include "Player.h"
#include "PadInput.h"

#define ACS_MAX 10	//最大加速度
#define DOWN 0	//下加速度用
#define UP 1	//上加速度用
#define RIGHT 2	//右加速度用
#define LEFT 3	//左加速度用

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
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	apply_gravity = true;
}

Player::~Player() 
{

}

void Player::Update()
{
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		if (onfloor_flg[i] == true)
		{
			apply_gravity = false;
		}
	}
	//床に触れていないなら
	if (apply_gravity == true)
	{
		GiveGravity();
	}
	//重力が働くかの判定をリセット
	apply_gravity = true;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	//左移動
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
	//右移動
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
	//ジャンプ
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true)
	{
		acs[UP] = 15;
	}
	//通常攻撃
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true)
	{
	}

	//移動処理
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

void Player::OnFloor(int num)
{
	acs[DOWN] = 0;
	acs[UP] = 0;
	onfloor_flg[num] = true;
}

void Player::NotOnFloor(int num)
{
	onfloor_flg[num] = false;
}

void Player::TouchCeiling(int num)
{
	acs[DOWN] = 10;
}

void Player::Push(int num,Location _sub)
{
	Location p_center;
	p_center.x = location.x + (erea.width / 2);
	p_center.y = location.y + (erea.height / 2);

	if (_sub.x != 0 && _sub.y != 0)
	{
		if (p_center.y < _sub.y)
		{
			OnFloor(num);
		}
		else
		{
			TouchCeiling(num);
		}
	}
	else
	{
		NotOnFloor(num);
	}
}