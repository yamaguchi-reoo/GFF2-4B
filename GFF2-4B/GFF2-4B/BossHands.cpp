#include "BossHands.h"
#include"GameMain.h"


BossHands::BossHands() {
	handsimg[0] = LoadGraph("resource/images/Boss/BhandM.png");
	handsimg[1] = LoadGraph("resource/images/Boss/bhandC.png");
	location.x = 1000;
	location.y = 0;
	erea.height = 190;
	erea.width = 190;
	switching = 0;
	down_hand = false;
	who = 1;
	
}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {
	if (down_hand ==false) {
		HandsMagenta();
		BossAttack(main);

	}
}

void BossHands::Draw() const {
	DrawGraphF(location.x, location.y,handsimg[0], TRUE);
	DrawGraph(200, 300, handsimg[1], TRUE);

#ifdef _DEBUG
	DrawFormatString(100, 0, 0xffffff, "%d", switching);
	DrawFormatString(120, 0, 0xff00ff, "%d", hitflg);
	DrawBox(-erea.width, -erea.height, erea.width, erea.height, 0xffffff, TRUE);

#endif // _DEBUG


}

void BossHands::HandsMagenta() {

	/*if (switching > 2) {
		down_hand = true;
	}*/


	if (hitflg != true) {
		location.y += 5;
	}
	else {
		hitflg = false;
	}
		Attack(main);

	


		//switch (switching) {
		//case 0:
		//	location.x = Magentax[switching];
		//	break;
		//case 1:
		//	location.x = Magentax[switching];
		//	break;
		//case 2:
		//	location.x = Magentax[switching];
		//	break;
		//default:
		//	break;
		//}
}

AttackData BossHands::BossAttactData()
{
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = erea.height;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 300;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = MELEE;



	return attack_data;
}

void BossHands::BossAttack(GameMain* main)
{
	//UŒ‚‚ð¶¬‚·‚é
	main->SpawnAttack(BossAttactData());
}

void BossHands::HandResetting() {
	location.x;
}