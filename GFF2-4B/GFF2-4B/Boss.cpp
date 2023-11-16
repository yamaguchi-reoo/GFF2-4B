#include "Boss.h"

Boss::Boss() {
	LoadDivGraph("resource/images/Boss/BossBody.png", 3, 3, 1, 360, 700,Boss_MainBody);
	LoadDivGraph("resource/images/Boss/BossArm.png", 2, 2, 1, 420, 700,Boss_MainArm);
	LoadDivGraph("resource/images/Boss/explosionMini.png", 2, 2, 1, 160, 160, Explosion);

	timer = 0;

	Boss_Arm_Rightx=800;
	Boss_Arm_Righty=0;

	Count_Death = 2;
	Boss_Form=0;
	Boss_Check_Playerx = -1;

	New_Hand_Flg = false;
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {
	
	if (timer++==100) {
		New_Hand_Flg = true;
	}
	Boss_Arm_Righty += timer;
}

void Boss::Draw() const {

	DrawGraph(440, 0, Boss_MainBody[0], TRUE);
	//DrawGraph(380, 0, Explosion[0], TRUE);
	//DrawGraph(380, 0, Explosion[1], TRUE);
	//DrawGraph(440, 0, Boss_MainBody[0], TRUE);

	DrawGraph(100, 0, Boss_MainArm[0], TRUE);
	DrawGraph(Boss_Arm_Rightx, Boss_Arm_Righty, Boss_MainArm[1], TRUE);
	DrawFormatString(400, 40, 0xff00ff, "death%d", Count_Death);

}

void Boss::BossImgChange() {

	

}