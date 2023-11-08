#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
	once = false;
}

Attack::~Attack()
{

}

void Attack::Update(Location _location, Erea _erea)
{
	//�v���C���[�̍U������
	if (attack_flg == true && --attack_data.delay < 0)
	{
		//�U���\
		can_apply_damage = true;
		//�U���̎�ނɉ����ċ�����ς���
		switch (attack_data.attack_type)
		{
		case MELEE:
			//�E�����ɍU������
			if (attack_data.direction == false)
			{
				location.x = _location.x + (_erea.width / 2) + attack_data.shift_x;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			//�������ɍU������
			else
			{
				location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			break;
		case BULLET:
			//��񂾂����W��ǂݍ���
			if (once == false)
			{
				//�E�����ɍU������
				if (attack_data.direction == false)
				{
					location.x = _location.x + (_erea.width / 2) + attack_data.shift_x;
					location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

				}
				//�������ɍU������
				else
				{
					location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x;
					location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

				}
				once = true;
			}
			//�e�̊p�x�ɉ������ړ��ʂ�ݒ�
			float rad = attack_data.angle * (float)M_PI * 2;

			location.x += attack_data.speed * cosf(rad);
			location.y += attack_data.speed * sinf(rad);
			break;
		}
		//���߂�ꂽ���Ԃ��o������U��������
		if (--attack_data.attack_time <= 0)
		{
			attack_flg = false;
			//�U���s�\
			can_apply_damage = false;
			//���Z�b�g
			once = false;
		}
	}
	else
	{
		//�U���s�\
		can_apply_damage = false;
	}
}

void Attack::Draw()const
{
	if (can_apply_damage == true)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, false);
	}

}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
}
