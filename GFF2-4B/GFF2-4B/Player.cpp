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
	erea.height = 150;
	erea.width = 75;
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
	}
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
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

	Reset();

	//左移動
	if (PadInput::TipLeftLStick(STICKL_X) <= 0.5)
	{
		if (acs[LEFT] <= ACS_MAX && rightwall_flg == false)
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
		if (acs[RIGHT] <= ACS_MAX && leftwall_flg == false)
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
		acs[UP] = 17;
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
		acs[num] -= 0.8f;
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
	Location p_center;
	p_center.x = location.x + (erea.width / 2);
	p_center.y = location.y + (erea.height / 2);

	if (location.y +erea.height-10 < _sub_location.y)
	{
		location.y = _sub_location.y- erea.height;
		OnFloor(num, _sub_location);
	}
	if(location.y - erea.height + 10 > _sub_location.y)
	{
		location.y = _sub_location.y + erea.height;
		TouchCeiling();
	}
	if (p_center.x < _sub_location.x)
	{
		if (onfloor_flg[num] == false && touch_ceil_flg == false)
		{
			location.x = _sub_location.x - erea.width;
			TouchRightWall();
		}
	}
	else
	{
		if (onfloor_flg[num] == false && touch_ceil_flg == false)
		{
			location.x = _sub_location.x + _sub_erea.width;
			TouchLeftWall();
		}
	}
}

void Player::Reset()
{
	//重力が働くかの判定をリセット
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
}