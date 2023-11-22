#include "Rock.h"
#include"GameMain.h"
#include <math.h>

Rock::Rock(int _who,int Set_Xnum) {
	//test
	erea.height = 75;
	erea.width = 75;
	location.x = 0;
	location.y = 0;
	Rock_Movex = 0;
	Rock_Movey = 0;
	Set_Rock_x = Rock_X[Set_Xnum];
	Set_xnum = Set_Xnum;
	Set_Rock_y = 500;
	Rock_img = LoadGraph("resource/images/Boss/Rock.png", true);
	timer = 0;
	g = 9.8;
	sita = 45;
	V_zero = 50;
	who = _who;
	Rock_Delete = false;

}

Rock::~Rock(){

}

void Rock::Update(GameMain* main) {

	switch (Set_xnum) {
	case 0:
		//放物線
		Rock_Movex = V_zero * (cosf(sita) * timer);
		Rock_Movey = (V_zero * (sinf(sita) * timer)) - ((g * (timer * timer)) / 2);
		//Set-Moveで左にSet+Moveで右に行く
		//Set-Moveで上にSet+Moveで↓に行く
		location.x = Set_Rock_x - Rock_Movex;
		location.y = Set_Rock_y - Rock_Movey;
		timer += 0.05f;
		break;
	case 1:
		Rock_Movex = V_zero * (cosf(sita) * timer);
		Rock_Movey = (V_zero * (sinf(sita) * timer)) - ((g * (timer * timer)) / 2);
		//Set-Moveで左にSet+Moveで右に行く
		//Set-Moveで上にSet+Moveで↓に行く
		location.x = Set_Rock_x + Rock_Movex;
		location.y = Set_Rock_y - Rock_Movey;
		timer += 0.05f;
		break;
	case 2:
		//放物線
		Rock_Movex = V_zero * (cosf(sita) * timer);
		Rock_Movey = (V_zero * (sinf(sita) * timer)) - ((g * (timer * timer)) / 2);
		//Set-Moveで左にSet+Moveで右に行く
		//Set-Moveで上にSet+Moveで↓に行く
		location.x = Set_Rock_x - Rock_Movex;
		location.y = Set_Rock_y - Rock_Movey;
		timer += 0.05f;
		break;
	case 3:
		Rock_Movex = V_zero * (cosf(sita) * timer);
		Rock_Movey = (V_zero * (sinf(sita) * timer)) - ((g * (timer * timer)) / 2);
		//Set-Moveで左にSet+Moveで右に行く
		//Set-Moveで上にSet+Moveで↓に行く
		location.x = Set_Rock_x + Rock_Movex;
		location.y = Set_Rock_y - Rock_Movey;
		timer += 0.05f;
		break;
	default:
		break;
	}


	if (location.y > 700) {
		Rock_Delete = true;
	}

	RockAttack(main);
}

void Rock::Draw() const {

	DrawGraphF(location.x, location.y, Rock_img, TRUE);

#ifdef _DEBUG
	//DrawFormatString(400, 200, 0xff00ff, "location%f", location.x);
	//DrawFormatString(400, 300, 0xff00ff, "locationy%f", location.y);
	DrawFormatString(400, 300, 0xff00ff, "XNum%d", Set_xnum);

#endif // _DEBUG


}

AttackData Rock::RockAttactData() {
	AttackData attack_data;
		attack_data.shift_x = -75;
		attack_data.shift_y = 10;
		attack_data.width = erea.height;
		attack_data.height = erea.width;
		attack_data.who_attack = who;
		attack_data.attack_time = 300;
		attack_data.delay = 0;
		attack_data.damage = 1;
		attack_data.attack_type = MELEE;

		return attack_data;
}

void Rock::RockAttack(GameMain* main) {
		//攻撃を生成する
		main->SpawnAttack(RockAttactData());	
}