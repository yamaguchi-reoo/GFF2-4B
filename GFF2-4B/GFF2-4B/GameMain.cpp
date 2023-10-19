#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player();
	stage[0] = new Stage(0, 800, 1980, 100);
	stage[1] = new Stage(200, 500, 100, 100);
	for (int i = 0; i < 2; i++)
	{
		count[i] = 0;
	}
	zakuro = new Zakuro();
	himawari = new Himawari();
	flg = false;
	onfloor_flg = false;
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < 2; i++)
	{
		delete stage[i];
	}
}

AbstractScene* GameMain::Update()
{
	//更新
	player->Update();
	//falseに設定しなおす
	onfloor_flg = false;
	for (int i = 0; i < 2; i++)
	{
		stage[i]->Update();
		//プレイヤーが地面に触れた時に着地する
		switch (player->HitBox(stage[i]))
		{
		case 0:
			count[i] = 0;
			break;
		case 1:
			count[i] = 1;
			onfloor_flg = true;
			break;
		case 2:
			count[i] = 2;
			break;
		case 3:
			count[i] = 3;
			break;
		case 4:
			count[i] = 4;
			break;
		}
	}
	if (onfloor_flg == true)
	{
		player->OnFloor();
	}
	else
	{
		player->NotOnFloor();
	}
		
	if (KeyInput::OnKey(KEY_INPUT_A)) {
		flg = true;
	}
	return this;
}

void GameMain::Draw() const
{
	
	SetFontSize(42);
	DrawString(400, 0, "GameMain", 0xffffff);

	//描画
	player->Draw();
	for (int i = 0; i < 2; i++)
	{
		DrawFormatString(0, 100+(i*20), 0x00ff00, "%d", count[i]);
		stage[i]->Draw();
	}
	if (flg == true) {
		DrawString(300, 300,"flg", 0xffffff);
	}
	zakuro->Draw();
	himawari->Draw();
}
