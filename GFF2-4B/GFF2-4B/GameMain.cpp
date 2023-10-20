#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"
#include "common.h"

GameMain::GameMain()
{
	player = new Player();
	scene_scroll = new SceneScroll();
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
	delete scene_scroll;
	for (int i = 0; i < 2; i++)
	{
		delete stage[i];
	}
}

AbstractScene* GameMain::Update()
{
	//�X�V
	player->Update();
	scene_scroll->Update(player->GetLocation(), player->GetAcs(2), player->GetAcs(3));

	//false�ɐݒ肵�Ȃ���
	onfloor_flg = false;
	//���̐������J��Ԃ�
	for (int i = 0; i < 2; i++)
	{
		stage[i]->Update();
		if (player->HitBox(stage[i]) == true)
		{
			//�G�ꂽ�ʂɉ����ĉ����o��
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

	//�`��
	player->Draw();
	for (int i = 0; i < 2; i++)
	{
		//DrawFormatString(0, 100+(i*20), 0x00ff00, "%d", count[i]);
		stage[i]->Draw();
	}
	if (flg == true) {
		DrawString(300, 300,"flg", 0xffffff);
	}
	zakuro->Draw();
	himawari->Draw();
}
