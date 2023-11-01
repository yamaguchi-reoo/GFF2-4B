#include "BossHands.h"

BossHands::BossHands() {
	handsimg[0] = LoadGraph("resource/images/Boss/BhandM.png");
	handsimg[1] = LoadGraph("resource/images/Boss/bhandC.png");

}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {

}

void BossHands::Draw() const {
	DrawGraph(1000, 300,handsimg[0], TRUE);
	DrawGraph(200, 300, handsimg[1], TRUE);

}