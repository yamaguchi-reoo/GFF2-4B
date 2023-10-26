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
#define DEFAULT_INVINCIBLE_TIME	80		//��{���G����(�U������������)

#define PLAYER_IMAGE_SHIFT_X 80			//�摜���炵�p
#define PLAYER_IMAGE_SHIFT_Y 105		//�摜���炵�p
#define PLAYER_IDOL 0					//�����p�A�j���[�V�����J�n�n�_
#define PLAYER_WALK 1					//�ړ��A�j���[�V�����J�n�n�_
#define PLAYER_JUMP 4					//�W�����v�A�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_ONE 5				//�U���P�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_TWO 8				//�U���Q�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_THREE 11			//�U���R�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_ATTACK_FOUR 14			//�U���S�i�ڃA�j���[�V�����J�n�n�_
#define PLAYER_JUMP_ATTACK 12			//�W�����v�U���A�j���[�V�����J�n�n�_
#define PLAYER_JUMP_ATTACK_END 16		//�W�����v�U���i���n�j�A�j���[�V�����J�n�n�_
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
	for (int i = 0; i < ATTACK_NUM; i++)
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
	SetPlayerAttackData();
	LoadDivGraph("resource/images/PlayerAnimation.png", 18, 6, 3, 256, 256, player_image);
	player_anim = 0;
	attack_anim = 0;
	player_anim_speed = PLAYER_ANIM;
	inv_flg = false;
	damage_flg = false;
	inv_time = DEFAULT_INVINCIBLE_TIME;
	damage_time = DEFAULT_INVINCIBLE_TIME / 2;
	hidden_flg = true;
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

	//�U��
	Attack(main);

	//�_���[�W���o���Ȃ�
	if (inv_flg == true)
	{
		damage_flg = true;
		if (--damage_time < 0)
		{
			damage_flg = false;
		}
		//���G���Ԃ��I�������
		if (--inv_time < 0)
		{
			inv_flg = false;
			inv_time = DEFAULT_INVINCIBLE_TIME;
			damage_time = DEFAULT_INVINCIBLE_TIME / 2;
		}
	}

	//�����ꂩ�̍U�����������Ă��邩�A�_���[�W���󂯂Ă���r���Ȃ�
	if (PlayAnyAttack() == true || damage_flg == true)
	{
		//�����Ȃ�����
		move_flg = false;
	}
	//�ǂ���ł��Ȃ��Ȃ�
	else
	{
		//������悤�ɂ���
		move_flg = true;
	}

	//�ړ�����
	Move();

	//�v���C���[�̏�Ԃ��X�V����
	UpdatePlayerState();


	//�e�ړ��p�ϐ������Z�b�g
	Reset();

	//�`��֘A�̕ϐ��𓮂���
	Anim();
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
		DrawFormatString(0, 100+i*30, 0x00ff00, "%d", attack_motion_flg[i]);
	}
	DrawFormatString(360, 360, 0xfffff0, "HP %d", hp);
	DrawFormatString(360, 380, 0xfffff0, "direction %d", direction);

	//�v���C���[�摜�\��
	if (hidden_flg == true)
	{
		switch (player_state)
		{
		case IDOL_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case IDOL_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case MOVE_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
			break;
		case MOVE_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
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
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_RIGHT_END:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case JUMP_ATTACK_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_LEFT_END:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case DAMAGE_RIGHT:
			DrawGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		case DAMAGE_LEFT:
			DrawTurnGraph(location.x - PLAYER_IMAGE_SHIFT_X, location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		}
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
	//���G��ԂłȂ��Ȃ�
	if (inv_flg == false)
	{
		//�̂�����
		acs[UP] += 10;
		acs[!direction + 2] += 10; //�������̊炪�����Ă�������Ƌt������
		//�̗͂����炷
		hp -= num;
		if (hp < 0)
		{
			//����HP�����Z�b�g����
			hp = 5;
		}
		//�_���[�W��̖��G��Ԃɓ���
		inv_flg = true;
	}
}

AttackData Player::CreateAttactData(int i)
{
	AttackData attack_data;
	attack_data = player_attack_data[i * 2 + powerup_flg];
	//�����̏u�Ԃɉ����ĕς����͂����Ŋi�[����
	attack_data.direction = direction;
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
		//�󒆂ɋ��Ȃ��Ȃ�
		if (acs[DOWN] == 0)
		{
			//�U���Ԋu�̑�����J�n
			attack_interval_count = attack_interval;
			//�v���C���[���ړ��ł��Ȃ�����
			if (powerup_flg == false)
			{
				attack_time = DEFAULT_ATTACK_INTERVAL;
			}
			else
			{
				attack_time = DEFAULT_ATTACK_INTERVAL/2;
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
		//�󒆂ɂ���Ȃ�
		else
		{
			//�����U�����s��
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
	//�����U���ȊO�Ȃ�
	switch (attack_step)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		if (--attack_time > 0)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ���
			attack_motion_flg[attack_step] = true;
		}
		else
		{
			//�s���Ă����U���̒i�K�ɉ������t���O��false�ɂ���
			attack_motion_flg[attack_step] = false;
		}
		break;
	case 4:
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
			//�����U���̃t���O��false�ɂ���
			attack_motion_flg[4] = false;
			//���n�U���̔���
			attack_step = 5;
			main->SpawnAttack(CreateAttactData(attack_step));
			//�v���C���[���ړ��ł��Ȃ�����
			if (powerup_flg == false)
			{
				attack_time = DEFAULT_ATTACK_INTERVAL;
			}
			else
			{
				attack_time = DEFAULT_ATTACK_INTERVAL / 2;
			}
		}
		break;
	case 5:
		if (--attack_time > 0)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ���
			attack_motion_flg[attack_step] = true;
		}
		else
		{
			//�s���Ă����U���̒i�K�ɉ������t���O��false�ɂ���
			attack_motion_flg[attack_step] = false;
		}
		break;
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
	//��̕�������
	if (acs[LEFT] < acs[RIGHT] && move_flg == true)
	{
		direction = false;
	}
	if (acs[LEFT] > acs[RIGHT] && move_flg == true)
	{
		direction = true;
	}
	
	//1�t���[���O�̍��W��ۑ�
	old_location = location;
	//�ړ�����
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];
}

