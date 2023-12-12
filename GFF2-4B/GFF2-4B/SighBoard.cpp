#include "SighBoard.h"

#define ACS_MAX 6	//最大加速度
#define DOWN 0	//下加速度用
#define UP 1	//上加速度用
#define RIGHT 2	//右加速度用
#define LEFT 3	//左加速度用

SighBoard::SighBoard(float pos_x, float pos_y, int type)
{
	frame = 0;
	hp = 100;
	location.x = pos_x;
	location.y = pos_y;
	disp_location.x = 0;
	disp_location.y = 0;
	erea.width = 5;
	erea.height = BOX_HEIGHT;
	disp_type = type;
	tuto_disp_flg = false;
	disp_once = false;
	disp_flg = true;
	break_flg = false;
	direction = false;
	LoadDivGraph("resource/images/Tutorialimg/Tutorial.png", 4, 4, 1, 320, 320, sb_img);
	Date.cyan = 0;
	Date.magenta = 5;
	Date.yellow = 5;
}

SighBoard::~SighBoard()
{

}

void SighBoard::Update(int _stage_height,Location _player_location, Location _player_local_location)
{
	if (++frame > 30)
	{
		frame = 0;
	}
	if (location.x - 100 < _player_location.x && location.x + erea.width + 100 > _player_location.x && location.y-200<_player_location.y&& location.y +erea.height +100 >_player_location.y && disp_once == false)
	{
		tuto_disp_flg = true;
	}
	if (break_flg == true && location.y < _stage_height + 100)
	{
		//重力
		acs[DOWN]++;
		for (int i = 0; i < 4; i++)
		{
			DecAcs(i);
		}
		location.x = location.x + acs[RIGHT] - acs[LEFT];
		location.y = location.y + acs[DOWN] - acs[UP];
	}
}

void SighBoard::Draw()const
{
	if (break_flg == false)
	{
		DrawBoxAA(local_location.x, local_location.y, local_location.x + erea.width, local_location.y + erea.height, 0xBFA46F, true);
		DrawTriangleAA(local_location.x + (erea.width / 2), local_location.y - 45, local_location.x - 25, local_location.y - 20, local_location.x + erea.width + 25, local_location.y - 20, 0xBFA46F, true);
		DrawBoxAA(local_location.x - 15, local_location.y - 30, local_location.x + erea.width + 15, local_location.y, 0xBFA46F, true);
	}
	else
	{
		DrawBox(local_location.x+GetRand(20), local_location.y + GetRand(20), local_location.x + erea.width + GetRand(20), local_location.y + erea.height + GetRand(20), 0xBFA46F, true);
		DrawTriangleAA(local_location.x + (erea.width / 2) + GetRand(20), local_location.y - 45 + GetRand(20), local_location.x - 25 + GetRand(20), local_location.y - 20 + GetRand(20), local_location.x + erea.width + 25 + GetRand(20), local_location.y - 20 + GetRand(20), 0xBFA46F, true);
		DrawBox(local_location.x - 15 + GetRand(20), local_location.y - 30 + GetRand(20), local_location.x + erea.width + 15 + GetRand(20), local_location.y + GetRand(20), 0xBFA46F, true);
	}
	
	if (tuto_disp_flg == true)
	{
		if (local_location.y < 300)
		{
			DrawGraphF(local_location.x - 30, local_location.y + 70, sb_img[disp_type - 9], true);
		}
		else
		{
			DrawGraphF(local_location.x - 30, local_location.y - 370, sb_img[disp_type - 9], true);
		}
		if (frame < 15)
		{
			DrawStringF(local_location.x, local_location.y, "B = 決定", 0x000000);
		}
		else
		{
			DrawStringF(local_location.x, local_location.y, "B = 決定", 0xffffff);
		}
	}
}

void SighBoard::DecAcs(int num)
{
	if (acs[num] > 0)
	{
		acs[num] -= 0.5f;
	}
	if (acs[num] < 0)
	{
		acs[num] = 0;
	}
}

//破壊可能にする
void SighBoard::SetBreak(bool _player_direction)
{
	break_flg = true;
	if (_player_direction == false)
	{
		acs[RIGHT] = 20;
		acs[UP] = 10;
	}
	else
	{
		acs[LEFT] = 20;
		acs[UP] = 10;
	}
}