#include "BossHands.h"
#include"GameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>
//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg)	(M_PI*(_deg)/180.0f)

bool BossHands::Cutin_flg=false;

float checkabs=0;

BossHands::BossHands(int _who,Boss* boss) {

	//全腕共通の初期化
	frame = 0;
	Hands_Img_num = 0;//イルカ
	//Hands_who = 1;
	Hands_who = boss->Hand_Num;
	erea.height = (float)hands_height[Hands_who];
	erea.width = (float)hands_width[Hands_who];
	who = _who;
	Attack_Num = 0;
	Death_Anim = 0;
	
	Blinking_Flg = false;
	Blinking_count = 0;
	Display = false;
	zakuro_state = Z_FALLING;
	Damage_flg = false;

	Stop_Count = 120;
	Make_hpflg = false;
	hands_hp = 0;
	LoadDivGraph("resource/images/Boss/Bosshp.png",3,3,1,70,70,Hands_HPimg);
	//LoadDivGraph("resource/images/Boss/Zakuro.png", 8, 4, 2, 360, 360, Zakuro_img);

	Date.magenta = 15.0f;
	Date.cyan = 15.0f;
	Date.yellow = 15.0f;

#ifdef _DEBUG
		hp = 5;
#else
	hp = 5;
#endif // _DEBUG


	switch (Hands_who)
	{
	case 0:
		//マゼンタ初期化
		MagentaInit();
		break;
	case 1:
		//シアン初期化
		CyanInit();
		LoadDivGraph("resource/images/Boss/Irukared.png", 2, 2, 1, 256, 256, Blinking_Img);
		break;
	case 2:
		//イエロー初期化
		YellowInit();
		//LoadDivGraph("resource/images/Boss/Bosshp.png", 3, 3, 1, 50, 50, Blinking_Img);
		break;
	default:
		break;
	}

	//強化形態になってるか？
	if (boss->GetBossForm() == 1) {
		//強化攻撃出すようになる

		Power_Up = true;
	}
	else {
		Power_Up = false;
	}
}

BossHands::~BossHands() {
}

void BossHands::Update(GameMain* main) {

	//フレーム測定
	if (++frame > 1200)frame = 0;

	if (Make_hpflg != true) {
		Stop_Count -= 10;
		switch (Stop_Count)
		{
		case 120:
			hands_hp = 0;
			break;
		case 80:
			hands_hp = 1;
			break;
		case 40:
			hands_hp = 2;
			break;
		case 0:
			hands_hp = 3;
			break;
		default:
			break;
		}
		if (Stop_Count < -40) {
			Make_hpflg = true;
			Stop_Count = 120;
		}
	}
	else {
		//手の種類に応じて実行するUpdateを変える
		Blinking();

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
			HandsYellow(main);
			break;
		default:
			break;
		}
	}
}

void BossHands::Draw() const {

	if (Make_hpflg != true) {
	}
	else {
		switch (Hands_who)
		{
		case 0:
			//マゼンタ
			DrawRotaGraphF(location.x + 150, location.y + 170, 1, Zakuro_rad, Zakuro_img[Zakuro_Imgnum], TRUE, Zakuro_Direction);

			if (Death_Flg == false) {
				if (zakuro_state == BossZakuroState::Z_FAINTING && F_switching == 1) {
					DrawGraphF(location.x + 150, location.y - 40, Fainting_img[CF], TRUE);
				}
			}

			if (Display == true) {
				DrawRotaGraphF(location.x + 150, location.y + 170, 1, Zakuro_rad, Zakurored_img[Zakuro_Imgnum], TRUE, Zakuro_Direction);
			}

		

			if (zakuro_state == Z_CUTIN) {
				DrawCutin();
			}
			break;
		case 1:
			//シアン
			DrawRotaGraphF(turu_location.x, turu_location.y, 1, turu_rad, turu_img, TRUE, FALSE);
			if (face_angle > 0.0f && face_angle < 0.7f)
			{
				DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, iruka_rad, Hands_img[Hands_Img_num], TRUE, TRUE);

				/*if (Display == true) {
					DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, iruka_rad, Blinking_Img[Hands_Img_num], TRUE, TRUE);
				}*/
			}
			else
			{
				DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, iruka_rad, Hands_img[Hands_Img_num], TRUE, TRUE);

			/*	if (Display == true) {
					DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, iruka_rad, Blinking_Img[Hands_Img_num], TRUE, TRUE);
				}*/
			}


			break;
		case 2:
			//イエロー
			DrawRotaGraphF(turu_location.x, turu_location.y, 1, turu_rad, turu_img, TRUE, FALSE);
			if (hima_state != BossHimawariState::SF_DOWN)
			{
				DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, face_angle * M_PI * 2, Hands_img[Hands_Img_num], TRUE, TRUE);
				//if (Display == true) {
				//	DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xff0000, true);
				//}
			}
			else
			{
				DrawRotaGraphF(local_location.x + 75, local_location.y + 75, 1, face_angle * M_PI * 2, Hands_img[Hands_Img_num], TRUE, TRUE);				
				//if (Display == true) {
				//	DrawBoxAA(local_location.x + GetRand(10), local_location.y + GetRand(10), local_location.x + erea.width + GetRand(10), local_location.y + erea.height + GetRand(10), 0xff0000, true);

				//}
			}
			break;
		default:
			break;
		}


	}

