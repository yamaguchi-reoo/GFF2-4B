#include "Himawari.h"
#include "GameMain.h"

#define BULLET_INTERVAL 120		//�C���^�[�o��
#define RAPID_INTERVAL 9		//�A�˃C���^�[�o��	
#define HIMAWARI_GRAVITY  10	// �d��
#define BULLET_NUM_MAX 3		//�e�̍ő�A�ː�

#define HIMAWARI_IMAGE_SHIFT_X 20		//�摜���炵�p
#define HIMAWARI_IMAGE_SHIFT_Y 14		//�摜���炵�p
#define HIMAWARI_ANIM_MOVE 0			//�ړ��A�j���[�V�����J�n�n�_
#define HIMAWARI_ANIM_ATTACK 2
#define HIMAWARI_DEATH 3				//���S�A�j���[�V�����J�n�n
#define HIMAWARI_ANIM 20				//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j
#define HIMAWARI_DEATH_ANIM 10			//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j


Himawari::Himawari(float pos_x, float pos_y, bool direction, int _who)
{
	anim_frame = 0;
	count = 0;

	himawari_state = HimawariState::LEFT;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 100;
	erea.width = 50;
	who = _who;
	hp = 2;

	image = LoadGraph("resource/images/Enemy/Himawari.png");
	LoadDivGraph("resource/images/Enemy/Himawari.png", 5, 5, 1, 90, 120, himawari_image);
	himawari_anim = 0;
	himawari_direction = direction;

	attack_flg = true;
	spawn_flg = false;

	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	onfloor_flg = false;
	death_flg = false;
	
	rapid_fire_interval = RAPID_INTERVAL;
	attack_interval_count = BULLET_INTERVAL;
	bullet_num = BULLET_NUM_MAX ;

	Date.magenta = 5.0f;
	Date.cyan = 5.0f;
	Date.yellow = 15.0f;
}

Himawari::~Himawari()
{
}

void Himawari::Update(GameMain* main)
{
	anim_frame++;
	//�X�|�[�����Ă��邩�A�^�b�N�t���O�������Ă���Ƃ�
	if (spawn_flg == false && attack_flg == true)
	{
		//�U��
		Attack(main);
		//�s��
		Move();
	}
	//���ɏ���Ă�����d��OFF
	if (onfloor_flg == true)
	{
		apply_gravity = false;
		//if (himawari_direction == true)
		//{
		//	himawari_state = HimawariState::LEFT;
		//}
		//else
		//{
		//	himawari_state = HimawariState::RIGHT;
		//}
	}
	//���ɐG��Ă��Ȃ��Ȃ�
	if (apply_gravity == true)
	{
		//�d�͂�^����
		HimawariGiveGravity();
	}
	//�e�ړ��p�ϐ������Z�b�g
	HimawariReset();
	//�`��֘A�̕ϐ��𓮂���
	HimawariAnim();
}

void Himawari::Draw() const
{
	if (spawn_flg == false) 
	{
		switch (himawari_state)
		{
		case HimawariState::IDLE:
			break;
		case HimawariState::RIGHT:
			DrawTurnGraphF(local_location.x - HIMAWARI_IMAGE_SHIFT_X, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_MOVE + himawari_anim], true);
			break;
		case HimawariState::LEFT:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_MOVE + himawari_anim], true);
			break;
		case HimawariState::RIGHT_SHOOT:
			DrawTurnGraphF(local_location.x - HIMAWARI_IMAGE_SHIFT_X, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_ATTACK], true);
			break;
		case HimawariState::LEFT_SHOOT:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[HIMAWARI_ANIM_ATTACK], true);
			break;
		case HimawariState::CHARGE:
			break;
		case HimawariState::DEATH:
			DrawGraphF(local_location.x, local_location.y - HIMAWARI_IMAGE_SHIFT_Y, himawari_image[/*HIMAWARI_DEATH + */himawari_anim], true);
			break;
		default:
			break;
		}
	}
}

