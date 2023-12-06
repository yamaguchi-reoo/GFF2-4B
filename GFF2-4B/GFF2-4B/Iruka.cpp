#include "Iruka.h"
#include "GameMain.h"
#include "PadInput.h"

#define MOVE_SPEED  3
#define MOVE_FALL_SPEED  5

#define MAX_FALL_TIME 120

#define IRUKA_IMAGE_SHIFT_X 10		//�摜���炵�p
#define IRUKA_IMAGE_SHIFT_Y 5		//�摜���炵�p
#define IRUKA_ANIM_MOVE 0			//�ړ��A�j���[�V�����J�n�n�_
#define IRUKA_DEATH 2				//���S�A�j���[�V�����J�n�n
#define IRUKA_ANIM 20				//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j
#define IRUKA_DEATH_ANIM 10			//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j


#define TRUN_RAD 1.5708f		//90�x��]�p

Iruka::Iruka(float pos_x, float pos_y, bool direction, int _who)
{
	anim_frame = 0;
	count = 0;
	iruka_state = IrukaState::LEFT;

	location.x = pos_x;//1400;
	location.y = pos_y;// 100;
	spawn_location_y = pos_y;
	spawn_location_x = pos_x;
	erea.width = 100;
	erea.height = 50;
	speed = 5;
	who = _who;
	hp = 1;

	LoadDivGraph("resource/images/Enemy/Iruka.png", 4, 4, 1, 100, 50, iruka_image);
	iruka_anim = 0;

	fps_count = 0;

	iruka_direction = direction;// true;
	
	onfloor_flg = false;
	return_flg = false;
	spawn_flg = false;
	attack_flg = true;
	fall_flg = false;
	rightwall_flg = false;
	leftwall_flg = false;
	death_flg = false;

	Date.magenta = 5.0f;
	Date.cyan = 15.0f;
	Date.yellow = 5.0f;
}

Iruka::~Iruka()
{
}

void Iruka::Update(GameMain* main)
{
	anim_frame++;
	//�X�|�[�����Ă���Ȃ�
	if (spawn_flg == false) {
		if (attack_flg == true) {
			Attack(main);
			//�������Ă��Ȃ��Ƃ�
			if (fall_flg == false && return_flg == false) {
				//���E�ړ�
				Move();
			}
			//������
			else if (fall_flg == true) {
				//����
				MoveFall();
			}
			//���A
			if (return_flg == true /* && location.y == 570*/) {
				MoveReturn();
			}
		}
	}
	//���̕ǂɂԂ�������E�Ɉړ�
	if (leftwall_flg == true) {
		iruka_state = IrukaState::RIGHT;
		iruka_direction = false;
		leftwall_flg = false;
	}
	//�E�̕ǂɂԂ������獶�Ɉړ�
	if (rightwall_flg == true) {
		iruka_state = IrukaState::LEFT;
		iruka_direction = true;
		rightwall_flg = false;
	}
	//�e�ړ��p�ϐ������Z�b�g
	IrukaReset();
	//�`��֘A�̕ϐ��𓮂���
	IrukaAnim();
}

void Iruka::Draw() const
{
	if (spawn_flg == false) {
		//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ffff, TRUE);
		switch (iruka_state)
		{
		case IrukaState::IDLE:
			break;
		case IrukaState::RIGHT:
			DrawTurnGraphF(local_location.x + IRUKA_IMAGE_SHIFT_X, local_location.y + IRUKA_IMAGE_SHIFT_Y, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true);
			break;
		case IrukaState::LEFT:
			DrawGraphF(local_location.x, local_location.y + IRUKA_IMAGE_SHIFT_Y, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true);
			break;
		case IrukaState::RIGHT_FALL:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 4), 1, TRUN_RAD, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true, true);
			break;
		case IrukaState::LEFT_FALL:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 4), 1, -TRUN_RAD, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true, false);
			break;
		case IrukaState::RIGHT_RETURN:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 5), 1, -TRUN_RAD, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true, true);
			break;
		case IrukaState::LEFT_RETURN:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 5), 1, TRUN_RAD, iruka_image[IRUKA_ANIM_MOVE + iruka_anim], true, false);
			break;
		case IrukaState::DEATH:
			DrawGraphF(local_location.x, local_location.y + IRUKA_IMAGE_SHIFT_Y, iruka_image[/*IRUKA_DEATH + */iruka_anim], true);
			break;
		case IrukaState::FALL_DEATH:
			DrawRotaGraphF(local_location.x + (IRUKA_IMAGE_SHIFT_X * 2), local_location.y + erea.height - (IRUKA_IMAGE_SHIFT_Y * 4), 1, TRUN_RAD, iruka_image[/*IRUKA_DEATH + */ iruka_anim], true, true);
			break;
		default:
			break;
		}
	}
}

void Iruka::Move()
{
	//���ړ�
	if (iruka_state == IrukaState::LEFT)
	{
		location.x -= MOVE_SPEED;
		iruka_direction = true;
		if (location.x <= spawn_location_x - 640) {
			iruka_state = IrukaState::RIGHT;
		}
	/*	if (location.x < -100)
		{
			iruka_state = IrukaState::RIGHT;
			iruka_direction = false;
		}*/
	}
	//�E�ړ�
	if (iruka_state == IrukaState::RIGHT)
	{
		location.x += MOVE_SPEED;
		iruka_direction = false;
		if (location.x >= spawn_location_x + 640) {
			iruka_state = IrukaState::LEFT;

		}
	/*	if (location.x > SCREEN_WIDTH + 100) 
		{
			iruka_state = IrukaState::LEFT;
			iruka_direction = true;
		}*/
	}
}

