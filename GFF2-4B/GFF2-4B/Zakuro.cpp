#include "Zakuro.h"
#include "DxLib.h"
#include "GameMain.h"
#include "common.h"
#include"SoundManager.h"

#define MOVE_SPEED  1	//���x
#define ZAKURO_GRAVITY  5//�d��

#define ZAKURO_IMAGE_SHIFT_X 0		//�摜���炵�p
#define ZAKURO_IMAGE_SHIFT_Y -9/*-20*/	//�摜���炵�p
#define ZAKURO_ANIM_MOVE 0			//�ړ��A�j���[�V�����J�n�n�_
#define ZAKURO_DEATH 0				//���S�A�j���[�V�����J�n�n
#define ZAKURO_ANIM 20				//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j
#define ZAKURO_DEATH_ANIM 10			//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j


Zakuro::Zakuro(float pos_x, float pos_y, bool direction,int _who)
{

	anim_frame = 0;
	count = 0;

	zakuro_state = ZakuroState::RIGHT;

	location.x = pos_x;
	location.y = pos_y;
	erea.height = 75 /*120*/;
	erea.width = 75/*120*/;
	speed = MOVE_SPEED;
	who = _who;
	//hp = 1;

	image = LoadGraph("resource/images/Enemy/zakuro.png");


	LoadDivGraph("resource/images/Enemy/ZakuroWalk.png", 2, 2, 1, 75, 75, zakuro_image);
	LoadDivGraph("resource/images/Enemy/ZakuroDeath.png", 2, 2, 1, 75, 75, zakuro_death_image);
	stop_count = 60;

	zakuro_direction = true;
	onfloor_flg = false;
	attack_flg = true;
	spawn_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	apply_gravity = true;
	hit_flg = false;
	knockback_flg = false;
	death_flg = false;

	zakuro_anim = 0;
	zakuro_death_anim = 0;
	hp = 3;

	Date.magenta = 15.0f;
	Date.cyan = 5.0f;
	Date.yellow = 5.0f;
	impact = 0;
}
Zakuro::~Zakuro()
{
}
void Zakuro::Update(GameMain* main)
{
	anim_frame++;
	if (--impact < 0)
	{
		impact = 0;
	}
	if (spawn_flg == false) 
	{
		if (attack_flg == true) 
		{
			//�U��
			Attack(main);
			//���E�ړ�
			Move();
		}
		else
		{
			MoveNockBack();
		}
	}
		//���ɏ���Ă�����d��OFF
	if (onfloor_flg == true)
	{
		apply_gravity = false;
		if (zakuro_direction == true)
		{
			zakuro_state = ZakuroState::LEFT;
		}
		else
		{
			zakuro_state = ZakuroState::RIGHT;
		}
	}
	//���ɐG��Ă��Ȃ��Ȃ�
	if (apply_gravity == true)
	{
		//�d�͂�^����
		ZakuroGiveGravity();
	}
	//
	HitWall();
	//�`��֘A�̕ϐ��𓮂���
	ZakuroAnim();
	//�e�ړ��p�ϐ������Z�b�g
	ZakuroReset();
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	//DrawFormatString(200, 0, 0xffffff, "%f", local_location.x);
	if (spawn_flg == false) 
	{
		switch (zakuro_state)
		{
		case ZakuroState::RIGHT:
			DrawTurnGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, zakuro_image[ZAKURO_ANIM_MOVE + zakuro_anim], true);
			break;
		case ZakuroState::LEFT:
			DrawGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, zakuro_image[ZAKURO_ANIM_MOVE + zakuro_anim], true);
			break;
		case ZakuroState::IDLE_RIGHT:
			DrawTurnGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, zakuro_image[ZAKURO_ANIM_MOVE + zakuro_anim], true);
			break;
		case ZakuroState::IDLE_LEFT:
			DrawGraphF(local_location.x - ZAKURO_IMAGE_SHIFT_X, local_location.y - ZAKURO_IMAGE_SHIFT_Y, zakuro_image[ZAKURO_ANIM_MOVE + zakuro_anim], true);
			break;
		case ZakuroState::DEATH:
			DrawGraphF(local_location.x, local_location.y + (ZAKURO_IMAGE_SHIFT_Y + 10), zakuro_death_image[/*ZAKURO_ANIM_MOVE + */ zakuro_death_anim], true);
			break;
		default:
			break;
		}
	}
}

void Zakuro::Move()
{
	//���ړ�
	if (zakuro_state == ZakuroState::LEFT) 
	{
		if (leftwall_flg == false)
		{
			location.x -= MOVE_SPEED;
		}
		/*zakuro_direction = true;*/
	/*	if (location.x < 0) 
		{
			zakuro_state = ZakuroState::RIGHT;
			zakuro_direction = false;
		}*/
	}
	//�E�ړ�
	if (zakuro_state == ZakuroState::RIGHT) 
	{
		if (rightwall_flg == false)
		{
			location.x += MOVE_SPEED;
		}
		/*zakuro_direction = false;*/
	/*	if (location.x > SCREEN_WIDTH - 50) 
		{
			zakuro_state = ZakuroState::LEFT;
			zakuro_direction = true;
		}*/
	}
}

