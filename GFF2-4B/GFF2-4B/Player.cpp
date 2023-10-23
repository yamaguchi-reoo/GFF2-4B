#include "Player.h"
#include "PadInput.h"

#define ACS_MAX 6	//最大加速度
#define DOWN 0	//下加速度用
#define UP 1	//上加速度用
#define RIGHT 2	//右加速度用
#define LEFT 3	//左加速度用

#define DEFAULT_MOVE_SPEED 0.3f			//基本移動速度(左右)
#define DEFAULT_JUMP_POWER 26			//基本最大跳躍力
#define GRAVITY_POWER  (ACS_MAX * 2.5f) //重力の強さ

Player::Player()
{
	old_location = { 0 };
	location.x = 100;
	location.y = 400;
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	hp = 10;
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
	//床に触れていないなら
	if (apply_gravity == true)
	{
		GiveGravity();
	}

	//左移動
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

	//右移動
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
	//ジャンプ
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true && jump_flg == false)
	{
		acs[UP] = jump_power;
		jump_flg = true;
	}
	else
	{
		//ジャンプしていない時は上に加速する力を弱める
		DecAcs(UP);
	}
	//通常攻撃
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true)
	{
		main->SpawnAttack(CreateAttactData());
	}

	//1フレーム前の座標を保存
	old_location = location;
	//移動処理
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];
	//顔の方向処理
	if (old_location.x < location.x)
	{
		direction = false;
	}
	if (old_location.x > location.x)
	{
		direction = true;
	}
	Reset();
}

void Player::Draw()const
{
	SetFontSize(24);
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff0000, true);
	if (direction == false)
	{
		DrawBox(location.x+ erea.width-40, location.y+10, location.x + erea.width, location.y + 40, 0x00ff00, true);
	}
	else
	{
		DrawBox(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
	}
	//hp表示（仮）
	DrawBox(10, 10, 250, 60, 0x000000, true);
	DrawString(20, 12, "HP", 0xffffff);
	for (int i = 0; i < hp; i++)
	{
		DrawBox(20 + i * 21, 30, 40 + i * 21, 50, 0xff0000, true);
	}
	//デバッグ用表示
	for (int i = 0; i < 4; i++)
	{
		DrawFormatString(0, 100+i*30, 0x00ff00, "%f", acs[i]);/*
		DrawFormatString(200, 100+i*30, 0x00ff00, "%f", external_move[i]);*/
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
	if (acs[num] < 0)
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

	//床に触れた時
	if (location.y +erea.height-12 < _sub_location.y)
	{
		location.y = _sub_location.y- erea.height;
		OnFloor(num, _sub_location);
	}
	//天井に触れた時
	else if (location.y +20> _sub_location.y + _sub_erea.height)
	{
		location.y = _sub_location.y + _sub_erea.height;
		TouchCeiling();
	}
	//右の壁に触れた時
	else if (location.x +erea.width-10 < _sub_location.x)
	{
		location.x = _sub_location.x - erea.width;
		TouchRightWall();
	}
	//左の壁に触れた時
	else if (location.x+10 > _sub_location.x + _sub_erea.width)
	{
		location.x = _sub_location.x + _sub_erea.width;
		TouchLeftWall();
	}
	//どっちの壁にも触れていないときの地面すり抜け防止
	else
	{
		location.y = _sub_location.y - erea.height;
		OnFloor(num, _sub_location);
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
	for (int i = 0; i < 4; i++)
	{
		external_move[i] = 0;
	}
}

void Player::MovePlayer(ScrollData _scroll)
{
	if (_scroll.direction == true)
	{
		external_move[RIGHT] += _scroll.move;
	}
	else
	{
		external_move[LEFT] = _move;
	}
}

void Player::ApplyDamage(int num)
{
	hp -= num;
	if (hp < 0)
	{
		//仮にHPをリセットする
		hp = 5;
	}
}

AttackData Player::CreateAttactData()
{
	AttackData attack_data;
	attack_data.center_x = location.x + (erea.width/2);
	attack_data.center_y = location.y + (erea.height/2);
	attack_data.width = 100;
	attack_data.height = 100;
	attack_data.who_attack = false;
	attack_data.attack_time = 10;
	attack_data.direction = direction;		
	return attack_data;
}