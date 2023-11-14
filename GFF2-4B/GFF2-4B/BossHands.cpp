#include "BossHands.h"
#include"GameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>


BossHands::BossHands(int _who,Boss* boss) {


	Hands_Img_num = 0;//イルカにしかまだ使ってないので後から
	Hands_who = 0;

	switch (Hands_who)
	{
	case 0:
		//マゼンタ
		location.x = 700;
		location.y = -500;
		hi[0] = LoadGraph("resource/images/Boss/Boss.png", true);
		count = STOPBOSS;	//振り下ろした腕が上にあがるまでとめる
		break;
	case 1:
		//シアン
		//出現位置
		Direction = 0;
		location.x = 1280;
		location.y = 700;
		LoadDivGraph("resource/images/Boss/Iruka.png", 4, 2, 2, 256, 256, Hands_img);
		count = 0;	//画像切り替え用

		break;
	case 2:
		//イエロー
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

	//強化形態になってるか？
	if(boss->GetBossForm()==1){
		//強化攻撃出すようになる

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
			//マゼンタ
			HandsMagenta(main);
			break;
		case 1:
			//シアン
			HandsCyan(main);
			break;
		case 2:
			//イエロー
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
			//マゼンタ
			DrawGraphF(location.x, location.y, hi[0], TRUE);
			break;
		case 1:
			//シアン
			if (Direction == 0) {
				DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			}
			else {
				DrawRotaGraph(location.x, location.y, 1, 0, Hands_img[Hands_Img_num], TRUE);
			}

			break;
		case 2:
			//イエロー
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

		//ボスの拳の攻撃判定
		if (switching != 3) {
			Attack_Num = 0;
			BossAttack(main);
		}

		//衝撃波を出す
		if (hitflg == true && onceflg == true) {
			//ボスが第二形態だったら
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
			//地面に付いた後カウントが0より小さくなったら、次の出現位置に移動
			if (count < 0) {
				location.y -= 10;
			}
			//次の出現位置に移動
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

		//拳出現位置セット用
		switch (switching) {
		case 0:
			//右に出現
			location.x = (float)Magentax[switching];
			break;
		case 1:
			//左に出現
			location.x = (float)Magentax[switching];
			break;
		case 2:
			//中央に出現
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
		//死亡アニメーション
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

	//最初に出現して左下に向かって落ちる
	//location.x -= 5;
	//location.y += 3;

	//if(location.x<0)
	//イルカが左をむいていたら
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
	
	//Hands_Img_num[0]左向きくち開け状態の場合
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
	//ザクロの拳0~2まで
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
		//衝撃波
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
		//攻撃を生成する
		main->SpawnAttack(BossAttactData());
	}
}

void BossHands::ApplyDamage(int num) {
	//攻撃がヒットした回数で倒れる
	if (HitJumpAttack!=true) {
		hp--;
	}
	
	if (hp <= 0) {
		Death_Flg = true;
		count = 0;
	}
}
