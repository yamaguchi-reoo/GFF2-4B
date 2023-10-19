#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"

GameMain::GameMain()
{
	player = new Player();
	stage = new Stage();
	zakuro = new Zakuro();
	himawari = new Himawari();
	flg = false;
	count = 0;
}

GameMain::~GameMain()
{
	delete player;
	delete stage;
}

AbstractScene* GameMain::Update()
{
	//更新
	player->Update();
	stage->Update();
	//プレイヤーが地面に触れた時に着地する
	switch(player->HitBox(stage))
	{
	case 0:
		count = 0;
		player->GiveGravity();
		break;
	case 1:
		count = 1;
		break;
	case 2:
		count = 2;
		player->GiveGravity();
		break;
	case 3:
		count = 3;
		player->GiveGravity();
		break;
	case 4:
		count = 4;
		player->GiveGravity();
		break;
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
	stage->Draw();
	DrawFormatString(0, 100, 0x00ff00, "%d", count);
	if (flg == true) {
		DrawString(300, 300,"flg", 0xffffff);
	}
	zakuro->Draw();
	himawari->Draw();
}
