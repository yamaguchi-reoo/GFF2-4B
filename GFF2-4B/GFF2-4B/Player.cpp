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
#define DEFAULT_ATTACK_INTERVAL	30		//��{�U���Ԋu(�t���[��)

#define PLAYER_IMAGE_SHIFT_X 75			//�摜���炵�p
#define PLAYER_IMAGE_SHIFT_Y 50			//�摜���炵�p
#define PLAYER_IDOL 0					//�����p�A�j���[�V�����J�n�n�_
#define PLAYER_WALK 1					//�ړ��A�j���[�V�����J�n�n�_
#define PLAYER_JUMP 4					//�W�����v�A�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_ONE 5				//�U���P�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_TWO 8				//�U���Q�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_THREE 11				//�U���R�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_FOUR 14				//�U���S�i�ڃA�j���[�V�����J�n�n�_

#define PLAYER_ANIM 10					//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j
Player::Player()
{
	frame = 0;
	player_state = IDOL_RIGHT;
	old_location = { 0 };
	location.x = 100;
	location.y = 400;
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	who = 0;
	hp = 10;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = DEFAULT_ATTACK_INTERVAL * 1.5f;
	attack_step = 0;
	attack_time = 0;
	for (int i = 0; i < 5; i++)
	{
		attack_motion_flg[i] = false;
	}
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
	move_flg = true;
	attack_anim_flg = false;
	LoadDivGraph("resource/images/PlayerAnimation.png", 17, 6, 3, 256, 256, player_image);
	player_anim = 0;
	attack_anim = 0;
	player_anim_speed = PLAYER_ANIM;
}

Player::~Player() 
{

}

void Player::Update(GameMain* main)
{
	frame++;
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
	//�A�j���[�V�����p�ϐ�����
	if (frame % player_anim_speed == 0)
	{
		if (++player_anim > 3)
		{
			player_anim = 0;
		}
	}
	attack_anim_flg = false;
	for (int i = 0; i < 5; i++)
	{
		//�����ꂩ�̍U�����s���Ă���Œ��Ȃ�t���O��true�ɂ���
		if (attack_motion_flg[i] == true)
		{
			attack_anim_flg = true;
		}
	}
	//�U���A�j���[�V�����p�ϐ�����
	if (attack_anim_flg == true)
	{
		if (frame % player_anim_speed == 0 && attack_anim < 3)
		{
			attack_anim++;
		}
	}
	//�U���A�j���[�V�����p�ϐ������Z�b�g
	else
	{
		attack_anim = 0;
	}
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
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(0, 100+i*30, 0x00ff00, "%d", attack_motion_flg[i]);/*
		DrawFormatString(200, 100+i*30, 0x00ff00, "%f", external_move[i]);*/
	}

	//�v���C���[�摜�\��
	DrawFormatString(location.x, location.y, 0x000000, "%d", player_state);
	switch (player_state)
	{
	case IDOL_RIGHT:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL],true);
		break;
	case IDOL_LEFT:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
		break;
	case MOVE_RIGHT:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK +walk_anim_num[player_anim]], true);
		break;
	case MOVE_LEFT:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y,player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
		break;
	case JUMP_RIGHT:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
		break;
	case JUMP_LEFT:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
		break;
	case FALL_RIGHT:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
		break;
	case FALL_LEFT:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
		break;
	case ATTACK_RIGHT_ONE:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_RIGHT_TWO:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_RIGHT_THREE:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_RIGHT_FOUR:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_LEFT_ONE:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_LEFT_TWO:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_LEFT_THREE:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
		break;
	case ATTACK_LEFT_FOUR:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
		break;
	case JUMP_ATTACK_RIGHT:
		DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[12], true);
		break;
	case JUMP_ATTACK_LEFT:
		DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[12], true);
		break;
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

