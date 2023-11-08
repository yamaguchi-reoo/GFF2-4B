#include "BossHands.h"
#include"GameMain.h"


BossHands::BossHands(int _who) {

	LoadDivGraph("resource/images/Boss/BossHandsImg.png", 2, 2, 1, 200, 200,Hands_img);

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
}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {

	//マゼンタ
		HandsMagenta(main);


	//シアン

	//イエロー
}

void BossHands::Draw() const {
	DrawGraphF(location.x, location.y,Hands_img[0], TRUE);

#ifdef _DEBUG
	DrawFormatString(100, 0, 0xffffff, "%d", switching);
	DrawFormatString(159, 0, 0xff00ff, "HP%d", hp);
	DrawGraph(200, 300, Hands_img[1], TRUE);
//	DrawBox(-erea.width, -erea.height, erea.width, erea.height, 0xffffff, TRUE);

#endif // _DEBUG


}

void BossHands::HandsMagenta(GameMain* main) {

		/*if (switching > 2) {
			down_hand = true;
		}*/

		//ボスの拳の攻撃判定
	if (switching != 3) {
		Attack_Num = 0;
		BossAttack(main);
	}
		//衝撃波を出す
		if (hitflg == true && onceflg == true) {
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
			//地面に付いた後カウントが0より小さくなったら、次の出現位置に移動
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

		//拳を振り下ろす動き
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


		switch (switching) {
		case 0:
			location.x = Magentax[switching];
			break;
		case 1:
			location.x = Magentax[switching];
			break;
		case 2:
			location.x = Magentax[switching];
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
	//ザクロの拳
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
	//攻撃を生成する
	main->SpawnAttack(BossAttactData());

}

void BossHands::ApplyDamage(int num) {

	if (Hit_Once != false) {
		hp++;
	}
}