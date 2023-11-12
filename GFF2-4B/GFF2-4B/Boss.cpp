#include "Boss.h"

Boss::Boss() {
	bfaceimg = LoadGraph("resource/images/Boss/BossFace.png");
	Count_Death = 2;
	Boss_Form=0;
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {



}

void Boss::Draw() const {

	//DrawGraph(400, 100, bfaceimg, TRUE);
	DrawFormatString(400, 40, 0xff00ff, "death%d", Count_Death);

}