void Player::ForciblyMovePlayer(ScrollData _scroll)
{
	if (_scroll.direction == true)
	{
		external_move[RIGHT] += (_scroll.move + acs[LEFT]);
	}
	else
	{
		external_move[LEFT] += (_scroll.move + acs[RIGHT]);
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

AttackData Player::CreateAttactData(int i)
{
	AttackData attack_data;
	//�ǂ̒i�K�̍U���ł��ς��Ȃ����͂����Ŋi�[����
	attack_data.x = location.x + (erea.width/2);
	attack_data.y = location.y + (erea.height/2);
	attack_data.who_attack = 0;
	attack_data.direction = direction;
	//�U���̒i�K�ɉ����Ċi�[�������ς���
	switch (i)
	{
		//�ʏ�P�i��
	case 0:
		attack_data.width = 100;
		attack_data.height = 100;
		attack_data.attack_time = 10;
		attack_data.damage = 1;
		attack_data.delay = 10;
		break;
		//�ʏ�Q�i��
	case 1:
		attack_data.width = 110;
		attack_data.height = 110;
		attack_data.attack_time = 10;
		attack_data.damage = 1;
		attack_data.delay = 10;
		break;
		//�ʏ�R�i��
	case 2:
		attack_data.width = 120;
		attack_data.height = 120;
		attack_data.attack_time = 10;
		attack_data.damage = 1;
		attack_data.delay = 10;
		break;
		//�ʏ�S�i��
	case 3:
		attack_data.width = 200;
		attack_data.height = 200;
		attack_data.attack_time = 10;
		attack_data.damage = 1;
		attack_data.delay = 10;
		break;
		//�W�����v�U��
	case 4:
		attack_data.width = 100;
		attack_data.height = 100;
		attack_data.attack_time = 2;
		attack_data.damage = 1;
		attack_data.delay = 0;
		break;
	}

	return attack_data;
}

void Player::SetPowerUp()
{
	powerup_flg = true;
	acs_max = ACS_MAX * 2;
	jump_power = DEFAULT_JUMP_POWER * 1.1;
	attack_interval = DEFAULT_ATTACK_INTERVAL / 2;
	player_anim_speed = PLAYER_ANIM / 2;
}

void Player::StopPowerUp()
{
	powerup_flg = false;
	acs_max = ACS_MAX;
	jump_power = DEFAULT_JUMP_POWER;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	player_anim_speed = PLAYER_ANIM;
}

void Player::Attack(GameMain* main)
{
	//�U��
	if (PadInput::OnButton(XINPUT_BUTTON_B) == true && attack_interval_count <= 0)
	{
		//�W�����v���łȂ��Ȃ�
		if (jump_flg == false)
		{
			//�U���Ԋu�̑�����J�n
			attack_interval_count = attack_interval;
			//�v���C���[���ړ��ł��Ȃ�����
			if (powerup_flg == false)
			{
				attack_time = 30;
			}
			else
			{
				attack_time = 15;
			}
			//���Ԋu���߂���O�ɍU�����s���Ă����Ȃ�
			if (ca_interval_count > 0)
			{
				//�ő�U���ł͂Ȃ��Ȃ�
				if (attack_step < 3)
				{
					attack_step++;
				}
			}
			//���Ԋu���߂�����
			else
			{
				//�U���̒i�K�����Z�b�g����
				attack_step = 0;
			}
			//�S�i�ڂ���������ɕK���P�i�ڂɖ߂�悤�ɂ���
			if (attack_step >= 3)
			{
				ca_interval_count = 0;
			}
			//����ȊO�̍U���̎��ɂ͐������Ԋu��ݒ肷��
			else
			{
				ca_interval_count = combo_attack_interval;
			}
			//�U���𐶐�����
			main->SpawnAttack(CreateAttactData(attack_step));
		}
		//�W�����v���Ȃ�
		else
		{
			//�W�����v�U�����s��
			attack_step = 4;
		}
	}
	//�U���Ԋu�p�ϐ�
	if (attack_interval_count > 0)
	{
		attack_interval_count--;
	}
	//�R���{�U���Ԋu�p�ϐ�(���̐��l���O�ȏ�̎��ɍU�����s���ƁA���̍U�����s��)
	if (ca_interval_count > 0)
	{
		ca_interval_count--;
	}
	//�U�����o�p
	//�W�����v�U���ȊO�Ȃ�
	if (attack_step != 4)
	{
		if (--attack_time > 0)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ���
			attack_motion_flg[attack_step] = true;
			move_flg = false;
		}
		else
		{
			//�s���Ă����U���̒i�K�ɉ������t���O��false�ɂ���
			attack_motion_flg[attack_step] = false;
			move_flg = true;
		}
	}
	//�W�����v�U���Ȃ�
	else
	{
		//�󒆂ɂ������U����������
		if (OnAnyFloorFlg() == false)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ���
			attack_motion_flg[attack_step] = true;
			//�U���𐶐�����
			main->SpawnAttack(CreateAttactData(attack_step));

		}
		//�n�ʂɂ�����U���I��
		else
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ���
			attack_motion_flg[attack_step] = false;
			//�U���i�K�����Z�b�g
			attack_step = 0;
		}
	}
}

void Player::Move()
{
	//���ړ�
	if (PadInput::TipLeftLStick(STICKL_X) <= -0.5 && move_flg == true)
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
	if (PadInput::TipLeftLStick(STICKL_X) >= 0.5 && move_flg == true)
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
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true && jump_flg == false && move_flg == true)
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
			if (jump_flg == true && acs[UP] >= acs[DOWN])
			{
				player_state = JUMP_RIGHT;
			}
		}
		//�d�͂�������Ă��Ȃ��i�n�ʂɂ���Ȃ�j
		else
		{
			player_state = IDOL_RIGHT;
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
		//�U�����Ȃ�
		if (attack_motion_flg[0] == true)
		{
			player_state = ATTACK_RIGHT_ONE;
		}
		if (attack_motion_flg[1] == true)
		{
			player_state = ATTACK_RIGHT_TWO;
		}
		if (attack_motion_flg[2] == true)
		{
			player_state = ATTACK_RIGHT_THREE;
		}
		if (attack_motion_flg[3] == true)
		{
			player_state = ATTACK_RIGHT_FOUR;
		}
		if (attack_motion_flg[4] == true)
		{
			player_state = JUMP_ATTACK_RIGHT;
		}
	}
	//������
	else
	{
		//�d�͂�������Ă���Ȃ�
		if (apply_gravity == true)
		{
			player_state = FALL_LEFT;
			if (jump_flg == true && acs[UP] >= acs[DOWN])
			{
				player_state = JUMP_LEFT;
			}
		}
		//�d�͂�������Ă��Ȃ��i�n�ʂɂ���Ȃ�j
		else
		{
			player_state = IDOL_LEFT;
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
		//�U�����Ȃ�
		if (attack_motion_flg[0] == true)
		{
			player_state = ATTACK_LEFT_ONE;
		}
		if (attack_motion_flg[1] == true)
		{
			player_state = ATTACK_LEFT_TWO;
		}
		if (attack_motion_flg[2] == true)
		{
			player_state = ATTACK_LEFT_THREE;
		}
		if (attack_motion_flg[3] == true)
		{
			player_state = ATTACK_LEFT_FOUR;
		}
		if (attack_motion_flg[4] == true)
		{
			player_state = JUMP_ATTACK_LEFT;
		}
	}
}

bool Player::OnAnyFloorFlg()
{
	bool ret = false;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//�G��Ă��鏰������΃��[�v�𔲂���
		if (onfloor_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}