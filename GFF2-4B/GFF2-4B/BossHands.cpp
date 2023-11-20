#include "BossHands.h"
#include"GameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>


BossHands::BossHands(int _who,Boss* boss) {

	//�S�r���ʂ̏�����
	frame = 0;
	Hands_Img_num = 0;//�C���J
	//Hands_who = 2;
	Hands_who = boss->Hand_Num;
	erea.height = hands_height[Hands_who];
	erea.width = hands_width[Hands_who];
	who = _who;
	Attack_Num = 0;
	Death_Anim = 0;

#ifdef _DEBUG
	hp = 0;
#else
	hp = 5;
#endif // _DEBUG

	switch (Hands_who)
	{
	case 0:
		//�}�[���^������
		MagentaInit();
		break;
	case 1:
		//�V�A��������
		CyanInit();
		break;
	case 2:
		//�C�G���[������
		YellowInit();
		break;
	default:
		break;
	}

	//�����`�ԂɂȂ��Ă邩�H
	if (boss->GetBossForm() == 1) {
		//�����U���o���悤�ɂȂ�

		Power_Up = true;
	}
	else {
		Power_Up = false;
	}
}

BossHands::~BossHands() {
}

void BossHands::Update(GameMain* main) {

	//�t���[������
	if (++frame > 1200)frame = 0;

		//��̎�ނɉ����Ď��s����Update��ς���
		switch (Hands_who)
		{
		case 0:
			//�}�[���^
			HandsMagenta(main);
			break;
		case 1:
			//�V�A��
			HandsCyan(main);
			break;
		case 2:
			//�C�G���[
			HandsYellow(main);
			break;
		default:
			break;
		}

}

void BossHands::Draw() const {

	//DrawGraphF(location.x + 100, location.y + 50, bosf[1], TRUE);
	


		switch (Hands_who)
		{
		case 0:
			//�}�[���^
				DrawGraphF(location.x, location.y, Zakuro_img[Zakuro_Imgnum], TRUE);
		
			break;
		case 1:
			//�V�A��
			//if (Direction == 0) {
			//	DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			//}
			//else {
			//	DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			//}
			DrawRotaGraph(turu_location.x, turu_location.y, 1, turu_angle, turu_img, TRUE, FALSE);
			if (face_angle > 0.0f && face_angle <0.7f)
			{
				DrawRotaGraph(location.x + 75, location.y + 75, 1, iruka_rad, Hands_img[Hands_Img_num], TRUE, TRUE);
			}
			else
			{
				DrawRotaGraph(location.x + 75, location.y + 75, 1, iruka_rad, Hands_img[Hands_Img_num], TRUE , TRUE);
			}
			break;
		case 2:
			//�C�G���[
			if (hima_state != BossHimawariState::SF_DOWN)
			{
				DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffff00, true);
			}
			else
			{
				DrawBoxAA(location.x + GetRand(10), location.y + GetRand(10), location.x + erea.width + GetRand(10), location.y + erea.height + GetRand(10), 0xffff00, true);
			}
			break;
		default:
			break;
		}
	

#ifdef _DEBUG
	//DrawFormatString(100, 500, 0xffffff, "�C���J��rad = %f", iruka_rad);
	DrawFormatString(159, 0, 0xff00ff, "HP%d", hp);
	//DrawFormatString(400, 0, 0xff00ff, "hitjump%d", HitJumpAttack);
	
	DrawFormatString(100, 400, 0xffffff, "location.y%f",location.y);
	DrawFormatString(100, 450, 0xffffff, "zakuro_state%d",zakuro_state);
	DrawFormatString(100, 470, 0xffffff, "hitflg%d",hitflg);
#endif // _DEBUG


}

void BossHands::MagentaInit()
{
	zakuro_state = BossZakuroState::Z_ANIM_UP;
	Zakuro_Direction = 0;
	Zakuro_Imgnum = 0;
	location.x = 700;
	location.y = 700;
	Set_Zakuro_x = 0;
	Set_Zakuro_y = 0;
	g = 9.8;
	sita = 45;
	V_zero = 50;
	time = 0;
	LoadDivGraph("resource/images/Boss/Zakuro.png", 8, 4, 2, 360, 360, Zakuro_img);
	count = STOPBOSS;	//�U�艺�낵���r����ɂ�����܂łƂ߂�
	switching = 0;
	HitJumpAttack = false;
	Death_Flg = false;
	Rock_Once = false;
	hitflg = false;
	onceflg = true;
}

