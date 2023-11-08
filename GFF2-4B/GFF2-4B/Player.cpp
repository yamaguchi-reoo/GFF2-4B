#include "Player.h"
#include "PadInput.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ACS_MAX 6	//�ő�����x
#define DOWN 0	//�������x�p
#define UP 1	//������x�p
#define RIGHT 2	//�E�����x�p
#define LEFT 3	//�������x�p

#define DEFAULT_MOVE_SPEED 0.3f			//��{�ړ����x(���E)
#define DEFAULT_JUMP_POWER 28			//��{�ő咵����
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
#ifdef _DEBUG
	d_inv_flg = false;
#endif
	frame = 0;
	old_location = { 0 };
	location.x = 100;
	location.y = 400;
	erea.height = PLAYER_HEIGHT;
	erea.width = PLAYER_WIDTH;
	who = 0;
	hp = 5;
	move_speed = DEFAULT_MOVE_SPEED;
	jump_power = DEFAULT_JUMP_POWER;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = (int)(DEFAULT_ATTACK_INTERVAL * 1.5f);
	attack_step = 0;
	attack_time = DEFAULT_ATTACK_INTERVAL;
	attack_time_count = 0;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		attack_motion_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	acs_max = ACS_MAX;
	onfloor_flg = false;
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
	hidden_flg = false;
	death_flg = false;
	death_time = 120;
}

Player::~Player() 
{
	
}

void Player::Update(GameMain* main)
{
	//���G��Ԃ̐؂�ւ��i�f�o�b�O�p�j
#ifdef _DEBUG
	if (KeyInput::OnKey(KEY_INPUT_Q) == true)
	{
		d_inv_flg = !d_inv_flg;
	}
#endif
	frame++;
	//�����Ă���Ȃ�d�́A�_���[�W�A�U���֘A�̏������s��
	if (death_flg == false)
	{

		//�_���[�W���󂯂Ă���r���łȂ��Ȃ�
		if (damage_flg == false)
		{
			//�U��
			Attack(main);
		}

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
	}
	//����ł���Ȃ玀�S���Ԃ̑���
	else
	{
		if (--death_time <= 0)
		{
			//���ɉ��o���I������炷���Ƀ��X�|�[������悤�ɂ���
			Location res_location = { 100,100 };
			Respawn(res_location);
			//�J�����̃��Z�b�g
			main->ResetCamera();
		}
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
	//�v���C���[�摜�\��
	if (hidden_flg == false)
	{
		switch (player_state)
		{
		case IDOL_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case IDOL_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_IDOL], true);
			break;
		case MOVE_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
			break;
		case MOVE_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_WALK + walk_anim_num[player_anim]], true);
			break;
		case JUMP_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case JUMP_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case FALL_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP], true);
			break;
		case ATTACK_RIGHT_ONE:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_TWO:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_THREE:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_RIGHT_FOUR:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_ONE:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_ONE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_TWO:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_TWO + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_THREE:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_THREE + attack_anim_num[attack_anim]], true);
			break;
		case ATTACK_LEFT_FOUR:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_ATTACK_FOUR + attack_anim_num[attack_anim]], true);
			break;
		case JUMP_ATTACK_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_RIGHT_END:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case JUMP_ATTACK_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK], true);
			break;
		case JUMP_ATTACK_LEFT_END:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[PLAYER_JUMP_ATTACK_END], true);
			break;
		case DAMAGE_RIGHT:
			DrawGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		case DAMAGE_LEFT:
			DrawTurnGraphF(local_location.x - PLAYER_IMAGE_SHIFT_X, local_location.y - PLAYER_IMAGE_SHIFT_Y, player_image[17], true);
			break;
		case DEATH_RIGHT:
			DrawRotaGraphF(local_location.x + PLAYER_IMAGE_SHIFT_X, local_location.y + PLAYER_IMAGE_SHIFT_Y * 1.5f , 1, M_PI / 2, player_image[17], true);
			break;
		case DEATH_LEFT:
			DrawRotaGraphF(local_location.x + PLAYER_IMAGE_SHIFT_X, local_location.y + PLAYER_IMAGE_SHIFT_Y * 1.5f , 1, M_PI / 2, player_image[17], true);
			break;
		default:
			DrawStringF(local_location.x, local_location.y, "no image", 0xff0000);
			break;
		}
	}

	//�f�o�b�O�p�\��
