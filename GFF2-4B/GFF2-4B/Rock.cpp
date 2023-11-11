#include "Rock.h"
#include"GameMain.h"
#include <math.h>

Rock::Rock(int _who,float x,float y) {
	//test
	location.x = 0;
	location.y = 0;
	Rock_Movex = 0;
	Rock_Movey = 0;
	Set_Rock_x = x;
	Set_Rock_y = y;
	Rock_img = LoadGraph("resource/images/Boss/Rock.png", true);
	timer = 0;
	g = 9.8;
	sita = 45;
	V_zero = 50;
	who = _who;
}

Rock::~Rock(){

}

void Rock::Update(GameMain* main) {

	//•ú•¨ü
	Rock_Movex = V_zero * (cosf(sita) * timer);
	Rock_Movey = (V_zero * (sinf(sita) * timer)) - ((g * (timer * timer)) / 2);
	location.x = Set_Rock_x + Rock_Movex;
	location.y = Set_Rock_y - Rock_Movey;
	timer += 0.05;

	RockAttack(main);
}

void Rock::Draw() const {

	DrawGraphF(location.x, location.y, Rock_img, TRUE);

#ifdef _DEBUG
	DrawFormatString(400, 200, 0xff00ff, "location%f", location.x);
	DrawFormatString(400, 300, 0xff00ff, "locationy%f", location.y);

#endif // _DEBUG


}

AttackData Rock::RockAttactData() {
	AttackData attack_data;

		attack_data.shift_x = 0;
		attack_data.shift_y = 0;
		attack_data.width = 75;
		attack_data.height = 75;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 0;
		attack_data.damage = 1;
		attack_data.attack_type = MELEE;

		return attack_data;
}

void Rock::RockAttack(GameMain* main) {
		//UŒ‚‚ð¶¬‚·‚é
		main->SpawnAttack(RockAttactData());	
}