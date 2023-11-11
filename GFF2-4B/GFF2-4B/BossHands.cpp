#include "BossHands.h"
#include"GameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>

BossHands::BossHands(int _who,Boss* boss) {

	LoadDivGraph("resource/images/Boss/BossHandsImg.png", 2, 2, 1, 200, 200,Hands_img);

	hi[0] = LoadGraph("resource/images/Boss/Boss.png",true);
	bosf[0] = LoadGraph("resource/images/Boss/BossFace.png", true);
	bosf[1] = LoadGraph("resource/images/Boss/LongTuru.png", true);
	location.x = 700;
	location.y = -500;
	erea.height = 190;
	erea.width = 190;
	switching = 0;
	down_hand = false;
	who = _who;
	count = STOPBOSS;
	Attack_Num=0;
	hp=0;
	Hit_Once = true;
	HitJumpAttack = false;
	Death_Flg = false;



	Rock_Once = true;

	if(boss->GetBossForm()==1){
		Power_Up=true;
	}
	else {
		Power_Up = false;
	}
}

BossHands::~BossHands() {
}

void BossHands::Update(GameMain* main) {

	//�}�[���^
		HandsMagenta(main);
	//�V�A��
	//�C�G���[

}

void BossHands::Draw() const {

	DrawGraphF(location.x + 100, location.y + 50, bosf[1], TRUE);
	DrawGraphF(location.x, location.y,hi[0], TRUE);


#ifdef _DEBUG
	DrawFormatString(100, 0, 0xffffff, "%d", switching);
	DrawFormatString(159, 0, 0xff00ff, "HP%d", hp);
	DrawFormatString(400, 0, 0xff00ff, "hitjump%d", HitJumpAttack);
	
#endif // _DEBUG


}

void BossHands::HandsMagenta(GameMain* main) {
		/*if (switching > 2) {
			down_hand = true;
		}*/
	
		//�{�X�̌��̍U������
	if (switching != 3) {
		Attack_Num = 0;
		BossAttack(main);
	}

		//�Ռ��g���o��
		if (hitflg == true && onceflg == true) {
			//��
			if (Power_Up == true) {
				if (Rock_Once == true) {
					Rock_Once = false;
				}
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

AttackData BossHands::BossAttactData()
{
	AttackData attack_data;
	switch (Attack_Num) {
	//�U�N���̌�
	case 0:
		attack_data.shift_x = -erea.width - 3;
		attack_data.shift_y = -30;
		attack_data.width = erea.width;
		attack_data.height = erea.height - 20;
		attack_data.who_attack = who;
		attack_data.attack_time = 30;
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
		attack_data.shift_x = 0;
		attack_data.shift_y = 0;
		attack_data.width = 0;
		attack_data.height = 0;
		attack_data.who_attack = who;
		attack_data.attack_time = 0;
		attack_data.delay = 3;
		attack_data.damage = 0;
		attack_data.attack_type =MELEE;

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
	
	if (hp < 0) {
		Death_Flg = true;
	}
}