#ifdef _DEBUG
	//DrawFormatString(100, 500, 0xffffff, "イルカのrad = %f", iruka_rad);
	DrawFormatString(159, 0, 0xff00ff, "HP%d", hp);
	//DrawFormatString(400, 0, 0xff00ff, "hitjump%d", HitJumpAttack);
	
	DrawFormatString(100, 400, 0xffffff, "location.y%f",location.y);
	DrawFormatString(100, 450, 0xffffff, "zakuro_state%d",zakuro_state);
	DrawFormatString(100, 470, 0xffffff, "hitflg%d",hitflg);
	DrawFormatString(100, 500, 0xffffff, "location.x%f", location.x);
	DrawFormatString(400, 550, 0xffffff, "Zakuroy%f", Old_Zakuroy-location.y);
#endif // _DEBUG
}

void BossHands::HandHp() const {
	SetFontSize(40);
	DrawString(450, 670, "BOSS", 0x0000ff);

	if (Make_hpflg != true) {
		switch (hands_hp) {
		case 0:
			DrawGraph(530, 650, Hands_HPimg[Hands_who], TRUE);
			break;
		case 1:
			DrawGraph(530, 650, Hands_HPimg[Hands_who], TRUE);
			DrawGraph(530 + 50, 650, Hands_HPimg[Hands_who], TRUE);
			break;
		case 2:
			for (int i = 0; i < 3; i++) {
				DrawGraph(530 + i * 50, 650, Hands_HPimg[Hands_who], TRUE);
			}
			break;
		case 3:
			for (int i = 0; i < 4; i++) {
				DrawGraph(530 + i * 50, 650, Hands_HPimg[Hands_who], TRUE);
			}
			break;
		default:
			break;
		}
	}
	else {
		//HP表示
		for (int i = 0; i < hp; i++) {
			DrawGraph(530 + i * 50, 650, Hands_HPimg[Hands_who], TRUE);
		}
		SetFontSize(40);
	}
}

void BossHands::Blinking() {
	if (Blinking_Flg == true) {
		switch (Blinking_count++) {
		case 0:
			Display = true;
			break;
		case 10:
			Display = false;
			Blinking_Flg = false;
			Blinking_count = 0;
			break;
		default:
			break;
		}
	}
}

void BossHands::MagentaInit()
{
	zakuro_state = BossZakuroState::Z_ANIM_UP;
	Zakuro_Direction = 0;
	Zakuro_Imgnum = 0;
	Zwalk_count = 0;
	Stop_Count = 120;
	location.x = 900;
	location.y = 700;
	Set_Zakuro_x = 0;
	Set_Zakuro_y = 0;
	g = 9.8f;
	sita = 60;
	V_zero = 200;
	time = 0;
	rad=sita*pi/180;//ラジアンに変換
	LoadDivGraph("resource/images/Boss/Zakuro.png", 6, 6, 1, 360, 360, Zakuro_img);
	LoadDivGraph("resource/images/Boss/Zakurored.png", 6, 6, 1, 360, 360, Zakurored_img);
	LoadDivGraph("resource/images/Boss/kizetu.png", 2, 2, 1, 120, 50, Fainting_img);
	LoadDivGraph("resource/images/Boss/KatinZ.png", 2, 2, 1, 640, 720, Cutin_img);
	LoadDivGraph("resource/images/Boss/Kback.png", 2, 2, 1, 640, 720, Cutin_backimg);

	Font_img=LoadGraph("resource/images/Boss/Hazi.png");

	count = STOPBOSS;	//振り下ろした腕が上にあがるまでとめる
	switching = 0;
	HitJumpAttack = false;
	Death_Flg = false;
	Rock_Once = false;
	hitflg = false;
	Jump_Num = -1;
	Jump_Once = true;
	Jump_Flg = false;
	Zakuro_rad = 0;
	Go_Flg = false;
	Charge = 0;
	Rush_speed = 0;
	CF = 0;
	Cutflg = false;
	x1 = -450;
	x2 =1100;
	CO = 0;
	//Cutin_flg = false;
	F_switching = 0;
	F_count = 700;
	alpha = 0;
}

