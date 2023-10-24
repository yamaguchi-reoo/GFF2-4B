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
#define DEFAULT_ATTACK_INTERVAL	60		//��{�U���Ԋu(�t���[��)

Player::Player()
{
	player_state = IDOL_RIGHT;
	old_location = { 0 };
	location.x = 100;
	location.y = 400;
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	hp = 10;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	attack_interval_count = 0;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	attack_step = 0;
	attack_time = 0;
	attack_motion_flg = false;
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	acs_max = ACS_MAX;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		onfloor_flg[i] = false;
	}
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
	powerup_flg = false;
}

Player::~Player() 
{

}

void Player::Update(GameMain* main)
{
	//�d�͂������邩�̏���
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
		//�d�͂�^����
		GiveGravity();
	}

	//�ړ�����
	Move();
	//�U��
	Attack(main);

	//�����e�X�g�p
	if (PadInput::OnButton(XINPUT_BUTTON_X) == true)
	{
		SetPowerUp();
	}
	//�����e�X�g�p
	if (PadInput::OnButton(XINPUT_BUTTON_Y) == true)
	{
		StopPowerUp();
	}

	//��̕�������
	if (acs[LEFT] < acs[RIGHT])
	{
		direction = false;
	}
	if (acs[LEFT] > acs[RIGHT])
	{
		direction = true;
	}
	//�v���C���[�̏�Ԃ��X�V����
	UpdatePlayerState();
	//�e�ړ��p�ϐ������Z�b�g
	Reset();
}

void Player::Draw()const
{
	SetFontSize(24);
	//������ԂłȂ��Ȃ�
	if (powerup_flg == false)
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff0000, true);
		//��̌���
		if (direction == false)
		{
			DrawBox(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
		}
		else
		{
			DrawBox(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
		}
	}
	else
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, true);
		//��̌���
		if (direction == false)
		{
			DrawBox(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0xff0000, true);
		}
		else
		{
			DrawBox(location.x + 40, location.y + 10, location.x, location.y + 40, 0xff0000, true);
		}
	}

	//�f�o�b�O�p�\��
	for (int i = 0; i < 4; i++)
	{
		DrawFormatString(0, 100+i*30, 0x00ff00, "%f", acs[i]);/*
		DrawFormatString(200, 100+i*30, 0x00ff00, "%f", external_move[i]);*/
	}
	DrawFormatString(location.x, location.y, 0x000000, "%d", player_state);

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

	//���ɐG�ꂽ��
	if (location.y +erea.height-12 < _sub_location.y)
	{
		location.y = _sub_location.y- erea.height+0.1f;
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

void Player::ForciblyMovePlayer(bool _direction, float _move)
{
	if (_direction == false)
	{
		external_move[RIGHT] = _move;
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
		//����HP�����Z�b�g����
		hp = 5;
	}
}

AttackData Player::CreateAttactData()
{
	AttackData attack_data;
	attack_data.x = location.x + (erea.width/2);
	attack_data.y = location.y + (erea.height/2);
	attack_data.width = 100;
	attack_data.height = 100;
	attack_data.who_attack = PLAYER;
	attack_data.attack_time = 10;
	attack_data.direction = direction;	
	attack_data.damage = 1;
	return attack_data;
}

void Player::SetPowerUp()
{
	powerup_flg = true;
	acs_max = ACS_MAX * 2;
	jump_power = DEFAULT_JUMP_POWER * 1.1;
	attack_interval = DEFAULT_ATTACK_INTERVAL / 2;
}

void Player::StopPowerUp()
{
	powerup_flg = false;
	acs_max = ACS_MAX;
	jump_power = DEFAULT_JUMP_POWER;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
}

void Player::Attack(GameMain* main)
{
	//�U��
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true && attack_interval_count <= 0)
	{
		//�W�����v���łȂ��Ȃ�
		if (jump_flg == false)
		{
			main->SpawnAttack(CreateAttactData());
			attack_interval_count = attack_interval;
			attack_time = 10;
		}
		//�W�����v���Ȃ�
		else
		{

		}
	}
	//�U���Ԋu�p�ϐ�
	if (attack_interval_count > 0)
	{
		attack_interval_count--;
	}
	//�U�����o�p
	if (--attack_time > 0)
	{
		attack_motion_flg = true;
	}
	else
	{
		attack_motion_flg = false;
	}
}

void Player::Move()
{
	//���ړ�
	if (PadInput::TipLeftLStick(STICKL_X) <= -0.5)
	{
		if (acs[LEFT] <= acs_max && rightwall_flg == false)
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
		if (acs[RIGHT] <= acs_max && leftwall_flg == false)
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

	//1�t���[���O�̍��W��ۑ�
	old_location = location;
	//�ړ�����
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];
}

void Player::UpdatePlayerState()
{
	//��̌����ɂ���ĕς���
	//�E����
	if (direction == false)
	{
		//�d�͂�������Ă���Ȃ�
		if (apply_gravity == true)
		{
			player_state = FALL_RIGHT;
		}
		//�d�͂�������Ă��Ȃ��i�n�ʂɂ���Ȃ�j
		else
		{
			player_state = IDOL_RIGHT;
		}
		//�U�����Ȃ�
		if (attack_motion_flg == true)
		{
			player_state = ATTACK_RIGHT_ONE;
		}
	}
	//������
	else
	{
		//�d�͂�������Ă���Ȃ�
		if (apply_gravity == true)
		{
			player_state = FALL_LEFT;
		}
		//�d�͂�������Ă��Ȃ��i�n�ʂɂ���Ȃ�j
		else
		{
			player_state = IDOL_LEFT;
		}
		//�U�����Ȃ�
		if (attack_motion_flg == true)
		{
			player_state = ATTACK_LEFT_ONE;
		}
	}
	//�E�Ɉړ����Ă���Ȃ�
	if (acs[LEFT] < acs[RIGHT])
	{
		player_state = MOVE_RIGHT;
	}
	//���Ɉړ����Ă���Ȃ�
	if (acs[LEFT] > acs[RIGHT])
	{
		player_state = MOVE_LEFT;
	}
}