void BossHands::HandsMagenta(GameMain* main) {

	
	if (Death_Flg == false) {

		/*
		//�{�X�̌��̍U������
		if (switching != 3) {
			Attack_Num = 0;
			BossAttack(main);
		}

		//�Ռ��g���o��
		if (hitflg == true && onceflg == true) {
			//�{�X�����`�Ԃ�������
			if (Power_Up == true) {
				Rock_Once = true;
				//if (rock != nullptr) {
				//	rock->Update();
				//}
			}

			switch (switching) {
			case 0:
				Attack_Num = 1;
				BossAttack(main);

				break;
			case 1:
				Attack_Num = 2;
				BossAttack(main);

				break;
			case 2:
				Attack_Num = 1;
				BossAttack(main);
				Attack_Num = 2;
				BossAttack(main);
				break;
			default:
				break;
			}
			onceflg = false;
		}

		if (switching < 2) {
			//�n�ʂɕt������J�E���g��0��菬�����Ȃ�����A���̏o���ʒu�Ɉړ�
			if (count < 0) {
				location.y -= 10;
			}
			//���̏o���ʒu�Ɉړ�
			if (location.y < -500) {
				hitflg = false;
				onceflg = true;
				location.y = -500;
				count = STOPBOSS;
				switching++;
			}
		}

		//����U�艺�낷����
		if (hitflg != true) {
			location.y += 5;
		}
		else {
			count--;
		}

		if (switching == 2 && hitflg == true) {
			count = 300;
			switching++;
		}

		//���o���ʒu�Z�b�g�p
		switch (switching) {
		case 0:
			//�E�ɏo��
			location.x = (float)Magentax[switching];
			break;
		case 1:
			//���ɏo��
			location.x = (float)Magentax[switching];
			break;
		case 2:
			//�����ɏo��
			location.x = (float)Magentax[switching];
			break;
		case 3:
			count--;
			if (count < 0) {
				location.y -= 10;
			}
			if (location.y < -500) {
				hitflg = false;
				onceflg = true;
				location.y = -500;
				count = STOPBOSS;
				switching = 0;
			}
			break;
		default:
			break;
		}
		*/

		switch (zakuro_state) {
		case BossZakuroState::Z_ANIM_UP:
			Zakuro_Imgnum = 1;
			if (location.y < -500) {
				zakuro_state = BossZakuroState::Z_FALLING;
			}
			else {
				location.y -= 10;
			}
			break;
		case BossZakuroState::Z_ANIM_FALLING:
			//�ŏ��̗����Ă���Ƃ��̓_���[�W���肪������
			break;
		case BossZakuroState::Z_MOVE:
			Zakuro_Imgnum = 0;

			Attack_Num = 4;
			BossAttack(main);

			
			if (location.x > 1000) {
				Zakuro_Direction = 1;
			}
			else if (location.x < 100) {
				Zakuro_Direction = 0;
			}

			if (Zakuro_Direction == 1) {
				location.x-=5;
			}
			else {
				location.x += 5;
			}

			if (0 + rand() % 100 == 0) {
				//�W�����v�͂���O�ɐF�X���������Ȃ��Ɠ��ڂ��炦�炢���ƂɂȂ�
				g = 9.8;
				sita = 45;
				V_zero = 50;
				time = 0;
				Set_Zakuro_x = location.x;
				Set_Zakuro_y = location.y;
				zakuro_state = BossZakuroState::Z_JUMP;
				onceflg = false;
			
			}

			break;
		case BossZakuroState::Z_JUMP:
			time+=0.3;
			Zakuro_Movex = V_zero * (cosf(sita) * time);
			Zakuro_Movey = (V_zero * (sinf(sita) * time)) - ((g * (time * time)) / 2);
			//Set-Move�ō���Set+Move�ŉE�ɍs��
			//Set-Move�ŏ��Set+Move�Ł��ɍs��
			location.x = Set_Zakuro_x - Zakuro_Movex;
			location.y = Set_Zakuro_y - Zakuro_Movey;

			if (location.y > 300) {
				zakuro_state = BossZakuroState::Z_MOVE;
			}

			break;
		case BossZakuroState::Z_FALLING:
			Zakuro_Imgnum = 2;
			Attack_Num = 4;
			BossAttack(main);
			if (location.y>290) {
				zakuro_state = BossZakuroState::Z_MOVE;
			}
				location.y += 10;
			break;
		default:
			break;
		}

	}
	else if(Death_Flg==true) {
		//���S�A�j���[�V����
		switch (Death_Anim) {
		case 0:
			if (count++ > 100) {
				Death_Anim++;
			}
			break;
		case 1:
			if (count++ > 100) {
				Death_Anim++;
			}
			break;
		case 2:
			main->Hands_Delete_Flg = true;
			break;
		default:
			break;
		};
	}

}

