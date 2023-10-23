#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player();
	scene_scroll = new SceneScroll();
	attack = new Attack();
	stage[0] = new Stage(0, SCREEN_HEIGHT-100, SCREEN_WIDTH,100);
	stage[1] = new Stage(200, 300, 200, 50);
	for (int i = 0; i < 2; i++)
	{
		count[i] = 0;
	}

	zakuro = new Zakuro();
	himawari = new Himawari();
	iruka = new Iruka();

	for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i] = new Bamboo(i * 60);
	}
	flg = false;
	onfloor_flg = false;
}

GameMain::~GameMain()
{
	delete player;
	//delete scene_scroll;
	for (int i = 0; i < 2; i++)
	{
		delete stage[i];
	}
	delete zakuro;
	delete himawari;
	delete iruka;
}

AbstractScene* GameMain::Update()
{
	//更新
	scene_scroll->Update(player->GetLocation(), player->GetAcs(2), player->GetAcs(3));
	scene_scroll->PlayerScroll(player->GetLocation());
	zakuro->Update(this);

	player->Update(this);
	attack->Update(player->GetLocation());
	//falseに設定しなおす
	onfloor_flg = false;
	//床の数だけ繰り返す
	for (int i = 0; i < 2; i++)
	{
		stage[i]->Update();
		if (player->HitBox(stage[i]) == true)
		{
			//触れた面に応じて押し出す
			player->Push(i,stage[i]->GetLocation(), stage[i]->GetErea());
		}
	}
	


	if (KeyInput::OnKey(KEY_INPUT_A)) {
		flg = true;
	}
	return this;
}

void GameMain::Draw() const
{
	scene_scroll->Draw();

	SetFontSize(42);
	DrawString(400, 0, "GameMain", 0xffffff);

	//描画
	player->Draw();
	attack->Draw();
	for (int i = 0; i < 2; i++)
	{
		//DrawFormatString(0, 100+(i*20), 0x00ff00, "%d", count[i]);
		stage[i]->Draw();
	}
	if (flg == true) {
		DrawString(300, 300,"flg", 0xffffff);
	}
	//エネミーの描画
	zakuro->Draw(); // ザクロ
	himawari->Draw();// ひまわり
	iruka->Draw();// イルカ

	for (int i = 0; i < BAMBOO_NUM; i++) {
		bamboo[i]->Draw();
	}
	
}

void GameMain::SpawnAttack(Location _location)
{
	attack->SpawnAttack(_location);
}
