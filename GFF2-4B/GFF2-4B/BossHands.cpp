#include "BossHands.h"

BossHands::BossHands() {
	handsimg[0] = LoadGraph("resource/images/Boss/BhandM.png");
	handsimg[1] = LoadGraph("resource/images/Boss/bhandC.png");
	location.x = 1000;
	location.y = 0;
	erea.height = 200;
	erea.width = 200;
	switching = 0;
	down_hand = false;
}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {
	if (down_hand ==false) {
		HandsMagenta();
	}

}

void BossHands::Draw() const {
	DrawGraphF(location.x, location.y,handsimg[0], TRUE);
	DrawGraph(200, 300, handsimg[1], TRUE);

#ifdef _DEBUG
	DrawFormatString(100, 0, 0xffffff, "%d", switching);
	DrawFormatString(120, 0, 0xff00ff, "%d", hitflg);

#endif // _DEBUG


}

void BossHands::HandsMagenta() {

	if (switching > 2) {
		down_hand = true;
	}

		if (hitflg != true) {
			//hands.y += 1.0f;
			location.y += 5;
		}
		else {
			switching++;

			if (down_hand != true) {
				location.y = 0;
			}

			hitflg = false;
		}
	

		switch (switching) {
		case 0:
			location.x = Magentax[switching];
			break;
		case 1:
			location.x = Magentax[switching];
			break;
		case 2:
			location.x = Magentax[switching];
			break;
		default:
			break;
		}


		
}