void BossHands::YellowInit()
{
	//�Ђ܂��
	hima_state = BossHimawariState::SF_WAIT;
	location.x = 1075;
	location.y = 500;
	pos = false;
	sf_speed = 10;
	angle_width = 0;
	angle_height = 0;
	move_angle = 0.75f;
	bullet_angle = 0;
	acceleration = 0;
	timer = 20;
	attack_cd = 30;
	attack_combo = 10;
	attack_num = 3;
	move_count = 0;
	face_angle = 0;
}

void BossHands::HandsYellow(GameMain* main)
{
	//�����Ă���Ȃ�
	if (Death_Flg == false) {

		//���̂̓����蔻��
		Attack_Num = 0;
		BossAttack(main);

		//��̌�������ʒ������ɌŒ�
		angle_width = (SCREEN_WIDTH / 2) - location.x;
		angle_height = (SCREEN_HEIGHT-erea.height) - location.y;
		rad = atan2f(angle_height, angle_width);
		face_angle = rad / M_PI / 2;

		//�Ђ܂��̏�Ԃɉ����čs����ς���
		switch (hima_state)
		{
			//�ҋ@
		case BossHimawariState::SF_WAIT:
			//�ړ��O�̗����ʒu��ۑ�
			if (location.x > (SCREEN_WIDTH / 2))
			{
				pos = false;
			}
			else
			{
				pos = true;
			}
			//�ҋ@��Ԃ��I������Ȃ�
			if (--timer < 0)
			{
				//�����x���Z�b�g
				acceleration = 0;
				//�ړ��J�n
				hima_state = BossHimawariState::SF_MOVE;
			}
			break;
			//�ړ�
		case BossHimawariState::SF_MOVE:
			if (location.y <= 500)
			{
				if (pos == false)
				{
					if (location.y < 400)
					{
						move_angle -= 0.0044f;
						attack_num = 3;
						attack_combo = 30;
					}
					else if (--attack_combo < 0 && attack_num>0)
					{
						Attack_Num = 3;
						BossAttack(main);
						attack_combo = 10;
						attack_num--;
					}
					if (move_angle >= 0.5f)
					{
						acceleration++;
					}
					else
					{
						if (acceleration > 1)
						{
							acceleration--;
						}
					}
				}
				else
				{
					if (location.y < 400)
					{
						move_angle += 0.0044f;
						attack_num = 3;
						attack_combo = 30;
					}
					else if (--attack_combo < 0 && attack_num>0)
					{
						Attack_Num = 3;
						BossAttack(main);
						attack_combo = 10;
						attack_num--;
					}
					if (move_angle <= 1)
					{
						acceleration++;
					}
					else
					{
						if (acceleration > 1)
						{
							acceleration--;
						}
					}
				}
				rad = move_angle * (float)M_PI * 2;
				location.x += (acceleration * 0.22f) * cosf(rad);
				location.y += (acceleration * 0.22f) * sinf(rad);
			}
			else
			{
				//�ړ����s�����񐔂𑪒�
				move_count++;
				//�e�ړ��p�ϐ����Z�b�g
				location.y = 500;
				move_angle = 0.75f;
				//���񐔈ړ����Ȃ�_�E����ԂցA����ȉ��Ȃ�ҋ@��Ԃ�
				if (move_count < 3)
				{
					timer = 20;
					hima_state = BossHimawariState::SF_WAIT;
				}
				else
				{
					move_count = 0;
					timer = 200;
					hima_state = BossHimawariState::SF_DOWN;
				}
			}
			if (--attack_cd < 0 && location.y < 400)
			{
				Attack_Num = 3;
				BossAttack(main);
				attack_cd = 30;
			}
			break;
			//����
		case BossHimawariState::SF_DOWN:
			//�ړ��O�̗����ʒu��ۑ�
			if (location.x > (SCREEN_WIDTH / 2))
			{
				pos = false;
			}
			else
			{
				pos = true;
			}
			//�ҋ@��Ԃ��I������Ȃ�
			if (--timer < 0)
			{
				//�����x���Z�b�g
				acceleration = 0;
				//�ړ��J�n
				hima_state = BossHimawariState::SF_MOVE;
			}
			break;
		default:
			break;
		}
	}
	else //����ł���Ȃ�
	{
	//���S�A�j���[�V����
	switch (Death_Anim) {
	case 0:
		if (count++ > 100) {
			Death_Anim++;
		}
		break;
	case 1:
		if (count++ > 100) {
			Death_Anim++;
		}
		break;
	case 2:
		main->Hands_Delete_Flg = true;
		break;
	default:
		break;
	};
	}
}