void Zakuro::MoveNockBack()
{
	//���ړ�
	if (zakuro_state == ZakuroState::LEFT)
	{
		location.x += speed * 0.8f;
	}
	//�E�ړ�
	if (zakuro_state == ZakuroState::RIGHT)
	{
		location.x -= speed * 0.8f;
	}
	stop_count -= 1;
	if (stop_count <= 0)
	{
		attack_flg = true;
		stop_count = 60;
		//knockback_flg = false;
	}
}

void Zakuro::ZakuroReset()
{
	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;
}

void Zakuro::ZakuroGiveGravity()
{
	if (zakuro_state == ZakuroState::LEFT)
	{
		zakuro_state = ZakuroState::IDLE_LEFT;
	}
	if (zakuro_state == ZakuroState::RIGHT)
	{
		zakuro_state = ZakuroState::IDLE_RIGHT;
	}
	location.y += ZAKURO_GRAVITY;
}

void Zakuro::Push(Location _sub_location, Erea _sub_erea)
{
	Location z_center = { 0 };
	z_center.x = location.x + (erea.width / 2);
	z_center.y = location.y + (erea.height / 2);
	//���ɐG�ꂽ��
	if (location.y + erea.height - 30 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height - 0.05f;
		onfloor_flg = true;
	}
	//�E�̕ǂɐG�ꂽ��
	if (location.x + erea.width - 24 < _sub_location.x && location.y + erea.height - 12 > _sub_location.y)
	{
		location.x = _sub_location.x - erea.width;
		/*zakuro_state = ZakuroState::LEFT;*/
		zakuro_direction = true;
		//�E�̕ǂɐG�ꂽ�t���O�𗧂Ă�
		rightwall_flg = true;
	}
	//���̕ǂɐG�ꂽ��
	if (location.x + 24 > _sub_location.x + _sub_erea.width && location.y + erea.height - 12 > _sub_location.y)
	{
		location.x = _sub_location.x + _sub_erea.width;
		/*zakuro_state = ZakuroState::RIGHT;*/
		zakuro_direction = false;
		//���̕ǂɐG�ꂽ�t���O�𗧂Ă�
		leftwall_flg = true;
	}
	////�ǂ����̕ǂɂ��G��Ă��Ȃ��Ƃ��̒n�ʂ��蔲���h�~
	//else
	//{
	//	location.y = _sub_location.y - erea.height;
	//	onfloor_flg = true;
	//}

}

void Zakuro::HitWall()
{
	////���̕ǂɂԂ�������E�Ɉړ�
	//if (leftwall_flg == true) {
	//	zakuro_state = ZakuroState::RIGHT;
	//	zakuro_direction = false;
	//	leftwall_flg = false;
	//}
	////�E�̕ǂɂԂ������獶�Ɉړ�
	//if (rightwall_flg == true) {
	//	zakuro_state = ZakuroState::LEFT;
	//	zakuro_direction = true;
	//	rightwall_flg = false;
	//}

}

AttackData Zakuro::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = (-erea.height / 4) + 40/*(- erea.height / 4) + 20*/;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 2;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = MELEE;
	attack_data.direction = zakuro_direction;


	return attack_data;
}

void Zakuro::Attack(GameMain* main)
{
	//�U���𐶐�����
	main->SpawnAttack(CreateAttactData());
}

void Zakuro::ApplyDamage(int num)
{
	hp -= num;
	attack_flg = false;
	if (hp <= 0) {
		death_flg = true;
		//�v���C���[���a�����G�̐����J�E���g
		Score::SetAttackEnemyNum(0);
	}
}

void Zakuro::HitZakuro()
{
	//switch (zakuro_state) {
	//case ZakuroState::RIGHT:
	//	zakuro_state = ZakuroState::LEFT;
	//	zakuro_direction = true;
	//	break;
	//case ZakuroState::LEFT:
	//	zakuro_state = ZakuroState::RIGHT;
	//	zakuro_direction = false;
	//	break;
	//}
}

void Zakuro::ZakuroAnim()
{
	if (spawn_flg == false)
	{
		//�A�j���[�V�����p�ϐ�����
		if (anim_frame % ZAKURO_ANIM == 0)
		{
			if (++zakuro_anim > 1)
			{
				zakuro_anim = 0;
			}
		}
	}
	if (death_flg == true)
	{
		zakuro_state = ZakuroState::DEATH;
		if (++count > ZAKURO_DEATH_ANIM)
		{
			zakuro_death_anim = 0;
		}
		if (++count > ZAKURO_DEATH_ANIM + 20)
		{
			zakuro_death_anim = 1;
		}
		if (++count > ZAKURO_DEATH_ANIM + 40)
		{
			spawn_flg = true;
		}
		SoundManager::StopSound(ENEMY_EXPLOSION_SOUND);
	}
	//�t���O��true�ɂȂ��Ă���count��12�ȏ�ɂȂ�����
	//if (death_flg == true && ++count >= (ZAKURO_DEATH_ANIM))
	//{
	//	//�X�|�[���t���O��
	//	spawn_flg = true;
	//	count = 0;
	//}

}

ColorDate Zakuro::GetColorDate()
{
	return Date;
}




