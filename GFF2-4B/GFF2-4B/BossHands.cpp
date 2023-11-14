#include "BossHands.h"
#include"GameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>


BossHands::BossHands(int _who,Boss* boss) {


	Hands_Img_num = 0;//�C���J�ɂ����܂��g���ĂȂ��̂Ōォ��
	Hands_who = 0;

	switch (Hands_who)
	{
	case 0:
		//�}�[���^
		location.x = 700;
		location.y = -500;
		hi[0] = LoadGraph("resource/images/Boss/Boss.png", true);
		count = STOPBOSS;	//�U�艺�낵���r����ɂ�����܂łƂ߂�
		break;
	case 1:
		//�V�A��
		//�o���ʒu
		Direction = 0;
		location.x = 1280;
		location.y = 700;
		LoadDivGraph("resource/images/Boss/Iruka.png", 4, 2, 2, 256, 256, Hands_img);
		count = 0;	//�摜�؂�ւ��p

		break;
	case 2:
		//�C�G���[
		break;
	default:
		break;
	}

	erea.height = 190;
	erea.width = 190;
	switching = 0;
	who = _who;
	Attack_Num=0;
	hp=10;
	HitJumpAttack = false;
	Death_Flg = false;
	Rock_Once = false;
	hitflg = false;

	Death_Anim = 0;

	//�����`�ԂɂȂ��Ă邩�H
	if(boss->GetBossForm()==1){
		//�����U���o���悤�ɂȂ�

		Power_Up=true;
	}
	else {
		Power_Up = false;
	}

}

BossHands::~BossHands() {
}

void BossHands::Update(GameMain* main) {

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
			DrawGraphF(location.x, location.y, hi[0], TRUE);
			break;
		case 1:
			//�V�A��
			if (Direction == 0) {
				DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			}
			else {
				DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			}

			break;
		case 2:
			//�C�G���[
			break;
		default:
			break;
		}
	

#ifdef _DEBUG
	DrawFormatString(100, 400, 0xffffff, "switching%d", switching);
	DrawFormatString(159, 0, 0xff00ff, "HP%d", hp);
	//DrawFormatString(400, 0, 0xff00ff, "hitjump%d", HitJumpAttack);
	
#endif // _DEBUG


}

void BossHands::HandsMagenta(GameMain* main) {
		/*if (switching > 2) {
			down_hand = true;
		}*/
	
	if (Death_Flg == false) {

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

void BossHands::HandsCyan(GameMain* main){

	//�ŏ��ɏo�����č����Ɍ������ė�����
	//location.x -= 5;
	//location.y += 3;

	//if(location.x<0)
	//�C���J�������ނ��Ă�����
	if (Direction == 0) {
		location.x -= 5;
	}
	else {
		location.x += 5;
	}

	if (location.x > 1100) {
		Direction = 0;
		Hands_Img_num = 1;
	}
	else if (location.x < 150) {
		//Hands_Img_num = 2;
		Direction = 1;
	}
	
	//Hands_Img_num[0]�����������J����Ԃ̏ꍇ
	if (Direction == 0) {

		switch (count++)
		{
		case 50:
			Hands_Img_num = 1;
			break;
		case 100:
			Hands_Img_num = 0;
			break;
		default:
			break;
		}
	}

	if (Direction == 1) {

		switch (count++)
		{
		case 50:
			Hands_Img_num = 3;
			break;
		case 100:
			Hands_Img_num = 2;
			break;
		default:
			break;
		}
	//Hands_Img_num = 3;
}



	//if (cou++ > 50) {
	//	cou = 0;
	//	if (Direction == 0) {
	//		Hands_Img_num = 1;
	//	}
	//	//if (Direction == 1) {
	//	//	Hands_Img_num = 3;
	//	//}
	//}
	//else {
	//	if (Direction == 0) {
	//		Hands_Img_num = 0;
	//	}
	//	//if (Direction == 1) {
	//	//	Hands_Img_num = 2;
	//	//}
	//}

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
