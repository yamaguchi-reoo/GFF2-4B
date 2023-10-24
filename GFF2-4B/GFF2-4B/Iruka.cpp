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
	//�������Ă��Ȃ��Ƃ�
	if (fall_flg == false) {
		//�E�ړ�
		if (iruka_flg == true) {
			location.x += 5;
			if (location.x > (SCREEN_WIDTH - 80)) {
				iruka_flg = false;
				direction = 0;
			}
		}
		//���ړ�
		if (iruka_flg == false) {
			location.x -= 5;
			if (location.x < 0) {
				iruka_flg = true;
				direction = 1;
			}
		}
	}

	//������
	if (fall_flg == true) {
		erea.width = 50;
		erea.height = 120;
		location.y += speed;
		//�˂��h����
		if (location.y >= 570) {
			location.y = 570;
		}
		//�E��������
		if (iruka_flg == true) {
			direction = 2;
		}
		//����������
		if (iruka_flg == false) {
			direction = 3;
		}

		
	}
	//���A
	if (fall_flg == true && location.y == 570) {
		if (++fps_count > 60) {
			fall_flg = false;
			location.y = 300;
			erea.width = 120;
			erea.height = 50;
			fps_count = 0;
			//��������O�̌����ɖ߂�
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
	//�E����
	if (direction == 0){
		DrawBoxAA(location.x + 40, location.y + 10, location.x, location.y + 40, 0x00ff00, true);
	}
	//������
	else if(direction == 1){
		DrawBoxAA(location.x + erea.width - 40, location.y + 10, location.x + erea.width, location.y + 40, 0x00ff00, true);
	}
	//�E��������
	else if (direction == 2) {
		DrawBoxAA(location.x + erea.width, location.y + erea.height - 40, location.x + 30, location.y + erea.height, 0x00ff00, true);
	}
	//����������
	else if (direction == 3) {
		DrawBoxAA(location.x + 30, location.y + erea.height - 40, location.x, location.y + erea.height, 0x00ff00, true);
	}
	
}