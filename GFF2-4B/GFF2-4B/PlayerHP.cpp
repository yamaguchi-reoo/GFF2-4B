#include "PlayerHP.h"

PlayerHP::PlayerHP()
{
	hpImage = LoadGraph("resource/images/HP.png");
	playerHP = 0;
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Update(int hp)
{
	playerHP = hp;
}

void PlayerHP::Draw() const
{
	for (int i = 0; i < playerHP; i++)
	{
		DrawGraph(160 + 40 * i, 58, hpImage, TRUE);
	}
	
	SetFontSize(20);
	DrawFormatString(160, 30, 0xffffff, "�X�R�A�F0000000");
}