void BossHands::CyanInit()
{
	//�o���ʒu
	iruka_state = BossIrukaState::D_WAIT;
	location.x = SCREEN_WIDTH;
	location.y = 0;
	face_angle = 0.6f;
	iruka_rad = 0;
	turu_rad = 0;
	ref_num = 0;
	LoadDivGraph("resource/images/Boss/Iruka.png", 4, 2, 2, 256, 256, Hands_img);
	turu_img = LoadGraph("resource/images/Boss/LongLongTuru.png", true);
	count = 0;	//�摜�؂�ւ��p
	turu_location = { 0,0 };
	turu_angle = 0;
	timer = 30;
	Death_Flg = false;
	acceleration = 0;

}

void BossHands::HandsCyan(GameMain* main) {

	//��
	//��̕`��ʒu���v�Z

	turu_location.x = (SCREEN_WIDTH / 2) + GetCenterLocation().x;
	turu_location.y = GetCenterLocation().y/2;
	turu_angle = atan2f(turu_location.y - GetCenterLocation().y, turu_location.x - GetCenterLocation().x);
	turu_rad =turu_angle*(float)M_PI*2;

	//�A�j���[�V�����p
	if (
		(iruka_state == BossIrukaState::D_DASH && frame % 3 == 0 && timer<=0) || 
		(iruka_state == BossIrukaState::D_MOVE && frame % 10 == 0 && timer <= 0)
		)
	{
		if (++Hands_Img_num > 1)
		{
			Hands_Img_num = 0;
		}
	}
		//�����Ă���Ȃ�
	if (Death_Flg == false) {
		//���̂̓����蔻��
		Attack_Num = 0;
		BossAttack(main);
		switch (iruka_state)
		{
		case BossIrukaState::D_WAIT:
			//�E��ɋA��
			iruka_rad = atan2f(0 - location.y, SCREEN_WIDTH - location.x);
			location.x += (120 * 0.22f) * cosf(iruka_rad);
			location.y += (120 * 0.22f) * sinf(iruka_rad);
			if (location.x > SCREEN_WIDTH - erea.width)
			{
				location.x = SCREEN_WIDTH - erea.width;
			}
			if (location.y < 0)
			{
				location.y = 0;
			}
			if (--timer < 0)
			{
				iruka_state = BossIrukaState::D_MOVE;
			}
			break;
		case BossIrukaState::D_MOVE:
			if (--timer < 0)
			{
				//���邩������������
				if (acceleration < 60)
				{
					acceleration++;
				}
				//��̊p�x��0~1�͈͓̔�����o�Ȃ��悤��
				if (face_angle > 1)face_angle -= 1;
				//�ړ������v�Z
				iruka_rad = face_angle * (float)M_PI * 2;
				location.x += (acceleration * 0.22f) * cosf(iruka_rad);
				location.y += (acceleration * 0.22f) * sinf(iruka_rad);
				//�ǂɔ���
				if (location.x < 0)
				{
					location.x = 0;
					face_angle = GetRandAngle(0);
					ref_num++;
					timer = 20;
					iruka_rad = face_angle * (float)M_PI * 2;
				}
				else if (location.x > SCREEN_WIDTH - erea.width)
				{
					location.x = SCREEN_WIDTH - erea.width;
					face_angle = GetRandAngle(1);
					ref_num++;
					timer = 20;
					iruka_rad = face_angle * (float)M_PI * 2;
				}
				else if (location.y < 0)
				{
					location.y = 0;
					face_angle = GetRandAngle(2);
					ref_num++;
					timer = 20;
					iruka_rad = face_angle * (float)M_PI * 2;
				}
				else if (location.y > SCREEN_HEIGHT - erea.height)
				{
					location.y = SCREEN_HEIGHT - erea.height;
					face_angle = 1 - face_angle;
					iruka_rad = face_angle * (float)M_PI * 2;
				}
			}
			//5�񏰈ȊO�ɔ��˂������Z
			if (ref_num > 5)
			{
				iruka_state = BossIrukaState::D_DASH;
				timer = 50;
				acceleration = 70;
				ref_num = 0;
			}
			break;
		case BossIrukaState::D_DASH:
			if (timer > 0)
			{
				iruka_rad = atan2f(main->GetPlayerLocation().y - location.y, main->GetPlayerLocation().x - location.x);
			}
			if (--timer < 0)
			{
				if (face_angle > 1)face_angle -= 1;
				location.x += (acceleration * 0.22f) * cosf(iruka_rad);
				location.y += (acceleration * 0.22f) * sinf(iruka_rad);
				if (location.x < 0)
				{
					location.x = 0;
					ref_num++;
				}
				else if (location.x > SCREEN_WIDTH - erea.width)
				{
					location.x = SCREEN_WIDTH - erea.width;
					ref_num++;
				}
				else if (location.y < 0)
				{
					location.y = 0;
					ref_num++;
				}
				else if (location.y > SCREEN_HEIGHT - erea.height)
				{
					location.y = SCREEN_HEIGHT - erea.height;
					ref_num++;
				}
				if (ref_num > 1)
				{
					iruka_state = BossIrukaState::D_DOWN;
					timer = 200;
					ref_num = 0;
					acceleration = 0;
				}
			}
			break;
		case BossIrukaState::D_DOWN:
			if (--timer < 0)
			{
				iruka_state = BossIrukaState::D_WAIT;
				timer = 50;
			}
			break;
		default:
			break;
		}
		
	}
	else //����ł���Ȃ�
	{
	//���S�A�j���[�V����
	switch (Death_Anim) {
	case 0:
		if (count++ > 100) {
			Death_Anim++;
		}
		break;
	case 1:
		if (count++ > 100) {
			Death_Anim++;
		}
		break;
	case 2:
		main->Hands_Delete_Flg = true;
		break;
	default:
		break;
	};
	}
}

