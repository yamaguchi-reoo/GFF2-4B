#include "SighBoard.h"

SighBoard::SighBoard(float pos_x, float pos_y, int type)
{
	location.x = pos_x;
	location.y = pos_y;
	disp_location.x = 0;
	disp_location.y = 0;
	erea.width = 5;
	erea.height = BOX_HEIGHT;
	disp_type = type;
	tuto_disp_flg = false;
	disp_time = 0;
	disp_once = false;
	hp = 1;
	disp_flg = true;
	damage_once = false;
	LoadDivGraph("resource/images/Tutorialimg/Tutorial.png", 4, 4, 1, 320, 320, sb_img);
}

SighBoard::~SighBoard()
{

}

void SighBoard::Update(Location _player_location, Location _player_local_location)
{
	//hpが０以下なら現在表示されているチュートリアルが消えた後表示されないように
	if (hp > 0)
	{
		if (location.x - 200 < _player_location.x && location.x + erea.width + 200 > _player_location.x)
		{
			if (tuto_disp_flg == false && disp_once == false)
			{
				tuto_disp_flg = true;
				disp_once = true;
				disp_time = 0;
			}
		}
		else
		{
			disp_once = false;
		}
	}
	disp_location = _player_local_location;
	if (++disp_time > 240)
	{
		tuto_disp_flg = false;
	}
}

void SighBoard::Draw()const
{
	if (hp > 0)
	{
		DrawBox(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xBFA46F, true);
		DrawTriangleAA(local_location.x + (erea.width / 2), local_location.y - 45, local_location.x - 25, local_location.y - 20, local_location.x + erea.width + 25, local_location.y - 20, 0xBFA46F, true);
		DrawBox(local_location.x - 15, local_location.y - 30, local_location.x + erea.width + 15, local_location.y, 0xBFA46F, true);
	}
	if (tuto_disp_flg == true)
	{
		if (disp_location.y > 200)
		{
			DrawGraph(disp_location.x - 59, disp_location.y - 370, sb_img[disp_type - 9], false);
		}
		else
		{
			DrawGraph(disp_location.x - 59, disp_location.y + 100, sb_img[disp_type - 9], false);
		}
		/*switch (disp_type)
		{
		case 9:
			DrawBox(local_location.x - 300, local_location.y - 500, local_location.x + erea.width + 300, local_location.y - 200, 0x000000, true);
			DrawString(local_location.x - 300, local_location.y - 500, "攻撃", 0xffffff);
			break;
		case 10:
			DrawBox(local_location.x - 300, local_location.y - 500, local_location.x + erea.width + 300, local_location.y - 200, 0x000000, true);
			DrawString(local_location.x - 300, local_location.y - 500, "ジャンプ", 0xffffff);
			break;
		case 11:
			DrawBox(local_location.x - 300, local_location.y - 500, local_location.x + erea.width + 300, local_location.y - 200, 0x000000, true);
			DrawString(local_location.x - 300, local_location.y - 500, "ジャンプ攻撃", 0xffffff);
			break;
		case 12:
			DrawBox(local_location.x - 300, local_location.y - 500, local_location.x + erea.width + 300, local_location.y - 200, 0x000000, true);
			DrawString(local_location.x - 300, local_location.y - 500, "強化状態", 0xffffff);
			break;
		}*/
	}
}