#include "BossHands.h"
#include"GameMain.h"


BossHands::BossHands(int _who) {
	handsimg[0] = LoadGraph("resource/images/Boss/BhandM.png");
	handsimg[1] = LoadGraph("resource/images/Boss/bhandC.png");
	location.x = 700;
	location.y = 0;
	erea.height = 190;
	erea.width = 190;
	switching = 0;
	down_hand = false;
	who = _who;
}

BossHands::~BossHands() {

}

void BossHands::Update(GameMain* main) {
	if (down_hand ==false) {
		HandsMagenta();
		BossAttack(main);
	}
	if (hitflg == true) {
		ShockWaveAttack(main);
	}
}

void BossHands::Draw() const {
	DrawGraphF(location.x, location.y,handsimg[0], TRUE);
	DrawGraph(200, 300, handsimg[1], TRUE);

#ifdef _DEBUG
	DrawFormatString(100, 0, 0xffffff, "%d", switching);
	DrawFormatString(120, 0, 0xff00ff, "%d", hitflg);
//	DrawBox(-erea.width, -erea.height, erea.width, erea.height, 0xffffff, TRUE);

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

		//location.y = 0;
		//hitflg = false;
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
	attack_data.shift_x = -erea.width-3;
	attack_data.shift_y = -30;
	attack_data.width = erea.width;
	attack_data.height = erea.height-20;
	attack_data.who_attack = who;
	attack_data.attack_time = 30;
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

AttackData BossHands::ShockWaveData() {
	AttackData attack_data;
	attack_data.shift_x = -erea.width;
	attack_data.shift_y = -50;
	attack_data.width = erea.width;
	attack_data.height = erea.height;
	attack_data.who_attack = who;
	attack_data.attack_time = 300;
	attack_data.delay = 0;
	attack_data.damage = 1;
	attack_data.attack_type = BULLET;
	attack_data.speed = 3;
	attack_data.angle = 0.4;

	return attack_data;
}

void BossHands::ShockWaveAttack(GameMain* main)
{
	//UŒ‚‚ð¶¬‚·‚é
	main->SpawnAttack(ShockWaveData());

}