#if DEBUG
	//�����蔻��\��
	//������ԂłȂ��Ȃ�
	if (powerup_flg == false)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xff0000, false);
	}
	//������ԂȂ�
	else
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffff00, false);
	}
	int old_size = GetFontSize();	//���̃T�C�Y��ێ�
	SetFontSize(14);
	DrawBox(0, 200, 260, 400, 0x000000, true);
	DrawBox(0, 200, 260, 400, 0xffffff, false);
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "�U��%d�i�K��:%d", i + 1, attack_motion_flg[i]);
			break;
		case 1:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "�U��%d�i�K��:%d", i + 1, attack_motion_flg[i]);
			break;
		case 2:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "�U��%d�i�K��:%d", i + 1, attack_motion_flg[i]);
			break;
		case 3:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "�U��%d�i�K��:%d", i + 1, attack_motion_flg[i]);
			break;
		case 4:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "�W�����v�U��:%d", attack_motion_flg[i]);
			break;
		case 5:
			DrawFormatString(0, 200 + i * 15, 0xffffff, "���n�U��:%d", attack_motion_flg[i]);
			break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "�������x:%f", acs[i]);
			break;
		case 1:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "������x:%f", acs[i]);
			break;
		case 2:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "�E�����x:%f", acs[i]);
			break;
		case 3:
			DrawFormatString(0, 320 + i * 15, 0xffffff, "�������x:%f", acs[i]);
			break;
		}
	}
	DrawFormatString(0, 290, 0xffffff, "HP %d", hp);
	if (direction == false)
	{
		DrawFormatString(0, 305, 0xffffff, "��̌���:�E", direction);
	}
	else
	{
		DrawFormatString(0, 305, 0xffffff, "��̌���:��", direction);
	}
	DrawFormatString(0, 380, 0xffffff, "���:%s", player_state_char[player_state]);
	DrawFormatString(110, 200, 0xffffff, "Q=�f�o�b�O�p���G:%d", d_inv_flg);
	SetFontSize(old_size);
#endif // DEBUG
}

