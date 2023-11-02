#include "EditScene.h"
#include <fstream>
#include <iostream>
#include <string>

#include "GameMain.h"

EditScene::EditScene()
{
	CreateStage();
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
			select_data[i][j] = false;
		}
	}
}

EditScene::~EditScene()
{

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			delete stage[i][j];
		}
	}
}

AbstractScene* EditScene::Update()
{
	//カーソルの位置更新
	cursor = KeyInput::GetMouseCursor();
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j]->Update();
			if (cursor.x > stage[i][j]->GetLocation().x && cursor.x<stage[i][j]->GetLocation().x + BOX_SIZE && cursor.y>stage[i][j]->GetLocation().y && cursor.y < stage[i][j]->GetLocation().y + BOX_SIZE)
			{
				select_data[i][j] = true;
				if (KeyInput::OnPresed(KEY_INPUT_0))
				{
					STAGE_DATA[i][j] = 0;
				}
				if (KeyInput::OnPresed(KEY_INPUT_1))
				{
					STAGE_DATA[i][j] = 1;
				}
				if (KeyInput::OnPresed(KEY_INPUT_2))
				{
					STAGE_DATA[i][j] = 2;
				}
				if (KeyInput::OnPresed(KEY_INPUT_3))
				{
					STAGE_DATA[i][j] = 3;
				}
				if (KeyInput::OnPresed(KEY_INPUT_4))
				{
					STAGE_DATA[i][j] = 4;
				}
			}
			else
			{
				select_data[i][j] = false;
			}
		}
	}
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j]->SetStageType(STAGE_DATA[i][j]);
		}
	}
	//ステージを動かす
	if (KeyInput::OnPresed(KEY_INPUT_A))
	{
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				stage[i][j]->MoveStage(-5);
			}
		}
	}
	if (KeyInput::OnPresed(KEY_INPUT_D))
	{
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				stage[i][j]->MoveStage(+5);
			}
		}
	}
	//ゲームメインに戻る
	if (KeyInput::OnKey(KEY_INPUT_B))
	{
		UpdateStageData();
		return new GameMain();
	}
	return this;
}

void EditScene::Draw()const
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			stage[i][j]->Draw();
			if (select_data[i][j] == true)
			{
				DrawBox(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x +BOX_SIZE, stage[i][j]->GetLocation().y + BOX_SIZE, 0xff0000, true);
			}
		}
	}
	DrawString(cursor.x, cursor.y, "Edit", 0x00ff00);
	DrawBox(cursor.x, cursor.y, cursor.x + 300, cursor.y + 25, 0x000000, true);
	DrawBox(cursor.x, cursor.y, cursor.x + 300, cursor.y + 25, 0xffffff, false);
	DrawString(cursor.x+5, cursor.y+5, "0=無 1=地面 2=木 3=岩 4=雲",0xffffff);
}

void EditScene::CreateStage()
{
	std::ifstream file("resource/dat/StageData.txt");
	//ファイルが読み込めていたなら
	if (file)
	{
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}

void EditScene::UpdateStageData()
{
	std::ofstream file("resource/dat/StageData.txt");
	//ファイルが読み込めていたなら
	if (file)
	{
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < STAGE_HEIGHT; i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				file << STAGE_DATA[i][j] << "\n";
			}
		}
	}
}