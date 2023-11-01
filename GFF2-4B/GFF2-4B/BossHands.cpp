#include "BossHands.h"

BossHands::BossHands() {
	handsimg[0] = LoadGraph("resource/images/Boss/BhandM.png");
	handsimg[1] = LoadGraph("resource/images/Boss/bhandC.png");
	location.x = 1000;
	location.y = 0;
	erea.height = 200;
	erea.width = 200;
}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {
	if (hitflg != true) {
		//hands.y += 1.0f;
		location.y += 5;
	}
}

void BossHands::Draw() const {
	DrawGraphF(location.x, location.y,handsimg[0], TRUE);
	DrawGraph(200, 300, handsimg[1], TRUE);
}