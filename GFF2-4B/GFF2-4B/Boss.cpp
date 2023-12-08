#include "Boss.h"

Boss::Boss() {
	LoadDivGraph("resource/images/Boss/BossBody.png", 4, 4, 1, 360, 700,Boss_MainBody);
	LoadDivGraph("resource/images/Boss/BossArm.png", 2, 2, 1, 420, 700,Boss_MainArm);
	LoadDivGraph("resource/images/Boss/explosionMini.png", 4, 4, 1, 180, 180, Explosion);

	timer = 0;
	Boss_Dieflg = false;

	Boss_Arm_Rightx=800;
	Boss_Arm_Righty=0;

	Boss_Body_X = 440;
	Boss_Body_Y = 0;

	Boss_Arm_Leftx = 100;
	Boss_Arm_Lefty = 0;

	Count_Death = 2;
	Boss_Form=0;
	Bossbody_ImgNum = 1;
	Hand_Num = 0;
	New_Hand_Flg = false;
	Boss_state = 2;
	Once_Flg = true;
	Boss_step = 0;
	Boss_Handmove = 0;
	Explosion_ImgNum = 0;
	Expl_count = 0;

	Explosion_X = Boss_Arm_Rightx;
	Explosion_Y = 0;
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {

	if (Boss_state!= BossState::Boss_M) {
		BossImgChange(main);
	}

	switch (Boss_Handmove)
	{
	case 0:
		//ヒマワリ出現
		if (Boss_Arm_Righty >-400 ) {
			Boss_Arm_Righty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 1:
		//やられたら
		//左右に揺れる
		//右腕が
		if (timer++ < 1) {
			Boss_Arm_Rightx += 10;
		}
		else {
			Boss_Arm_Rightx -= 10;
			timer = 0;
		}

		//爆発もする
		// 
		ExplosionAnim();
		break;
	case 2:
		//頭下がる
		if (Boss_Body_Y <700) {
			Boss_Body_Y += 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 3:
		//本体上がってくる
		
		if (Boss_Body_Y > 0) {
			Boss_Body_Y -= 10;
			if (timer++ < 1) {
				Boss_Body_X += 10;
			}
			else {
				Boss_Body_X -= 10;
				timer = 0;
			}

		}
		else {
			Boss_Body_Y = 0;
			Boss_Body_X = 440;
			Boss_Handmove++;
		}

		break;
	case 4:
		//左手上がる
		if (Boss_Arm_Lefty > -400) {
			Boss_Arm_Lefty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 5:
		//やられたら
		//左右に揺れる
		//左腕が
		if (timer++ < 1) {
			Boss_Arm_Leftx += 10;
		}
		else {
			Boss_Arm_Leftx -= 10;
			timer = 0;
		}

		//爆発もする
		// 

		ExplosionAnim();

		//Boss_Handmove++
		break;
	case 6:
		//頭下がる
		if (Boss_Body_Y < 700) {
			Boss_Body_Y += 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 7:
		//身体上がって来て
				//本体上がってくる
		if (Boss_Body_Y > 0) {
			Boss_Body_Y -= 10;
			if (timer++ < 1) {
				Boss_Body_X += 10;
			}
			else {
				Boss_Body_X -= 10;
				timer = 0;
			}
		}
		else {
			Boss_Body_Y = 0;
			Boss_Body_X = 440;
			Boss_Handmove++;
		}
	case 8:

		//爆発して死ぬ
		Boss_Dieflg = true;
		//if()
			//Boss_Body_X += 10;
			//Boss_Body_X -= 10;

		break;
	default:
		break;
	}



	/*
	if (Dead == false) {
		if (timer++ == 100) {
			New_Hand_Flg = true;
		}
		//Boss_Arm_Righty += timer;
		Boss_Body_Y += timer/2;

		if (i<3) {

			if (Dead == true) {
				Dead = false;
				timer = 0;
				Hand_Num = ++i;
			}

		}
		else {
			Boss_Dead = true;
		}
	}
	*/

}

void Boss::Draw() const {
	
	switch (Boss_Handmove)
	{
	case 0:
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		//DrawGraph(380, 0, Explosion[0], TRUE);
		//DrawGraph(380, 0, Explosion[1], TRUE);
		//DrawGraph(440, 0, Boss_MainBody[0], TRUE);

		//左手
		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//右手
		DrawGraph(Boss_Arm_Rightx, Boss_Arm_Righty, Boss_MainArm[1], TRUE);
		//DrawFormatString(400, 40, 0xff00ff, "Newhandsflg%d",New_Hand_Flg);
		//DrawFormatString(400, 80, 0xff00ff, "%d", timer);
		break;
	case 1:
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		DrawGraph(Explosion_X, Explosion_Y, Explosion[Explosion_ImgNum], TRUE);
		//DrawGraph(380, 0, Explosion[1], TRUE);
		//DrawGraph(440, 0, Boss_MainBody[0], TRUE);

		//左手
		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//右手
		DrawGraph(Boss_Arm_Rightx, Boss_Arm_Righty, Boss_MainArm[1], TRUE);
		//DrawFormatString(400, 40, 0xff00ff, "Newhandsflg%d",New_Hand_Flg);
		//DrawFormatString(400, 80, 0xff00ff, "%d", timer);

		break;
	case 2:
		//左手
		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);

		break;
	case 3:
		//左手

		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		break;
	case 4:
		//左手
		DrawGraph(Boss_Arm_Leftx, Boss_Arm_Lefty, Boss_MainArm[0], TRUE);

		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		break;
	case 5:
		//左手
		DrawGraph(Boss_Arm_Leftx, Boss_Arm_Lefty, Boss_MainArm[0], TRUE);
		//爆発
		DrawGraph(Explosion_X, Explosion_Y, Explosion[Explosion_ImgNum], TRUE);
		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		break;
	case 6:
		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		break;
	case 7:
		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[0], TRUE);
		break;
	case 8:
		//本体
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[3], TRUE);

		break;
	default:
		break;
	}

#ifdef _DEBUG
	//DrawFormatString(100, 500, 0xffffff, "イルカのrad = %f", iruka_rad);
	DrawFormatString(300, 300, 0xff00ff, "Boss_Body_Y%f",Boss_Body_Y);

#endif // _DEBUG
}

void Boss::BossImgChange(GameMain* main) {
	
	if (main->GetPlayerLocation().x < 426) {
		Bossbody_ImgNum = 1;
	}
	else if (main->GetPlayerLocation().x < 852) {
		Bossbody_ImgNum = 0;
	}
	else {
		Bossbody_ImgNum = 2;
	}
}

void Boss::Boss_MakeHand() {

	if(Once_Flg==true){
		if (timer++ > 100) {
			switch (Boss_step) {
			case 0:
				Boss_state = Boss_Y;
				Boss_step++;
				break;
			case 1:
				//Boss_Body_Y += 400;
					Boss_state = Boss_M;
					Boss_step++;
				break;
			case 2:
				//Boss_Body_Y += -400;
				Boss_state = Boss_C;
				Boss_step++;
				break;
			case 3:
				//Boss_Body_Y += 400;
				Boss_state = Boss_M;
				Boss_step++;
				break;
			case 4:
				//クリア処理
				break;
			}
			

			New_Hand_Flg = true;
			Hand_Num = Boss_state;
			timer = 0;
			Once_Flg = false;
		}
	}

}

void Boss::ExplosionAnim() {

	Expl_count++;
	
	switch (Expl_count)
	{
	case 0:
		Explosion_ImgNum = 0;
		break;
	case 10:
		Explosion_ImgNum = 1;
		break;
	case 12:
		Explosion_ImgNum = 2;
		break;
	case 15:
		Explosion_ImgNum = 3;
		//Expl_count = 0;
		break;
	case 50:
		Explosion_ImgNum = 0;
		Expl_count = 0;
		Boss_Handmove++;
		Explosion_Y = 0;
		break;
	default:
		break;
	}
	

}