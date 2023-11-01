#include "Boss.h"

Boss::Boss() {
	bfaceimg = LoadGraph("resource/images/Boss/BossFace.png");
	bhandm= LoadGraph("resource/images/Boss/BhandM.png");
	bhandc= LoadGraph("resource/images/Boss/bhandC.png");
		
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {


}

void Boss::Draw() const {

	DrawGraph(400, 100, bfaceimg, TRUE);
	DrawGraph(1000, 300, bhandm, TRUE);
	DrawGraph(200, 300, bhandc, TRUE);
}