void Iruka::MoveFall()
{
	erea.width = 50;
	erea.height = 120;
	location.y += MOVE_FALL_SPEED;
	//�E�������Ă��鎞�Ƀv���C���[�Ɍ������č~������Ȃ�
	if (iruka_state == IrukaState::RIGHT) 
	{
		//State��ω�
		iruka_state = IrukaState::RIGHT_FALL;
	}
	//���������Ă��鎞�Ƀv���C���[�Ɍ������č~������Ȃ�
	if (iruka_state == IrukaState::LEFT) 
	{
		//State��ω�
		iruka_state = IrukaState::LEFT_FALL;
	}
}

void Iruka::MoveReturn()
{
	
	if (++fps_count > MAX_FALL_TIME)
	{
		if (return_flg == true) {
			location.y -= speed;
			if (spawn_location_y >= location.y) {

				location.y = spawn_location_y;
				erea.width = 120;
				erea.height = 50;
				return_flg = false;
				fps_count = 0;
				//���̍����ɖ߂�Ƃ��C���J���E������������
				if (iruka_state == IrukaState::RIGHT_RETURN)
				{
					//�E�����ړ��ɂ���
					iruka_state = IrukaState::RIGHT;
				}
				//���̍����ɖ߂�Ƃ��C���J����������������
				if (iruka_state == IrukaState::LEFT_RETURN)
				{
					//�������ړ��ɂ���
					iruka_state = IrukaState::LEFT;
				}
			}
		}
		//�E�����ō~�肽��
		if (iruka_state == IrukaState::RIGHT_FALL) 
		{
			//�E�����ŏ㏸����
			iruka_state = IrukaState::RIGHT_RETURN;
		}
		//�������ō~�肽��
		if (iruka_state == IrukaState::LEFT_FALL) 
		{
			//�������ŏ㏸����
			iruka_state = IrukaState::LEFT_RETURN;
		}		
	}
}

void Iruka::IrukaOnFloor()
{
	onfloor_flg = true;
	if (fall_flg == true) {
		return_flg = true;
		fall_flg = false;
	}
}

void Iruka::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location i_center = { 0 };
	i_center.x = location.x + (erea.width / 2);
	i_center.y = location.y + (erea.height / 2);

	//���ɐG�ꂽ��
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = (_sub_location.y) - erea.height + 0.1f;
		//onfloor_flg = true;
		IrukaOnFloor();
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

void Iruka::IrukaReset()
{
	//�d�͂��������̔�������Z�b�g
	rightwall_flg = false;
	leftwall_flg = false;
	onfloor_flg = false;

}

AttackData Iruka::CreateAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = erea.height / 2;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 2;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = MELEE;
	if (iruka_state == IrukaState::RIGHT) {
		attack_data.direction = 0;
	}
	else if (iruka_state == IrukaState::LEFT) {
		attack_data.direction = 1;
	}
	
	if (fall_flg == true) {
		attack_data.shift_y = -12;
	}

	if (return_flg == true) {
		attack_data.shift_y = -6.5;
	}

	return attack_data;
}

void Iruka::Attack(GameMain* main)
{
	//�U���𐶐�����
	main->SpawnAttack(CreateAttactData());
}

void Iruka::ApplyDamage(int num)
{
	hp -= num;
	if (hp <= 0) {
		death_flg = true;
		//spawn_flg = true;
		//�v���C���[���a�����G�̐����J�E���g
		Score::SetAttackEnemyNum(1);
	}
}

ColorDate Iruka::GetColorDate()
{
	return Date;
}

void Iruka::IrukaAnim()
{
	if (spawn_flg == false)
	{
		//�A�j���[�V�����p�ϐ�����
		if (anim_frame % IRUKA_ANIM == 0)
		{
			if (++iruka_anim > 1)
			{
				iruka_anim = 0;
			}
		}
	}
	//�t���O��true�ɂȂ�����C���J�̏�Ԃ�DEATH�ɂ���
	if (death_flg == true)
	{
		//�󒆂ɂ���Ȃ�
		if (iruka_state == IrukaState::RIGHT || iruka_state == IrukaState::LEFT) {
			iruka_state = IrukaState::DEATH;
		}
		//���~�܂��͏㏸���Ȃ�
		else if(iruka_state == IrukaState::RIGHT_FALL || iruka_state == IrukaState::LEFT_FALL || 
			    iruka_state == IrukaState::RIGHT_RETURN || iruka_state == IrukaState::LEFT_RETURN)
		{
			iruka_state = IrukaState::FALL_DEATH;
		}
		if (++count > IRUKA_DEATH_ANIM)
		{
			iruka_anim = 2;
		}
		if (++count > IRUKA_DEATH_ANIM + 20)
		{
			iruka_anim = 3;
		}
		if (++count > IRUKA_DEATH_ANIM + 40)
		{
			spawn_flg = true;
		}
	}
	//�t���O��true�ɂȂ��Ă���count��12�ȏ�ɂȂ�����
	//if (++count >= (IRUKA_DEATH_ANIM))
	//{
	//	//�X�|�[���t���O��
	//	spawn_flg = true;
	//	count = 0;
	//}
	//else
	//{
	//	//�A�j���[�V�����p�ϐ�����
	//	if (anim_frame % IRUKA_DEATH_ANIM == 0)
	//	{
	//		if (++iruka_anim > 1)
	//		{
	//			iruka_anim = 0;
	//		}
	//	}
	//}
}