void BossHands::JumpInit() {
	g = 980;
	sita = 70;
	V_zero = 700;
	rad = sita * pi / 180;//ラジアンに変換
	time = 0.0167;
	Set_Zakuro_x = location.x;
	Set_Zakuro_y = location.y;

	Old_Zakuroy = 0;
}

void BossHands::Zwalk() {

	if (zakuro_state == Z_RUSH) {
		switch (Zwalk_count)
		{
		case 3:
			Zakuro_Imgnum = 0;
			break;
		case 6:
			Zakuro_Imgnum = 1;
			break;
		case 9:
			Zakuro_Imgnum = 2;
			break;
		case 12:
			Zwalk_count = 0;
			break;
		default:
			break;
		}
	}
	else {
		switch (Zwalk_count)
		{
		case 5:
			Zakuro_Imgnum = 0;
			break;
		case 15:
			Zakuro_Imgnum = 1;
			break;
		case 25:
			Zakuro_Imgnum = 2;
			break;
		case 35:
			Zwalk_count = 0;
			break;
		default:
			break;
		}
	}

	Zwalk_count++;

}

void BossHands::HandsMagenta(GameMain* main) {

	if (Death_Flg == false) {

		switch (zakuro_state) {
		case BossZakuroState::Z_ANIM_UP:
			Zakuro_Imgnum = 3;
			if (location.y < -500) {
				zakuro_state = BossZakuroState::Z_FALLING;
			}
			else {
				location.y -= 15;
			}
			break;
		case BossZakuroState::Z_MOVE:
			
			Zwalk();
			Zakuro_rad = 0;

			if (hitflg == true) {
				if (Zakuro_Direction == 0 && location.x<700) {
					if (location.x> main->GetPlayerLocation().x) {
						Zwalk_count = 0;
						zakuro_state = Z_NOCKBACK;
					}
					else {
						hitflg = false;
					}
				}
				else if (Zakuro_Direction == 1 && location.x > 300) {
					if (location.x < main->GetPlayerLocation().x) {
						Zwalk_count = 0;
						zakuro_state = Z_NOCKBACK;
					}
					else {
						hitflg = false;
					}
				}
				else {
					hitflg = false;
				}
		}
			else {
				Attack_Num = 4;
				BossAttack(main);

				if (location.x > 900) {
					Zakuro_Direction = 0;
					//Jump_Once = true;
					//Jump_Num = 0 + rand() % 3;
				}
				else if (location.x < 0) {
					Zakuro_Direction = 1;
					//Jump_Once = true;
					//Jump_Num = 0 + rand() % 3;
				}

				if (Zakuro_Direction == 0) {
					location.x -= 5;
				}
				else {
					location.x += 5;
				}

				//float a = main->GetPlayerLocation().x - location.x;
				checkabs = fabsf(main->GetPlayerLocation().x - location.x);

				//if (fabsf(main->GetPlayerLocation().x - location.x)<200) {
				//	checkabs = fabsf(main->GetPlayerLocation().x - location.x+180);
				//}
				/*
				if (Jump_Once == true) {
					if (location.x > 426 && location.x < 752) {

						//if (0 + rand() % 100 == 0) {
						//onceflg = true;
						//}
						//if (onceflg == true) {
						//	//ジャンプはいる前に初期化
						//	JumpInit();
						//		zakuro_state = BossZakuroState::Z_JUMP_RIGHT;
						//		Jump_Count++;
						//		onceflg = false;
						//}
						//
						//if (Jump_Count == 0) {
						//	JumpInit();
						//	zakuro_state = BossZakuroState::Z_JUMP_RIGHT;
						//	Jump_Count++;
						//
						//}

						//Jump_Once = false;
						////Jump_Num = 0 + rand() % 3;
						Jump_Num = 2;
						//zakuro_state = Z_JUMP_RIGHT;
						//プレイヤーとの距離いくらかに入り込んで来たら
						//そっから区分分けしてジャンプする

						switch (Jump_Num) {
						case 0:
							if (location.x >= 426 && location.x <= 507) {
								Jump_Once = false;
								JumpInit();
								zakuro_state = Z_JUMP_RIGHT;
							}
							break;
						case 1:
							if (location.x > 557 && location.x <= 589) {
								Jump_Once = false;
								JumpInit();
								zakuro_state = Z_JUMP_RIGHT;
							}
							break;
						case 2:
							if (location.x > 600 && location.x <= 670) {
								Jump_Once = false;
								JumpInit();
								zakuro_state = Z_JUMP_RIGHT;
							}
							break;
						case 3:
							if (location.x > 700 && location.x <= 752) {
								Jump_Once = false;
								JumpInit();
								zakuro_state = Z_JUMP_RIGHT;
							}
							break;
						default:
							break;
						}

					}
				}
				*/
			}

			break;
			/*
		case BossZakuroState::Z_JUMP_RIGHT:

			Old_Zakuroy = location.y;

			//右ジャンプ
				Zakuro_Movex = V_zero * cosf(rad) * time;
				Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;
				if (location.x > 1200)location.x = Set_Zakuro_x + Zakuro_Movex;
				if (location.y < 320)location.y = Set_Zakuro_y + Zakuro_Movey;

				time += 0.01f;

				if (location.y > 320) {
					zakuro_state = BossZakuroState::Z_MOVE;
					Jump_Flg = false;
					hitflg = false;
					location.y = 310;
				}

				//ザクロジャンプ画像切り替え
				if (Old_Zakuroy - location.y > 0) {
					Zakuro_Imgnum = 1;
				}
				else {
					Zakuro_Imgnum = 2;
				}

			break;
		case BossZakuroState::Z_JUMP_LEFT:
			/*
			Zakuro_Movex = V_zero * cosf(rad) * time;
			Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;
			if (location.x > 0)location.x = Set_Zakuro_x - Zakuro_Movex;
			if (location.y < 320)location.y = Set_Zakuro_y + Zakuro_Movey;

			time += 0.01f;
			if (location.y>320) {
				zakuro_state = BossZakuroState::Z_MOVE;
				location.y = 310;
			}
			
			break;
			*/
		case BossZakuroState::Z_FALLING:
			Zakuro_Imgnum = 4;
			Attack_Num = 4;
			BossAttack(main);
			if (location.y>310) {
				//Attack_Num = 1;
				//BossAttack(main);
				//Attack_Num = 2;
				//BossAttack(main);
				//zakuro_state = BossZakuroState::Z_FAINTING;
				hitflg = false;
				zakuro_state = BossZakuroState::Z_MOVE;
			}
				location.y += 10;
			break;
		case BossZakuroState::Z_ANIM_RUSH:

			Damage_flg = true;
			RushStartAnim();
			break;
		case BossZakuroState::Z_RUSH:
			Attack_Num = 4;
			BossAttack(main);

			if (--Stop_Count < -50) {
				Zakuro_rad = 0;
				Damage_flg = false;
				Zwalk();

				//右に向かって突進
				if (Zakuro_Direction == 0) {
					if (hitflg == true) {
						location.x += 20;
						location.y -= 20;

						if (location.x < 1300 && location.y < -400) {
							hitflg = false;
							location.x = 640;
							location.y = -500;
							Zakuro_Direction = 1;
							F_switching = 0;
							zakuro_state = Z_FAINTING;
						}

					}
					else {
						location.x -= Rush_speed;
					}

					if (location.x < -100) {
						hitflg = false;
						location.x = 640;
						location.y = -500;
						Zakuro_Direction = 1;
						zakuro_state = Z_FALLING;
					}
				}
				else {
					//左に向かって突進
					if (hitflg == true) {
						location.x -= 20;
						location.y -= 20;

						if (location.x < -100 && location.y < -400) {
							hitflg = false;
							Zakuro_Direction = 0;

							location.x = 640;
							location.y = -500;
							zakuro_state = Z_FAINTING;
						}

					}
					else {
						location.x += Rush_speed;
					}

					if (location.x > 1300) {
						hitflg = false;
						Zakuro_Direction = 0;
						location.x = 600;
						location.y = -500;
						zakuro_state = Z_FALLING;
					}
				}
			}
			else {
				Damage_flg = true;
				hitflg = false;
			}

			break;
		case Z_NOCKBACK:
			Damage_flg = true;
			Zakuro_rad += 7;
			NockBack();

			break;
		case Z_CUTIN:

			switch (CO)
			{
			case 0:
				//ザクロ
				if (x2 > 640)
				{
					x2 -= 20;
					x1 += 20;
				}
				else
				{
					Cutflg = true;
					CO++;
				}
				break;
			case 1:
				Stop_Count -= 6;
				if (Stop_Count < 50)
				{
					Stop_Count = 120;
					CO++;
				}

				break;
			case 2:
				//文字表示
				if (--Stop_Count > 50)
				{
					if (alpha < 255) {
						alpha += 30;
					}
				}
				else {
					if (x2 < 1100)
					{
						x2 += 30;
						x1 -= 30;
					}else {
						CO = 0;
						Stop_Count = 120;
						Cutflg = false;
						Damage_flg = false;
						//Zakuro_rad = 0;
						zakuro_state = Z_RUSH;
					}
				}
				break;
			default:
				break;
			}

			break;
		case Z_FAINTING:
			//吹き飛ばされたのち落下
			switch (F_switching)
			{ 
			case 0:
				//落下してくる
				Damage_flg = true;
				Zakuro_Imgnum = 5;
				if (location.y > 340){
					Damage_flg = false;
					F_switching++;
				}
				location.y += 10;

				break;
			case 1:
				//気絶
				//かけよって4撃突っ込めるぐらいの時間
				Zakuro_Imgnum = 5;
				F_count -= 5;
				if (F_count > 0) {
					switch (Stop_Count) {
					case 120:
						CF = 0;
						break;
					case 60:
						CF = 1;
						break;
					default:
						break;
					}

					Stop_Count -= 10;
					if (Stop_Count < 0) {
						Stop_Count = 120;
					}
				}
				else {
					Stop_Count = 120;
					F_count = 700;
					F_switching++;
				}

				break;
			case 2:

				Damage_flg = true;
				Zakuro_Imgnum = 3;
					switch (Stop_Count) {
					case 120:
						Zakuro_Direction=0;
						break;
					case 60:
						Zakuro_rad = 0;
						Zakuro_Direction=1;
						break;
					case 40:
						Zakuro_Direction = 0;
						break;
					case 0:
						Stop_Count = 120;
						Damage_flg = false;
						hitflg = false;
						zakuro_state = Z_ANIM_UP;
						break;
					default:
						break;
					}

					Stop_Count -= 5;
					if (Stop_Count < 0) {
						Stop_Count = 120;
					}


				break;
			default:
				break;
			}

			break;
		default:
			break;
		}

	}
	else if(Death_Flg==true) {
		//死亡アニメーション
		switch (Death_Anim) {
			Zakuro_Imgnum = 5;
		case 0:
			if (location.y < 700) {
				Zakuro_rad += 7;
				location.y += 5;
			}
			else {
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

void BossHands::DrawCutin()const {


	switch (CO)
	{
	case 0:
		//ザクロ
		DrawGraphF(x2, 0, Cutin_img[1], TRUE);
		//プレイヤー
		DrawGraphF(x1, 0, Cutin_img[0], TRUE);
		break;
	case 1:
		//ザクロ
		DrawGraphF(x2, 0, Cutin_img[1], TRUE);
		//プレイヤー
		DrawGraphF(x1, 0, Cutin_img[0], TRUE);

		break;
	case 2:
		DrawGraphF(x2, 0, Cutin_backimg[1], TRUE);
		DrawGraphF(x1, 0, Cutin_backimg[0], TRUE);

		if (Stop_Count > 50)
		{
			//文字表示
			//透明度設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawGraph(420, 300, Font_img, TRUE);
			//透明度を元に戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else {

		}
		break;
	default:
		break;
	}


}

void BossHands::RushStartAnim() {
	
	Stop_Count -= 1;
	if (Go_Flg == false) {
		if (Zakuro_Direction == 0) {
			switch (Stop_Count) {
			case 60:
				Zakuro_rad = pi / -10;
				location.x += 30;
				break;
			case 50:
				Zakuro_rad = pi / -5;
				location.x += 50;
			case 40:
				Stop_Count = 120;
				//zakuro_state = Z_RUSH;
				Go_Flg = true;
				Charge = GetRand(1);
				break;
			default:
				break;
			}
		}
		else {
			switch (Stop_Count) {
			case 50:
				location.x -= 30;
				Zakuro_rad = pi / 10;
				break;
			case 20:
				location.x -= 50;
				Zakuro_rad = pi / 5;
				break;
			case 0:
				Stop_Count = 120;
				Charge = GetRand(1);
				Go_Flg = true;
				break;
			default:
				break;
			}

		}
	}
	else {

		if (Cutin_flg == false) {
			Stop_Count = 120;
			Cutin_flg = true;
			Go_Flg = false;
			Rush_speed = 20;
			zakuro_state = Z_CUTIN;
		}

		switch (Charge)
		{
		case 0:
			if (Stop_Count == 70) {
				zakuro_state = Z_RUSH;
				Stop_Count = 120;
				Go_Flg = false;
				Rush_speed = 20;
			}
			break;
		case 1:
			if (Stop_Count == 80) {
				zakuro_state = Z_RUSH;
				Stop_Count = 120;
				Go_Flg = false;
				Rush_speed = 15;
			}
			break;
		case 2:
			if (Stop_Count == 90) {
				zakuro_state = Z_RUSH;
				Stop_Count = 120;
				Go_Flg = false;
				Rush_speed = 10;
			}
			break;
		default:
			if (Stop_Count == 100) {
				zakuro_state = Z_RUSH;
				Stop_Count = 120;
				Go_Flg = false;
				Rush_speed = 5;
			}
			break;
		}
	}


}

void BossHands::NockBack()
{
	if (Zakuro_Direction == 0) {
		Zakuro_rad = pi / 10;
	}
	else {
		Zakuro_rad = pi / -10;
	}

	//左移動
	if (Zakuro_Direction==0)
	{
		location.x += 10 * 0.8f;
	}
	//右移動
	if (Zakuro_Direction ==1)
	{
		location.x -= 10 * 0.8f;
	}

	Stop_Count -= 5;

	if (Stop_Count <= 0)
	{
		Damage_flg = false;
		hitflg = false;
		zakuro_state = Z_ANIM_RUSH;
		Zakuro_rad = 0;
		Stop_Count = 120;
	}

}

void BossHands::YellowInit()
{
	//ひまわり
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
	LoadDivGraph("resource/images/Boss/ヒマワリボス　全部.png", 3, 3, 1, 256, 256, Hands_img);
	turu_img = LoadGraph("resource/images/Boss/LongLongTuru.png", true);
	turu_location = { 0,0 };
	turu_rad = 0;
}

void BossHands::HandsYellow(GameMain* main)
{

	turu_rad = atan2f(local_location.y, local_location.x - SCREEN_WIDTH);
	turu_location.x = local_location.x + (erea.width / 2) - (640 * cosf(turu_rad));
	turu_location.y = local_location.y + (erea.height / 2) - (640 * sinf(turu_rad));
	Hands_Img_num = 0;
	if ((attack_cd >= 25 && attack_cd <= 30) || (attack_combo >= 6 && attack_combo <= 10))
	{
		Hands_Img_num = 2;
	}
	if ((attack_cd >= 1 && attack_cd <= 5) || (attack_combo >= 1 && attack_combo <= 5))
	{
		Hands_Img_num = 1;
	}
	//生きているなら
	if (Death_Flg == false) {

		//胴体の当たり判定
		Attack_Num = 0;
		BossAttack(main);

		//顔の向きを画面中央下に固定
		angle_width = (SCREEN_WIDTH / 2) - location.x;
		angle_height = (SCREEN_HEIGHT-erea.height) - location.y;
		rad = atan2f(angle_height, angle_width);
		face_angle = (float)(rad / M_PI / 2);

		//ひまわりの状態に応じて行動を変える
		switch (hima_state)
		{
			//待機
		case BossHimawariState::SF_WAIT:
			//移動前の立ち位置を保存
			if (location.x > (SCREEN_WIDTH / 2))
			{
				pos = false;
			}
			else
			{
				pos = true;
			}
			//待機状態が終わったなら
			if (--timer < 0)
			{
				//加速度リセット
				acceleration = 0;
				//移動開始
				hima_state = BossHimawariState::SF_MOVE;
			}
			break;
			//移動
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
				//移動を行った回数を測定
				move_count++;
				//各移動用変数リセット
				location.y = 500;
				move_angle = 0.75f;
				//一定回数移動下ならダウン状態へ、それ以下なら待機状態へ
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
				attack_cd = 31;
			}
			break;
			//やられ
		case BossHimawariState::SF_DOWN:
			//移動前の立ち位置を保存
			if (location.x > (SCREEN_WIDTH / 2))
			{
				pos = false;
			}
			else
			{
				pos = true;
			}
			//待機状態が終わったなら
			if (--timer < 0)
			{
				//加速度リセット
				acceleration = 0;
				//移動開始
				hima_state = BossHimawariState::SF_MOVE;
			}
			break;
		default:
			break;
		}
	}
	else //死んでいるなら
	{
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

void BossHands::CyanInit()
{
	//1%の確率で没イルカ挙動
	if (GetRand(99) == 0)
	{
		rare_flg = true;
		timer = 30;
	}
	else
	{
		rare_flg = false;
		timer = 0;
	}		
	//出現位置
	iruka_state = BossIrukaState::D_WAIT;
	lottery_once = false;
	location.x = SCREEN_WIDTH - erea.width + 10;
	location.y = 50;
	face_angle = 0.5f;
	iruka_rad = 0;
	turu_rad = 0;
	ref_num = 0;
	/*LoadDivGraph("resource/images/Boss/Iruka.png", 4, 2, 2, 256, 256, Hands_img);*/
	LoadDivGraph("resource/images/Boss/BossIruka.png", 2, 2, 1, 256, 256, Hands_img);
	turu_img = LoadGraph("resource/images/Boss/LongLongTuru.png", true);
	count = 0;	//画像切り替え用
	turu_location = { 0,0 };
	Death_Flg = false;
	acceleration = 0;
	tackle_num = 0;
}

void BossHands::HandsCyan(GameMain* main) {

	//仮
	//つるの描画位置を計算

	turu_rad = atan2f(local_location.y, local_location.x - SCREEN_WIDTH);
	turu_location.x = local_location.x + (erea.width / 2) - (650 * cosf(turu_rad)) - (100 * cosf(iruka_rad));
	turu_location.y = local_location.y + (erea.height / 2) - (650 * sinf(turu_rad)) - (100 * sinf(iruka_rad));

	//アニメーション用
	if (
		(iruka_state == BossIrukaState::D_WAIT && frame % 12 == 0 && timer <= 0 && rare_flg==false) ||
		(iruka_state == BossIrukaState::D_DASH && frame % 3 == 0 && timer <= 0) || 
		(iruka_state == BossIrukaState::D_MOVE && frame % 10 == 0 && timer <= 0) ||
		(iruka_state == BossIrukaState::D_RISE && frame % 10 == 0 && timer <= 0)
		)
	{
		if (++Hands_Img_num > 1)
		{
			Hands_Img_num = 0;
		}
	}
		//生きているなら
	if (Death_Flg == false) {
		//胴体の当たり判定
		Attack_Num = 0;
		BossAttack(main);
		switch (iruka_state)
		{
		case BossIrukaState::D_WAIT:
			if (rare_flg == true)
			{
				//右上に帰る
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
			}
			else
			{
				//いるかを加速させる
				if (acceleration < 60)
				{
					acceleration++;
				}
				//顔の角度が0~1の範囲内から出ないように
				if (face_angle > 1)face_angle -= 1;
				if (face_angle < 0)face_angle += 1;
				//移動距離計算
				iruka_rad = face_angle * (float)M_PI * 2;
				location.x += (acceleration * 0.22f) * cosf(iruka_rad);
				location.y += (acceleration * 0.22f) * sinf(iruka_rad);
				if (location.x > SCREEN_WIDTH - erea.width)
				{
					location.x = SCREEN_WIDTH - erea.width;
					face_angle = face_angle - 0.5f;
					ref_num++;
					main->ImpactCamera(5);
				}
				if (location.x < 0)
				{
					location.x = 0;
					face_angle = face_angle - 0.5f;
					ref_num++;
					main->ImpactCamera(5);
				}
				if (main->GetPlayerLocation().x > location.x - 50 && main->GetPlayerLocation().x < location.x + 50 && ref_num>0)
				{
					if (lottery_once == false)
					{
						if (GetRand(1) == 0)
						{
							if (tackle_num > 2)
							{
								tackle_num = 0;
								ref_num = 0;
								iruka_state = BossIrukaState::D_DASH;
								timer = 100;
								acceleration = 90;
							}
							else
							{
								ref_num = 0;
								iruka_state = BossIrukaState::D_MOVE;
								timer = 50;
								acceleration = 70;
							}
						}
						lottery_once = true;
					}
				}
				else
				{
					lottery_once = false;
				}
			}
			break;
		case BossIrukaState::D_MOVE:
			if (rare_flg == true)
			{
				if (--timer < 0)
				{
					//いるかを加速させる
					if (acceleration < 60)
					{
						acceleration++;
					}
					//顔の角度が0~1の範囲内から出ないように
					if (face_angle > 1)face_angle -= 1;
					//移動距離計算
					iruka_rad = face_angle * (float)M_PI * 2;
					location.x += (acceleration * 0.22f) * cosf(iruka_rad);
					location.y += (acceleration * 0.22f) * sinf(iruka_rad);
					//壁に反射
					if (location.x < 0)
					{
						location.x = 0;
						face_angle = GetRandAngle(0);
						ref_num++;
						timer = 20;
						iruka_rad = face_angle * (float)M_PI * 2;
						main->ImpactCamera(10);
					}
					else if (location.x > SCREEN_WIDTH - erea.width)
					{
						location.x = SCREEN_WIDTH - erea.width;
						face_angle = GetRandAngle(1);
						ref_num++;
						timer = 20;
						iruka_rad = face_angle * (float)M_PI * 2;
						main->ImpactCamera(10);
					}
					else if (location.y < 0)
					{
						location.y = 0;
						face_angle = GetRandAngle(2);
						ref_num++;
						timer = 20;
						iruka_rad = face_angle * (float)M_PI * 2;
						main->ImpactCamera(10);
					}
					else if (location.y > SCREEN_HEIGHT - erea.height)
					{
						location.y = SCREEN_HEIGHT - erea.height;
						face_angle = 1 - face_angle;
						iruka_rad = face_angle * (float)M_PI * 2;
						main->ImpactCamera(10);
					}
				}
				//5回床以外に反射したら大技
				if (ref_num > 5)
				{
					iruka_state = BossIrukaState::D_DASH;
					timer = 50;
					acceleration = 70;
					ref_num = 0;
				}
			}
			else
			{
				if (--timer > 0)
				{
					if (face_angle < 0.24f)
					{
						face_angle += 0.01f;
						iruka_rad = face_angle * (float)M_PI * 2;
					}
					else if (face_angle > 0.26f)
					{
						face_angle -= 0.01f;
						iruka_rad = face_angle * (float)M_PI * 2;
					}
					else
					{
						face_angle = 0.25f;
					}
				}
				else
				{
					//顔の角度が0~1の範囲内から出ないように
					if (face_angle > 1)face_angle -= 1;
					//移動距離計算
					iruka_rad = face_angle * (float)M_PI * 2;
					location.x += (acceleration * 0.22f) * cosf(iruka_rad);
					location.y += (acceleration * 0.22f) * sinf(iruka_rad);
					if (location.y > SCREEN_HEIGHT - erea.height)
					{
						tackle_num++;
						location.y = SCREEN_HEIGHT - erea.height;
						acceleration = 70;
						iruka_state = BossIrukaState::D_RISE;
						timer = 30;
						main->ImpactCamera(10);
					}
				}
			}
			break;
		case BossIrukaState::D_RISE:
			if (--timer > 0)
			{
				if (face_angle < 0.5f)
				{
					face_angle += 0.04f;
				}
				else if (face_angle < 0.74f)
				{
					face_angle += 0.02f;
				}
				else if (face_angle > 0.76f)
				{
					face_angle -= 0.02f;
				}
				else
				{
					face_angle = 0.75f;
				}
				iruka_rad = face_angle * (float)M_PI * 2;
			}
			else
			{
				//顔の角度が0~1の範囲内から出ないように
				if (face_angle > 1)face_angle -= 1;
				//移動距離計算
				iruka_rad = face_angle * (float)M_PI * 2;
				location.x += (acceleration * 0.22f) * cosf(iruka_rad);
				location.y += (acceleration * 0.22f) * sinf(iruka_rad);
				if (location.y < 50)
				{
					location.y = 50;
					if (GetRand(1) == 0)
					{
						face_angle = 0.5f;
					}
					else
					{
						face_angle = 0;
					}
					acceleration = 0;
					iruka_state = BossIrukaState::D_WAIT;
				}
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
					main->ImpactCamera(20);
				}
				else if (location.x > SCREEN_WIDTH - erea.width)
				{
					location.x = SCREEN_WIDTH - erea.width;
					ref_num++;
					main->ImpactCamera(20);
				}
				else if (location.y < 0)
				{
					location.y = 0;
					ref_num++;
					main->ImpactCamera(20);
				}
				else if (location.y > SCREEN_HEIGHT - erea.height)
				{
					location.y = SCREEN_HEIGHT - erea.height;
					ref_num++;
					main->ImpactCamera(20);
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
				if (rare_flg == false)
				{
					acceleration = 70;
					iruka_state = BossIrukaState::D_RISE;
					timer = 70;
				}
				else
				{
					iruka_state = BossIrukaState::D_WAIT;
					timer = 50;
				}
			}
			break;
		default:
			break;
		}
		
	}
	else //死んでいるなら
	{
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
		attack_data.shift_x = -erea.width/2;
		attack_data.shift_y = 200;
		attack_data.width = erea.width/2;
		attack_data.height = erea.height / 4;
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
		attack_data.shift_x = -erea.width/2;
		attack_data.shift_y = 200;
		attack_data.width = erea.width/2;
		attack_data.height = erea.height / 4;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 3;
		attack_data.damage = 1;
		attack_data.attack_type = BULLET;
		attack_data.speed = 3;
		attack_data.angle = 1.0;
		attack_data.direction = false;
		break;
		//ひまわり弾
	case 3:
		attack_data.shift_x = -erea.width/2;
		attack_data.shift_y = 0;
		attack_data.width = 70;
		attack_data.height = 70;
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
		//攻撃を生成する
		main->SpawnAttack(BossAttactData());
	}
}

void BossHands::ApplyDamage(int num) {
	//攻撃がヒットした回数で倒れる
	//if (HitJumpAttack!=true) {
			hitflg = true;

			if (Damage_flg == false) {
				if (Blinking_Flg == false) {
					Blinking_Flg = true;
				}

				hp--;
				impact = 10;
			}
	//}
	
	if (hp <= 0) {
		Death_Flg = true;
		count = 0;
	}
}

float BossHands::GetRandAngle(int _wall)
{
	switch (_wall)
	{
		//左壁
	case 0:
		//0から0.2、0.8から1の中からランダムな値を返す
		return fabsf(GetRand(1) - (GetRand(20) * 0.01f));
		//右壁
	case 1:
		//0.3から0.7の中からランダムな値を返す
		return (GetRand(40) * 0.01f) + 0.3f;
		//上壁
	case 2:
		//0.05から0.45の中からランダムな値を返す
		return (GetRand(40) * 0.01f) + 0.05f;
		break;
	}

	return 0;
}

ColorDate BossHands::GetColorDate()
{
	return Date;
}
