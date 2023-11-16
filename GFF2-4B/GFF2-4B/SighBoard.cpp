#include "SighBoard.h"

SighBoard::SighBoard(float pos_x, float pos_y, int type)
{
	location.x = pos_x;
	location.y = pos_y;
	erea.width = 25;
	erea.height = BOX_HEIGHT;
	disp_type = type;
	disp_flg = false;
}

SighBoard::~SighBoard()
{

}

void SighBoard::Update(Location _player_location)
{
	if (location.x - 100 < _player_location.x && location.x + erea.width + 100 > _player_location.x)
	{
		disp_flg = true;
	}
	else
	{
		disp_flg = false;
	}
}

void SighBoard::Draw()const
{
	DrawBox(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0x892F1B, true);
	if (disp_flg == true)
	{
		switch (disp_type)
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
		}
	}
}