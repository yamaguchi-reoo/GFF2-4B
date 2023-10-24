#include "Iruka.h"


Iruka::Iruka()
{
	location.x = 900;
	location.y = 300;
	erea.width = 120;
	erea.height = 50;
	speed = 3;

	fps_count = 0;

	direction = 0;

	iruka_flg = false;
	fall_flg = false;
}

Iruka::~Iruka()
{
}

void Iruka::Update(GameMain* main)
{
	//落下していないとき
	if (fall_flg == false) {
		//右移動
		if (iruka_flg == true) {
			location.x += 5;
			if (location.x > (SCREEN_WIDTH - 80)) {
				iruka_flg = false;
				direction = 0;
			}
		}
		//左移動
		if (iruka_flg == false) {
			location.x -= 5;
			if (location.x < 0) {
				iruka_flg = true;
				direction = 1;
			}
		}
	}

	//落下中
	if (fall_flg == true) {
		erea.width = 50;
		erea.height = 120;
		location.y += speed;
		//突き刺さり
		if (location.y >= 570) {
			location.y = 570;
		}
		//右向き落下
		if (iruka_flg == true) {
			direction = 2;
		}
		//左向き落下
		if (iruka_flg == false) {
			direction = 3;
		}

		
	}
	//復帰
	if (fall_flg == true && location.y == 570) {
		if (++fps_count > 60) {
			fall_flg = false;
			location.y = 300;
			erea.width = 120;
			erea.height = 50;
			fps_count = 0;
			//落下する前の向きに戻す
			if (iruka_flg == false) {
				direction = 0;
			}
			if (iruka_flg == true) {
				direction = 1;
			}
		}
	}

}

void Iruka::Draw() const
{
	
	DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0x00ffff, TRUE);
	//右向き
	if (direction == 0){
		DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
	}
	//左向き
	else if(direction == 1){
		DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
	}
	//右向き落下
	else if (direction == 2) {
		DrawBoxAA(location.x + erea.width, location.y + erea.height - 40, location.x + 30, location.y + erea.height, 0x00ff00, true);
	}
	//左向き落下
	else if (direction == 3) {
		DrawBoxAA(location.x + 30, location.y + erea.height - 40, location.x, location.y + erea.height, 0x00ff00, true);
	}
	
}