void Himawari::Move()
{
	//���ړ�
	if (himawari_state == HimawariState::LEFT)
	{
		himawari_direction = true;
	}
	//�E�ړ�
	if (himawari_state == HimawariState::RIGHT)
	{
		himawari_direction = false;
	}
}

void Himawari::HimawariReset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Himawari::HimawariGiveGravity()
{
	location.y += HIMAWARI_GRAVITY;
}

void Himawari::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location h_center = { 0 };
	h_center.x = location.x + (erea.width / 2);
	h_center.y = location.y + (erea.height / 2);

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

AttackData Himawari::CreateAttactData()
{

	AttackData attack_data;
	//�ǂ̒i�K�̍U���ł��ς��Ȃ����͂����Ŋi�[����
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = + 15;
	attack_data.who_attack = who;
	attack_data.direction = himawari_direction;
	//�e�̑傫��
	attack_data.width = 40;
	attack_data.height = 30;
	//�U���Ɋւ�����
	attack_data.attack_time = 60;
	attack_data.damage = 1;
	attack_data.delay = 5;
	attack_data.attack_type = BULLET;//MELEE;
	attack_data.effect_type = HIMAWARI_BULLET;

	//�E�Ɍ����Ă�����A���O���͂��̂܂�
	if (himawari_direction == false)
	{
		attack_data.angle = 0.0f;
	}
	//���Ɍ����Ă�����A���O����180��]
	else
	{
		attack_data.angle = 0.5f;
	}
	attack_data.speed = 10;

	return attack_data;
	
}

void Himawari::Attack(GameMain* main)
{
	if (--attack_interval_count <= 0)
	{
		if (--rapid_fire_interval <= 0) {
			bullet_num--;
			rapid_fire_interval = RAPID_INTERVAL;

			// �U���𐶐�����
			main->SpawnAttack(CreateAttactData());

			// �N�[���_�E��
			if (bullet_num <= 0) {
				bullet_num = BULLET_NUM_MAX;
				attack_interval_count = BULLET_INTERVAL;
			}

			// �e�𔭎˂�����ɃA�j���[�V�����X�e�[�g��ݒ�
			if (himawari_direction == false)
			{
				himawari_state = HimawariState::RIGHT_SHOOT;
			}
			else
			{
				himawari_state = HimawariState::LEFT_SHOOT;
			}
		}
	}
	else
	{
		// �e�𔭎˂�����̈�莞�Ԃ��o�߂���O�Ɍ��̃A�j���[�V�����X�e�[�g�ɖ߂�
		if (himawari_direction == false)
		{
			himawari_state = HimawariState::RIGHT;
		}
		else
		{
			himawari_state = HimawariState::LEFT;
		}
	}
}

void Himawari::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		death_flg = true;
		//�v���C���[���a�����G�̐����J�E���g
		Score::SetAttackEnemyNum(2);
	}
}

void Himawari::ReverseDirection()
{
		himawari_direction = false;
}

void Himawari::ObverseDirection()
{
	himawari_direction =true ;
}

void Himawari::HimawariAnim()
{
	if (spawn_flg == false)
	{
		//�A�j���[�V�����p�ϐ�����
		if (anim_frame % HIMAWARI_ANIM == 0)
		{
			if (++himawari_anim > 1)
			{
				himawari_anim = 0;
			}
		}
	}
	if (death_flg == true)
	{
		himawari_state = HimawariState::DEATH;
		if (++count > HIMAWARI_DEATH_ANIM)
		{
			himawari_anim = 3;
		}
		if (++count > HIMAWARI_DEATH_ANIM + 20)
		{
			himawari_anim = 4;
		}
		if (++count > HIMAWARI_DEATH_ANIM + 40)
		{
			spawn_flg = true;
		}
	}
	////�t���O��true�ɂȂ��Ă���count��12�ȏ�ɂȂ�����
	//if (death_flg == true && ++count >= (HIMAWARI_DEATH_ANIM))
	//{
	//	//�X�|�[���t���O��
	//	spawn_flg = true;
	//	count = 0;
	//}
}

ColorDate Himawari::GetColorDate()
{
	 return Date;
}

