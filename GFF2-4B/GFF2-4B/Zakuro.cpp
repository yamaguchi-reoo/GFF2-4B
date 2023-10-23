#include "Zakuro.h"
#include "DxLib.h"
#include "Player.h"

Zakuro::Zakuro()
{
	location.x = 290;
	location.y = 570;
	erea.height = 50;
	erea.width = 50;

	zakuro_flg = false;
}
Zakuro::~Zakuro()
{
	
}
void Zakuro::Update(GameMain* main)
{
	//ç∂à⁄ìÆ
	if (zakuro_flg == false) {
		location.x--;
		if (location.x < 0) {
			zakuro_flg = true;
		}
	}
	//âEà⁄ìÆ
	if (zakuro_flg == true) {
		location.x++;
		if (location.x > 500) {
			zakuro_flg = false;
		}
	}
}

void Zakuro::Draw() const
{
	SetFontSize(20);
	DrawFormatString(200, 0, 0xffffff, "%f", location.x);
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xff00ff, TRUE);
}



