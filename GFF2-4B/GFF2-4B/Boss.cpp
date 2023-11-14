#include "Boss.h"

Boss::Boss() {
	LoadDivGraph("resource/images/Boss/BossBody.png", 3, 3, 1, 360, 700,Boss_MainBody);
	Count_Death = 2;
	Boss_Form=0;
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {



}

void Boss::Draw() const {

	DrawGraph(440, 100, Boss_MainBody[0], TRUE);
	DrawFormatString(400, 40, 0xff00ff, "death%d", Count_Death);

}