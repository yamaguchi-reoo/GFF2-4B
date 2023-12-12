#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define CUT_ANIM_TIME 20
Attack::Attack()
{
	attack_flg = false;
	attack_data = { 0 };
	can_apply_damage = false;
	once = false;
	cut_flg = false;
	cut_time = 0;
	LoadDivGraph("resource/images/Boss/BossBullet.png", 2, 2, 1, 100, 64, bullet_img[BOSSHIMAWARI_BULLET]);
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
		if (cut_time < CUT_ANIM_TIME)
		{
			cut_time++;
		}
		else
		{
			cut_flg = false;
		}
	}
}

void Attack::Draw()const
{
#ifdef _DEBUG
	if (can_apply_damage == true)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, false);
		//�U���G�t�F�N�g������Ȃ�
		if (attack_data.effect_type >= 0 && attack_data.effect_type < 15)
		{
			//�`�悷��
			DrawFormatStringF(local_location.x, local_location.y, 0x00ffff, "%d", attack_data.effect_type);
		}
	}
#endif
	if (can_apply_damage == true)
	{
		//���`��i���Â炳�h�~�j
		if (attack_data.effect_type == HIMAWARI_BULLET || attack_data.effect_type == BOSSHIMAWARI_BULLET)
		{
			DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, true);
		}
		else
		{
			//DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x00ff00, false);
		}
		//�U���G�t�F�N�g������Ȃ�
		if (attack_data.effect_type >= 0 && attack_data.effect_type < 15)
		{
			//�`�悷��
			DrawGraph(local_location.x, local_location.y, bullet_img[attack_data.effect_type][0], false);
		}
	}
	if (cut_flg ==true && cut_time < CUT_ANIM_TIME)
	{
		//���Ő؂�ꂽ�\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-(cut_time*10));
		if(attack_data.effect_type == BOSSHIMAWARI_BULLET)
		{
			//�`�悷��
			DrawGraph(local_location.x, local_location.y, bullet_img[attack_data.effect_type][1], false);
		}
		else
		{
			DrawBox(local_location.x, local_location.y - cut_time, local_location.x + erea.width, local_location.y - (erea.height / 2) - cut_time, 0x00ff00, true);
			DrawBox(local_location.x, local_location.y + cut_time, local_location.x + erea.width, local_location.y + (erea.height / 2) + cut_time, 0x00ff00, true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Attack::SpawnAttack(AttackData _attackdata)
{
	attack_flg = true;
	attack_data = _attackdata;
	erea.width = attack_data.width;
	erea.height = attack_data.height;
	once = false;
	cut_flg = false;
}

void Attack::DeleteAttack() 
{
	attack_flg = false; 
}

void Attack::SetCutFlg()
{
	cut_flg = true;
	cut_time = 0;
	DeleteAttack();
}