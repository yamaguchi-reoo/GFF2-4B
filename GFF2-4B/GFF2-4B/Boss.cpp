#include "Boss.h"

Boss::Boss() {
	LoadDivGraph("resource/images/Boss/BossBody.png", 3, 3, 1, 360, 700,Boss_MainBody);
	LoadDivGraph("resource/images/Boss/BossArm.png", 2, 2, 1, 420, 700,Boss_MainArm);

	test[0] = LoadGraph("resource/images/Boss/Himawari.png", true);


	Count_Death = 2;
	Boss_Form=0;
	Boss_Check_Playerx = -1;
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {


}

void Boss::Draw() const {

	DrawGraph(440, 0, Boss_MainBody[0], TRUE);
	DrawGraph(500, 600, test[0], TRUE);
	DrawGraph(800, 0, Boss_MainArm[1], TRUE);
	DrawFormatString(400, 40, 0xff00ff, "death%d", Count_Death);

}

void Boss::BossImgChange() {

	

}