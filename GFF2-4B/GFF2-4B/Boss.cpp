#include "Boss.h"

Boss::Boss() {
	bfaceimg = LoadGraph("resource/images/Boss/BossFace.png");
		
}

Boss::~Boss() {

}

void Boss::Update(GameMain* main) {



}

void Boss::Draw() const {

	DrawGraph(400, 100, bfaceimg, TRUE);
}