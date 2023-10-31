#include"Attack.h"

Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
	move_front = 0;
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
		case WAVES:
			//�E�����ɍU������
			if (attack_data.direction == false)
			{
				location.x = _location.x + (_erea.width / 2) + attack_data.shift_x + move_front;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			//�������ɍU������
			else
			{
				location.x = _location.x - erea.width - (_erea.width / 2) - attack_data.shift_x - move_front;
				location.y = _location.y + ATTACK_EREA_SHIFT_Y + attack_data.shift_y;

			}
			move_front += attack_data.move;
			break;
		case BULLET:

			break;
		}
		//���߂�ꂽ���Ԃ��o������U��������
		if (--attack_data.attack_time <= 0)
		{
			attack_flg = false;
			//�U���s�\
			can_apply_damage = false;
		}
	}
	else
	{
		//�U���s�\
		can_apply_damage = false;
		move_front = 0;
	}
}

void Attack::Draw()const
{
	if (can_apply_damage == true)
	{
		DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ff00, false);
	}
}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
}