void Player::GiveGravity()
{
	if (acs[DOWN] <= GRAVITY_POWER)
	{
		acs[DOWN] += (1.5f + (float)powerup_flg);
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

void Player::OnFloor()
{
	acs[DOWN] = 0;
	acs[UP] = 0.05f;
	onfloor_flg = true;
	jump_flg = false;
}

void Player::Push(int num,Location _sub_location, Erea _sub_erea ,int _type)
{
	Location p_center = { 0 };
	p_center.x = location.x + (erea.width / 2);
	p_center.y = location.y + (erea.height / 2);

	//�E�̕ǂɐG�ꂽ��
	if (location.x + erea.width - 10 < _sub_location.x && location.y + erea.height - 10 > _sub_location.y && _type != 2 && _type != 4)
	{
		location.x = _sub_location.x - erea.width;
		//�E�����x��0�ɂ���
		acs[RIGHT] = 0;
		//�E�̕ǂɐG�ꂽ�t���O�𗧂Ă�
		rightwall_flg = true;
	}
	//���̕ǂɐG�ꂽ��
	else if (location.x + 10 > _sub_location.x + _sub_erea.width && location.y + erea.height - 10 > _sub_location.y && _type != 2 && _type != 4)
	{
		location.x = _sub_location.x + _sub_erea.width;
		//�������x��0�ɂ���
		acs[LEFT] = 0;
		//���̕ǂɐG�ꂽ�t���O�𗧂Ă�
		leftwall_flg = true;
	}
	//���ɐG�ꂽ��
	else if (location.y + erea.height - 30 < _sub_location.y)
	{
		//�؂Ɖ_�͏ォ��~��Ă����Ƃ���������悤�ɂ���
		if ((_type != 2 && acs[DOWN] - acs[UP] >= 0) || (_type != 4 && acs[DOWN] - acs[UP] >= 0))
		{
			location.y = _sub_location.y - erea.height + 0.1f;
			OnFloor();
		}
	}
	//�V��ɐG�ꂽ��
	else if (location.y + 30 > _sub_location.y + _sub_erea.height && _type != 2 && _type != 4)
	{
		location.y = _sub_location.y + _sub_erea.height;
		//������x��0�ɂ���
		acs[UP] = 0;
		//�V��ɐG�ꂽ�t���O�𗧂Ă�
		touch_ceil_flg = true;
	}
	//�ǂ����̕ǂɂ��G��Ă��Ȃ��Ƃ��̒n�ʂ��蔲���h�~
	//else
	//{
	//	if (onfloor_flg == true)
	//	{
	//		location.y = _sub_location.y - erea.height;
	//		OnFloor();
	//	}
	//	else
	//	{
	//		location.y = _sub_location.y + _sub_erea.height;
	//	}
	//}
}

void Player::Reset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
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
	//���G��ԂłȂ�������ł����ԂłȂ��A�f�o�b�O�p�̖��G��ԂłȂ��Ȃ�
	if (inv_flg == false && death_flg == false 
#ifdef _DEBUG
		&& d_inv_flg == false
#endif
		){
		//�̂�����
		acs[UP] += 10;
		acs[!direction + 2] += 10; //�������̊炪�����Ă�������Ƌt������
		//�̗͂����炷
		hp -= num;
		if (hp < 0)
		{
			//����HP�����Z�b�g����
			/*hp = 5;*/
			//��
			death_flg = true;
			move_flg = false;
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
	//�U���̊p�x����̌����ɉ����ĕς���
	if (attack_data.attack_type == BULLET)
	{
		if (direction == false)
		{
			attack_data.angle = player_attack_data[i * 2 + powerup_flg].angle;
		}
		else
		{
			attack_data.angle = 0.5f - player_attack_data[i * 2 + powerup_flg].angle;
		}
	}
	return attack_data;
}

void Player::SetPowerUp()
{
	powerup_flg = true;								
	acs_max = ACS_MAX * 2;							//�ő�����x��2�{
	jump_power = DEFAULT_JUMP_POWER * 1.2f;			//�����͂�1.2�{
	attack_interval = DEFAULT_ATTACK_INTERVAL / 2;	//�U���Ԋu�𔼕���
	combo_attack_interval = DEFAULT_ATTACK_INTERVAL;//�A���U����t���Ԃ𔼕���
	player_anim_speed = PLAYER_ANIM / 2;			//�A�j���[�V�����؂�ւ��Ԋu���{
	attack_time = DEFAULT_ATTACK_INTERVAL / 2;		//�v���C���[�������Ȃ����Ԃ𔼕���
}

void Player::StopPowerUp()
{
	powerup_flg = false;
	//SetPowerUp�ŕύX�����l�����ׂČ��ʂ��
	acs_max = ACS_MAX;
	jump_power = DEFAULT_JUMP_POWER;
	attack_interval = DEFAULT_ATTACK_INTERVAL;
	combo_attack_interval = (int)(DEFAULT_ATTACK_INTERVAL * 1.5f);
	player_anim_speed = PLAYER_ANIM;
	attack_time = DEFAULT_ATTACK_INTERVAL;		
}

void Player::Attack(GameMain* main)
{
	//�U��
	if (
#if DEBUG
		(KeyInput::OnKey(KEY_INPUT_RETURN) == true || PadInput::OnButton(XINPUT_BUTTON_B) == true)
#else
		PadInput::OnButton(XINPUT_BUTTON_B) == true
#endif
		&& attack_interval_count <= 0)
	{
		//�󒆂ɋ��Ȃ��Ȃ�
		if (acs[DOWN] == 0)
		{
			//�U���Ԋu�̑�����J�n
			attack_interval_count = attack_interval;

			//�v���C���[���ړ��ł��Ȃ�����
			attack_time_count = attack_time;

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
			//�S�i�ڂ���������ɕK���P�i�ڂɖ߂�悤�ɊԊu��ݒ肷��
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
		if (--attack_time_count > 0)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ��A����ȊO��false�ɂ���
			SetAttackFlg(attack_step);
		}
		else
		{
			//�s���Ă����U���̒i�K�ɉ������t���O��false�ɂ���
			attack_motion_flg[attack_step] = false;
		}
		break;
	case 4:
		//�󒆂ɂ������U����������
		if (onfloor_flg == false)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ��A����ȊO��false�ɂ���
			SetAttackFlg(attack_step);
			//�U���𐶐�����
			main->SpawnAttack(CreateAttactData(attack_step));

		}
		//�n�ʂɂ����璅�n�U��
		else
		{
			//�����U���̃t���O��false�ɂ���
			attack_motion_flg[4] = false;
			//���n�U���̔���
			attack_step = 5;
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ��A����ȊO��false�ɂ���
			SetAttackFlg(attack_step);
			main->SpawnAttack(CreateAttactData(attack_step));
			//�U���Ԋu�̑�����J�n
			attack_interval_count = attack_interval;
			//�v���C���[���ړ��ł��Ȃ�����
			attack_time_count = attack_time;
		}
		break;
	case 5:
		if (--attack_time_count >= 0)
		{
			//���ݍs���Ă���U���̒i�K�ɉ������t���O��true�ɂ��A����ȊO��false�ɂ���
			SetAttackFlg(attack_step);
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
	//���ɐG��Ă��Ȃ��Ȃ�
	if (onfloor_flg == false)
	{
		//�d�͂�^����
		GiveGravity();
		jump_flg = true;
	}

	//�����ꂩ�̍U�����������Ă��邩�A�_���[�W���󂯂Ă���r�����A����ł���r���Ȃ�
	if ((PlayAnyAttack() == true && attack_motion_flg[4] == false) || damage_flg == true || death_flg == true)
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

	//���ړ�
	if (
#if DEBUG
	(KeyInput::OnPresed(KEY_INPUT_A) == true || PadInput::TipLeftLStick(STICKL_X) <= -0.5)
#else
		PadInput::TipLeftLStick(STICKL_X) <= -0.5
#endif
		&& move_flg == true)
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
	if (
#if DEBUG
	(KeyInput::OnPresed(KEY_INPUT_D) == true || PadInput::TipLeftLStick(STICKL_X) >= 0.5)
#else
		PadInput::TipLeftLStick(STICKL_X) >= 0.5
#endif 
		&& move_flg == true)
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
	if (
#if DEBUG
	(KeyInput::OnKey(KEY_INPUT_SPACE) == true || PadInput::OnButton(XINPUT_BUTTON_A) == true)
#else
		PadInput::OnButton(XINPUT_BUTTON_A) == true
#endif
		&& jump_flg == false && move_flg == true)   
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
	
	//�W�����v���Ƀ_���[�W���󂯂����A�}����������
	if (jump_flg == true && damage_flg == true)
	{
		acs[DOWN]++;
	}
	//1�t���[���O�̍��W��ۑ�
	old_location = location;
	//�ړ�����
	location.x = location.x - acs[LEFT] + acs[RIGHT] - external_move[LEFT] + external_move[RIGHT];
	if (location.x < 0)
	{
		location.x = old_location.x;
	}
	location.y = location.y - acs[UP] + acs[DOWN] - external_move[UP] + external_move[DOWN];

	//Y���W�������������玀
	if (location.y > SCREEN_HEIGHT * 1.5f)
	{
		death_flg = true;
		move_flg = false;
	}
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
		hidden_flg = false;
	}
}

void Player::UpdatePlayerState()
{
	//��̌����ɂ���ĕς���
	//�E����
	if (direction == false)
	{
		//�d�͂�������Ă���Ȃ�
		if (onfloor_flg == false)
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
		//����ł���Ȃ�
		if (death_flg == true)
		{
			player_state = DEATH_RIGHT;
		}
	}
	//������
	else
	{
		//�d�͂�������Ă���Ȃ�
		if (onfloor_flg == false)
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
		//����ł���Ȃ�
		if (death_flg == true)
		{
			player_state = DEATH_LEFT;
		}
	}
}

bool Player::PlayAnyAttack()
{
	bool ret = false;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		//�����ꂩ�̍U�����s���Ă���Œ��Ȃ�t���O��true�ɂ���
		if (attack_motion_flg[i] == true)
		{
			ret = true;
		}
	}
	return ret;
}

void Player::SetAttackFlg(int num)
{
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		//�w�肵�������ȊO�̍U���t���O��������
		if (i != num)
		{
			attack_motion_flg[i] = false;
		}
		//�w�肵�������̍U���t���O�𗧂Ă�
		else
		{
			attack_motion_flg[i] = true;
		}
	}
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
	player_attack_data[0].attack_type = MELEE;
	//��i�K�ځ@������
	player_attack_data[1].shift_x = -erea.width;
	player_attack_data[1].shift_y = -50;
	player_attack_data[1].width = erea.width + 110;
	player_attack_data[1].height = 220;
	player_attack_data[1].who_attack = 0;
	player_attack_data[1].attack_time = 5;
	player_attack_data[1].damage = 3;
	player_attack_data[1].delay = 5;
	player_attack_data[1].attack_type = BULLET;
	player_attack_data[1].angle = 0.0f;
	player_attack_data[1].speed = 20;
	//��i�K��
	player_attack_data[2].shift_x = -erea.width;
	player_attack_data[2].shift_y = -70;
	player_attack_data[2].width = erea.width + 100;
	player_attack_data[2].height = 210;
	player_attack_data[2].who_attack = 0;
	player_attack_data[2].attack_time = 10;
	player_attack_data[2].damage = 1;
	player_attack_data[2].delay = 10;
	player_attack_data[2].attack_type = MELEE;
	//��i�K�ځ@������
	player_attack_data[3].shift_x = -erea.width;
	player_attack_data[3].shift_y = -70;
	player_attack_data[3].width = erea.width + 120;
	player_attack_data[3].height = 230;
	player_attack_data[3].who_attack = 0;
	player_attack_data[3].attack_time = 5;
	player_attack_data[3].damage = 2;
	player_attack_data[3].delay = 5;
	player_attack_data[3].attack_type = BULLET;
	player_attack_data[3].angle = 0.0f;
	player_attack_data[3].speed = 20;
	//�O�i�K��
	player_attack_data[4].shift_x = -erea.width;
	player_attack_data[4].shift_y = 50;
	player_attack_data[4].width = erea.width + 170;
	player_attack_data[4].height = 100;
	player_attack_data[4].who_attack = 0;
	player_attack_data[4].attack_time = 10;
	player_attack_data[4].damage = 1;
	player_attack_data[4].delay = 5;
	player_attack_data[4].attack_type = MELEE;
	//�O�i�K�ځ@������
	player_attack_data[5].shift_x = -erea.width;
	player_attack_data[5].shift_y = 40;
	player_attack_data[5].width = erea.width + 250;
	player_attack_data[5].height = 110;
	player_attack_data[5].who_attack = 0;
	player_attack_data[5].attack_time = 10;
	player_attack_data[5].damage = 2;
	player_attack_data[5].delay = 5;
	player_attack_data[5].attack_type = BULLET;
	player_attack_data[5].angle = 0.0f;
	player_attack_data[5].speed = 15;
	//�l�i�K��
	player_attack_data[6].shift_x = -erea.width;
	player_attack_data[6].shift_y = -90;
	player_attack_data[6].width = erea.width + 150;
	player_attack_data[6].height = 200;
	player_attack_data[6].who_attack = 0;
	player_attack_data[6].attack_time = 10;
	player_attack_data[6].damage = 2;
	player_attack_data[6].delay = 10;
	player_attack_data[6].attack_type = MELEE;
	//�l�i�K�ځ@������
	player_attack_data[7].shift_x = -erea.width;
	player_attack_data[7].shift_y = -90;
	player_attack_data[7].width = erea.width + 200;
	player_attack_data[7].height = 200;
	player_attack_data[7].who_attack = 0;
	player_attack_data[7].attack_time = 10;
	player_attack_data[7].damage = 3;
	player_attack_data[7].delay = 10;
	player_attack_data[7].attack_type = BULLET;
	player_attack_data[7].angle = 0.0f;
	player_attack_data[7].speed = 20;
	//�W�����v�U��
	player_attack_data[8].shift_x = -erea.width;
	player_attack_data[8].shift_y = 50;
	player_attack_data[8].width = erea.width+100;
	player_attack_data[8].height = 100;
	player_attack_data[8].who_attack = 0;
	player_attack_data[8].attack_time = 2;
	player_attack_data[8].damage = 1;
	player_attack_data[8].delay = 0;
	player_attack_data[8].attack_type = MELEE;
	//�W�����v�U���@������
	player_attack_data[9].shift_x = 0;
	player_attack_data[9].shift_y = 50;
	player_attack_data[9].width = 100;
	player_attack_data[9].height = 150;
	player_attack_data[9].who_attack = 0;
	player_attack_data[9].attack_time = 2;
	player_attack_data[9].damage = 1;
	player_attack_data[9].delay = 0;
	player_attack_data[9].attack_type = MELEE;
	//�W�����v�U������̒��n�U��
	player_attack_data[10].shift_x = 0;
	player_attack_data[10].shift_y = 50;
	player_attack_data[10].width = 100;
	player_attack_data[10].height = 100;
	player_attack_data[10].who_attack = 0;
	player_attack_data[10].attack_time = 5;
	player_attack_data[10].damage = 2;
	player_attack_data[10].delay = 0;
	player_attack_data[10].attack_type = BULLET;
	player_attack_data[10].angle = 0.0f;
	player_attack_data[10].speed = 20;
	//�W�����v�U������̒��n�U���@�����p
	player_attack_data[11].shift_x = 0;
	player_attack_data[11].shift_y = 50;
	player_attack_data[11].width = 250;
	player_attack_data[11].height = 100;
	player_attack_data[11].who_attack = 0;
	player_attack_data[11].attack_time = 5;
	player_attack_data[11].damage = 2;
	player_attack_data[11].delay = 0;
	player_attack_data[11].attack_type = BULLET;
	player_attack_data[11].angle = 0.0f;
	player_attack_data[11].speed = 25;
}

void Player::Respawn(Location _location)
{
	location = _location;
	player_state = IDOL_RIGHT;
	StopPowerUp();
	hp = 5;
	direction = false;
	attack_interval_count = 0;
	ca_interval_count = 0;
	attack_step = 0;
	attack_time_count = 0;
	for (int i = 0; i < ATTACK_PATTERN; i++)
	{
		attack_motion_flg[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		acs[i] = 0;
		external_move[i] = 0;
	}
	onfloor_flg = false;
	touch_ceil_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	jump_flg = false;
	move_flg = true;
	attack_anim_flg = false;
	player_anim = 0;
	attack_anim = 0;
	inv_flg = true;
	damage_flg = false;
	hidden_flg = false;
	death_flg = false;
	death_time = 120;
	damage_time = 0;
}
