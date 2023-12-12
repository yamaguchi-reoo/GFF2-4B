#include "bamboo.h"
#include "PadInput.h"

#define BAMBOO_GRAVITY  10

#define BAMBOO_IMAGE_SHIFT_X 12		//�摜���炵�p
#define BAMBOO_IMAGE_SHIFT_Y 48/*20*/		//�摜���炵�p
#define BAMBOO_IDLE 0				//�A�C�h����Ԃ̉摜
#define BAMBOO_ON_DEATH 1			//�ォ��U�����ꂽ�Ƃ��̉摜
#define BAMBOO_DEATH 2				//���S�A�j���[�V�����J�n�n
#define BAMBOO_DEATH_ANIM 10		//���̉摜�ɐ؂�ւ���܂ł̎��ԁi�t���[���j
#define BAMBOO_ON_DEATH_ANIM 10	


Bamboo::Bamboo(float pos_x, float pos_y)
{
	bamboo_state = BambooState::IDLE;
	anim_frame = 0;
	count = 0;
	location.x = pos_x;
	location.y = pos_y;
	erea.width = 75/*100*/;
	erea.height = 120/*200*/;

	hp = 1;
	image = LoadGraph("resource/images/Enemy/Bamboo.png");
	LoadDivGraph("resource/images/Enemy/bamboo(2).png", 4, 4, 1, 100, 200, bamboo_image);
	bamboo_anim = 0;

	apply_gravity = true;
	onfloor_flg = false;
	spawn_flg = true;
	death_flg = false;
	jump_attack = false;
	hidden_flg = false;
	Date.cyan = 10;
	Date.magenta = 0;
	Date.yellow = 10;
}

Bamboo::~Bamboo()
{
}

void Bamboo::Update(GameMain* main)
{
	anim_frame++;
	if (spawn_flg == true)
	{
		//���ɐG��Ă��Ȃ��Ȃ�
		if (apply_gravity == true)
		{
			//�d�͂�^����
			BambooGiveGravity();
		}
	}
	//�e�ړ��p�ϐ������Z�b�g
	BambooReset();
	//�`��֘A�̕ϐ��𓮂���
	BambooAnim();
}

void Bamboo::Draw() const
{
	if (hidden_flg == false)
	{
		//DrawFormatString(400, 400, 0xfffff, "%d", jump_attack);
		/*DrawGraphF(local_location.x, local_location.y, image, FALSE);*/
		//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xffffff, FALSE);
		switch (bamboo_state)
		{
		case BambooState::IDLE:
			DrawGraphF(local_location.x - BAMBOO_IMAGE_SHIFT_X, local_location.y - BAMBOO_IMAGE_SHIFT_Y, bamboo_image[BAMBOO_IDLE], true);
			break;
		case BambooState::DEATH:
			DrawGraphF(local_location.x - BAMBOO_IMAGE_SHIFT_X, local_location.y - BAMBOO_IMAGE_SHIFT_Y, bamboo_image[BAMBOO_DEATH + bamboo_anim], true);
			break;
		case BambooState::JUMP_ATTACK_DEATH:
			DrawGraphF(local_location.x - BAMBOO_IMAGE_SHIFT_X, local_location.y - BAMBOO_IMAGE_SHIFT_Y, bamboo_image[BAMBOO_ON_DEATH + bamboo_anim], true);
			break;
		default:
			break;
		}
	}
	//DrawFormatString(200, 400, 0xfffff, "%d", spawn_flg);
}
	
void Bamboo::BambooReset()
{	//�d�͂��������̔�������Z�b�g
	apply_gravity = true;
	onfloor_flg = false;
}

void Bamboo::BambooGiveGravity()
{
	location.y += BAMBOO_GRAVITY;
}

void Bamboo::Push(int num, Location _sub_location, Erea _sub_erea)
{
	Location b_center = { 0 };
	b_center.x = location.x + (erea.width / 2);
	b_center.y = location.y + (erea.height / 2);
	//���ɐG�ꂽ��
	if (location.y + erea.height - 12 < _sub_location.y)
	{
		location.y = _sub_location.y - erea.height + 0.1f;
		onfloor_flg = true;
	}
}
bool Bamboo::ApplyDamage(int num)
{
	hp = -num;
	if (hp <= 0 && death_flg == false) {
		
		/*spawn_flg = false;*/
		death_flg = true;

		spawn_flg = false;

		return true;
	}
	return false;
}
void Bamboo::FalseGravity()
{
	apply_gravity = false;
}

void Bamboo::BambooAnim()
{
	//�A�j���[�V�����p�ϐ�����
	//�W�����v�U���ł͂Ȃ��n��ł̍U���Ŏ��񂾏ꍇ
	if (death_flg == true && jump_attack == false)
	{
		bamboo_state = BambooState::DEATH;
		if (++count > BAMBOO_DEATH_ANIM)
		{
			bamboo_anim = 0;

		}
		if (++count > BAMBOO_DEATH_ANIM + 20)
		{
			bamboo_anim = 1;
		}
		if (++count > BAMBOO_DEATH_ANIM + 40)
		{
			hidden_flg = true;
			//spawn_flg = false;
		}
	}
	// �n��ł̍U���ł͂Ȃ��W�����v�U���Ŏ��񂾏ꍇ
	if (death_flg == true && jump_attack == true)
	{
		bamboo_state = BambooState::JUMP_ATTACK_DEATH;
		if (++count > BAMBOO_ON_DEATH_ANIM)
		{
			bamboo_anim = 0;
		}
		if (++count > BAMBOO_ON_DEATH_ANIM + 40)
		{
			bamboo_anim = 1;
		}
		if (++count > BAMBOO_ON_DEATH_ANIM + 70)
		{
			bamboo_anim = 2;
		}
		if (++count > BAMBOO_ON_DEATH_ANIM + 100)
		{
			hidden_flg = true;
		}
	}
	//�t���O��true�ɂȂ��Ă���count��12�ȏ�ɂȂ�����
	//if (death_flg == true && ++count >= (BAMBOO_DEATH_ANIM))
	//{
	//	//�X�|�[���t���O��
	//	spawn_flg = false;
	//	count = 0;
	//}
}

