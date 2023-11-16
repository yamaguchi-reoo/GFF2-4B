#include "PlayerHP.h"
#include"DxLib.h"

//コンストラクタ
PlayerHP::PlayerHP()
{
	hpImage[0] = LoadGraph("resource/images/HP.png");
	hpImage[1] = LoadGraph("resource/images/HP1.png");
	hpImage[2] = LoadGraph("resource/images/HP2.png");
	hpImage[3] = LoadGraph("resource/images/HP3.png");
	hpImage[4] = LoadGraph("resource/images/HP4.png");
	hpImage[5] = LoadGraph("resource/images/HP5.png");



	player_hp = 5;
	draw_hp = 5;
	flash_flg = 0;
	flash_hp = 0;
}

//デストラクタ
PlayerHP::~PlayerHP()
{
}

//更新処理
void PlayerHP::Update(int hp)
{
	player_hp = hp;

	if (draw_hp > player_hp)
	{
		AnimHP();
		/*flash_hp = draw_hp - player_hp;
		FlashHP();*/
	}
}

//描画処理
void PlayerHP::Draw() const
{
	//点滅
	/*if ((flash_flg != 0) && (flash_flg % 10 == 0))
	{
		DrawGraph(160 + 40 * player_hp, 80, hpImage[0], TRUE);
	}*/

	//消滅
	if (flash_flg != 0)
	{
		DrawGraph(160 + 40 * player_hp, 80, hpImage[flash_flg], TRUE);
	}

	for (int i = 0; i < player_hp; i++)
	{
		DrawGraph(160 + 40 * i, 80, hpImage[0], TRUE);
	}
	
}

//HP点滅
void PlayerHP::FlashHP(void)
{
	if (flash_flg < 30)
	{
		flash_flg++;
	}
	else
	{
		flash_flg = 0;
		draw_hp = player_hp;
		flash_hp = 0;
	}
}

//HP消滅
void PlayerHP::AnimHP(void)
{
	switch (flash_flg)
	{
	case 0:
		flash_flg = 1;
		break;
	case 1:
		flash_flg = 2;
		break;
	case 2:
		flash_flg = 3;
		break;
	case 3:
		flash_flg = 4;
		break;
	case 4:
		flash_flg = 5;
		break;
	case 5:
		flash_flg = 0;
		draw_hp = player_hp;
		break;
	default:
		break;
	}
	
}