void Player::Anim()
{
	//�A�j���[�V�����p�ϐ�����
	if (frame % player_anim_speed == 0)
	{
		if (++player_anim > 3)
		{
			player_anim = 0;
		}
	}
	//�U���A�j���[�V�����p�ϐ�����
	if (PlayAnyAttack() == true)
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
	//���G���Ԓ��Ȃ�
	if (inv_flg == true)
	{
		//5�t���[������
		if (frame % 5 == 0)
		{
			//�\�����邩���Ȃ�����؂�ւ���
			hidden_flg = !hidden_flg;
		}
	}
	//���G���ԂłȂ��Ȃ�
	else
	{
		//��ɉ摜�\����Ԃ�
		hidden_flg = true;
	}
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
		if (attack_motion_flg[5] == true)
		{
			player_state = JUMP_ATTACK_RIGHT_END;
		}
		//�_���[�W����������ԂȂ�
		if (damage_flg == true)
		{
			player_state = DAMAGE_RIGHT;
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
		if (attack_motion_flg[5] == true)
		{
			player_state = JUMP_ATTACK_LEFT_END;
		}

		//�_���[�W����������ԂȂ�
		if (damage_flg == true)
		{
			player_state = DAMAGE_LEFT;
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

bool Player::PlayAnyAttack()
{
	bool ret = false;
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�����ꂩ�̍U�����s���Ă���Œ��Ȃ�t���O��true�ɂ���
		if (attack_motion_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}

void Player::SetPlayerAttackData()
{
	//��i�K�ځ@
	player_attack_data[0].shift_x = -erea.width;
	player_attack_data[0].shift_y = -50;
	player_attack_data[0].width = erea.width + 100;
	player_attack_data[0].height = 200;
	player_attack_data[0].who_attack = 0;
	player_attack_data[0].attack_time = 10;
	player_attack_data[0].damage = 1;
	player_attack_data[0].delay = 10;
	//��i�K�ځ@������
	player_attack_data[1].shift_x = -erea.width;
	player_attack_data[1].shift_y = -50;
	player_attack_data[1].width = erea.width + 110;
	player_attack_data[1].height = 220;
	player_attack_data[1].who_attack = 0;
	player_attack_data[1].attack_time = 5;
	player_attack_data[1].damage = 3;
	player_attack_data[1].delay = 5;
	//��i�K��
	player_attack_data[2].shift_x = -erea.width;
	player_attack_data[2].shift_y = -70;
	player_attack_data[2].width = erea.width + 100;
	player_attack_data[2].height = 210;
	player_attack_data[2].who_attack = 0;
	player_attack_data[2].attack_time = 10;
	player_attack_data[2].damage = 1;
	player_attack_data[2].delay = 10;
	//��i�K�ځ@������
	player_attack_data[3].shift_x = -erea.width;
	player_attack_data[3].shift_y = -70;
	player_attack_data[3].width = erea.width + 120;
	player_attack_data[3].height = 230;
	player_attack_data[3].who_attack = 0;
	player_attack_data[3].attack_time = 5;
	player_attack_data[3].damage = 3;
	player_attack_data[3].delay = 5;
	//�O�i�K��
	player_attack_data[4].shift_x = -erea.width;
	player_attack_data[4].shift_y = 50;
	player_attack_data[4].width = erea.width + 170;
	player_attack_data[4].height = 100;
	player_attack_data[4].who_attack = 0;
	player_attack_data[4].attack_time = 10;
	player_attack_data[4].damage = 1;
	player_attack_data[4].delay = 5;
	//�O�i�K�ځ@������
	player_attack_data[5].shift_x = -erea.width;
	player_attack_data[5].shift_y = 40;
	player_attack_data[5].width = erea.width + 250;
	player_attack_data[5].height = 110;
	player_attack_data[5].who_attack = 0;
	player_attack_data[5].attack_time = 10;
	player_attack_data[5].damage = 1;
	player_attack_data[5].delay = 5;
	//�l�i�K��
	player_attack_data[6].shift_x = -erea.width;
	player_attack_data[6].shift_y = -90;
	player_attack_data[6].width = erea.width + 150;
	player_attack_data[6].height = 200;
	player_attack_data[6].who_attack = 0;
	player_attack_data[6].attack_time = 10;
	player_attack_data[6].damage = 1;
	player_attack_data[6].delay = 10;
	//�l�i�K�ځ@������
	player_attack_data[7].shift_x = -erea.width;
	player_attack_data[7].shift_y = -90;
	player_attack_data[7].width = erea.width + 200;
	player_attack_data[7].height = 200;
	player_attack_data[7].who_attack = 0;
	player_attack_data[7].attack_time = 10;
	player_attack_data[7].damage = 1;
	player_attack_data[7].delay = 10;
	//�W�����v�U��
	player_attack_data[8].shift_x = -erea.width;
	player_attack_data[8].shift_y = 50;
	player_attack_data[8].width = erea.width+100;
	player_attack_data[8].height = 100;
	player_attack_data[8].who_attack = 0;
	player_attack_data[8].attack_time = 2;
	player_attack_data[8].damage = 1;
	player_attack_data[8].delay = 0;
	//�W�����v�U���@������
	player_attack_data[9].shift_x = 0;
	player_attack_data[9].shift_y = 50;
	player_attack_data[9].width = 100;
	player_attack_data[9].height = 150;
	player_attack_data[9].who_attack = 0;
	player_attack_data[9].attack_time = 2;
	player_attack_data[9].damage = 1;
	player_attack_data[9].delay = 0;
	//�W�����v�U������̒��n�U��
	player_attack_data[10].shift_x = 0;
	player_attack_data[10].shift_y = 50;
	player_attack_data[10].width = 200;
	player_attack_data[10].height = 100;
	player_attack_data[10].who_attack = 0;
	player_attack_data[10].attack_time = 10;
	player_attack_data[10].damage = 2;
	player_attack_data[10].delay = 0;
	//�W�����v�U������̒��n�U���@�����p
	player_attack_data[11].shift_x = 0;
	player_attack_data[11].shift_y = 50;
	player_attack_data[11].width = 250;
	player_attack_data[11].height = 100;
	player_attack_data[11].who_attack = 0;
	player_attack_data[11].attack_time = 5;
	player_attack_data[11].damage = 2;
	player_attack_data[11].delay = 0;
}