AttackData BossHands::BossAttactData()
{
	AttackData attack_data;
	switch (Attack_Num) {
	//�U�N���̌�0~2�܂�
	case 0:
		attack_data.shift_x = -erea.width - 3;
		attack_data.shift_y = -30;
		attack_data.width = erea.width;
		attack_data.height = erea.height - 20;
		attack_data.who_attack = who;
		attack_data.attack_time = 3;
		attack_data.delay = 0;
		attack_data.damage = 1;
		attack_data.attack_type = MELEE;
		break;
		//�Ռ��g
	case 1:
		attack_data.shift_x = -erea.width;
		attack_data.shift_y = 50;
		attack_data.width = erea.width;
		attack_data.height = erea.height / 2;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 3;
		attack_data.damage = 1;
		attack_data.attack_type = BULLET;
		attack_data.speed = 3;
		attack_data.angle = 0.5;
		attack_data.effect_type = BOSSZAKURO_WAVES;

		attack_data.direction = true;
		break;
	case 2:
		attack_data.shift_x = -erea.width;
		attack_data.shift_y = 50;
		attack_data.width = erea.width;
		attack_data.height = erea.height / 2;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 3;
		attack_data.damage = 1;
		attack_data.attack_type = BULLET;
		attack_data.speed = 3;
		attack_data.angle = 1.0;
		attack_data.direction = false;
		break;
		//�Ђ܂��e
	case 3:
		attack_data.shift_x = 0;
		attack_data.shift_y = 0;
		attack_data.width = 50;
		attack_data.height = 50;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 3;
		attack_data.damage = 1;
		attack_data.attack_type = BULLET;
		attack_data.speed = 7;
		attack_data.angle = face_angle;
		attack_data.effect_type = BOSSHIMAWARI_BULLET;
		break;
	case 4:
		attack_data.shift_x = -erea.width - 3;
		attack_data.shift_y = -100;
		attack_data.width = erea.width;
		attack_data.height = erea.height - 20;
		attack_data.who_attack = who;
		attack_data.attack_time = 3;
		attack_data.delay = 0;
		attack_data.damage = 1;
		attack_data.attack_type = MELEE;
		break;
	default:
		break;
	}

	return attack_data;
}

void BossHands::BossAttack(GameMain* main)
{
	if (Death_Flg == false) {
		//�U���𐶐�����
		main->SpawnAttack(BossAttactData());
	}
}

void BossHands::ApplyDamage(int num) {
	//�U�����q�b�g�����񐔂œ|���
	if (HitJumpAttack!=true) {
		hp--;
	}
	
	if (hp <= 0) {
		Death_Flg = true;
		count = 0;
	}
}

float BossHands::GetRandAngle(int _wall)
{
	switch (_wall)
	{
		//����
	case 0:
		//0����0.2�A0.8����1�̒����烉���_���Ȓl��Ԃ�
		return fabs(GetRand(1) - (GetRand(20) * 0.01f));
		//�E��
	case 1:
		//0.3����0.7�̒����烉���_���Ȓl��Ԃ�
		return (GetRand(40) * 0.01f) + 0.3f;
		//���
	case 2:
		//0.05����0.45�̒����烉���_���Ȓl��Ԃ�
		return (GetRand(40) * 0.01f) + 0.05f;
		break;
	}

	return 0;
}
