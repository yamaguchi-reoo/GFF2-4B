#include "Boss.h"

Boss::Boss() {
	LoadDivGraph("resource/images/Boss/BossBody.png", 3, 3, 1, 360, 700,Boss_MainBody);
	LoadDivGraph("resource/images/Boss/BossArm.png", 2, 2, 1, 420, 700,Boss_MainArm);
	LoadDivGraph("resource/images/Boss/explosionMini.png", 2, 2, 1, 160, 160, Explosion);

	timer = 0;


	Boss_Arm_Rightx=800;
	Boss_Arm_Righty=0;

	Boss_Body_X = 440;
	Boss_Body_Y = 0;

	Count_Death = 2;
	Boss_Form=0;
	Bossbody_ImgNum = 1;
	Hand_Num = 0;
	New_Hand_Flg = false;
	Boss_state = 2;
	Once_Flg = true;
	Boss_step = 0;
	Boss_Handmove=0;
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
		//�q�}�����o��
		if (Boss_Arm_Righty >-400 ) {
			Boss_Arm_Righty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 1:
		//���ꂽ��
		//���E�ɗh���
		//�E�r��

		Boss_Arm_Rightx += 10;
		Boss_Arm_Rightx -= 20;
		//����������
		// 
		//������r
		//Boss_Handmove++
		break;
	case 2:
		//��������
		if (Boss_Arm_Righty > -400) {
			Boss_Arm_Righty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 3:
		//�g�̏オ���Ă���
		//Boss_Handmove++
		break;
	case 4:
		//����オ��
		if (Boss_Arm_Righty > -400) {
			Boss_Arm_Righty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	case 5:
		//���E�ɗh���
		//�E�r��

		Boss_Arm_Rightx += 10;
		Boss_Arm_Rightx -= 20;
		//����������
		// 
		//������r
		//Boss_Handmove++
		break;
	case 6:
		//��������
		if (Boss_Arm_Righty > -400) {
			Boss_Arm_Righty -= 10;
		}
		else {
			Boss_MakeHand();
		}
		break;
	default:
		break;
	}

	switch (Boss_state) {
	case BossState::Boss_M:
		//�{�X�̊璾�߂ăU�N���̊炾���o��
		break;
	case BossState::Boss_C:
		//�E�r���ɂ���ă{�X�o��
		break;
	case BossState::Boss_Y:
		//���r�����ɂ����
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

		//����
		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//�E��
		DrawGraph(Boss_Arm_Rightx, Boss_Arm_Righty, Boss_MainArm[1], TRUE);
		//DrawFormatString(400, 40, 0xff00ff, "Newhandsflg%d",New_Hand_Flg);
		//DrawFormatString(400, 80, 0xff00ff, "%d", timer);
		break;
	case 1:
		DrawGraph(Boss_Body_X, Boss_Body_Y, Boss_MainBody[Bossbody_ImgNum], TRUE);
		//DrawGraph(380, 0, Explosion[0], TRUE);
		//DrawGraph(380, 0, Explosion[1], TRUE);
		//DrawGraph(440, 0, Boss_MainBody[0], TRUE);

		//����
		DrawGraph(100, 0, Boss_MainArm[0], TRUE);

		//�E��
		DrawGraph(Boss_Arm_Rightx, Boss_Arm_Righty, Boss_MainArm[1], TRUE);
		//DrawFormatString(400, 40, 0xff00ff, "Newhandsflg%d",New_Hand_Flg);
		//DrawFormatString(400, 80, 0xff00ff, "%d", timer);

		break;
	case 3:
		break;
	default:
		break;
	}
}

void Boss::BossImgChange(GameMain* main) {
	
	if (main->GetPlayerLocation().x < 426) {
		Bossbody_ImgNum = 0;
	}
	else if (main->GetPlayerLocation().x < 852) {
		Bossbody_ImgNum = 1;
	}
	else {
		Bossbody_ImgNum = 2;
	}
}

void Boss::Boss_MakeHand() {

	if(Once_Flg==true){
		if (timer++ > 200) {
			switch (Boss_step) {
			case 0:
				Boss_state = Boss_Y;
				Boss_step++;
				break;
			case 1:
					Boss_Body_Y += 400;
					Boss_state = Boss_M;
					Boss_step++;
				break;
			case 2:
				Boss_Body_Y += -400;
				Boss_state = Boss_C;
				Boss_step++;
				break;
			case 3:
				Boss_Body_Y += 400;
				Boss_state = Boss_M;
				Boss_step++;
				break;
			case 4:
				//�N���A����
				break;
			}
			

			New_Hand_Flg = true;
			Hand_Num = Boss_state;
			timer = 0;
			Once_Flg = false;
		}
	}

}