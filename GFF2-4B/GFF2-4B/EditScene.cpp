#include "EditScene.h"
#include <fstream>
#include <iostream>
#include <string>

#include "GameMain.h"

EditScene::EditScene(int _stage)
{
	now_stage = _stage;
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
		}
	}
}

EditScene::~EditScene()
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			delete stage[i][j];
		}
	}
}

AbstractScene* EditScene::Update()
{
	//カーソルの位置更新
	cursor = KeyInput::GetMouseCursor();
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
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
				if (KeyInput::OnPresed(KEY_INPUT_5))
				{
					STAGE_DATA[i][j] = 5;
				}
				if (KeyInput::OnPresed(KEY_INPUT_6))
				{
					STAGE_DATA[i][j] = 6;
				}
			}
			else
			{
				select_data[i][j] = false;
			}
		}
	}
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->SetStageType(STAGE_DATA[i][j]);
		}
	}
	//ステージを動かす
	if (KeyInput::OnPresed(KEY_INPUT_W))
	{
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j]->MoveStage(0, +10);
			}
		}
	}
	if (KeyInput::OnPresed(KEY_INPUT_A))
	{
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j]->MoveStage(+10,0);
			}
		}
	}
	if (KeyInput::OnPresed(KEY_INPUT_S))
	{
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j]->MoveStage(0, -10);
			}
		}
	}
	if (KeyInput::OnPresed(KEY_INPUT_D))
	{
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage[i][j]->MoveStage(-10,0);
			}
		}
	}
	//ゲームメインに戻る
	if (KeyInput::OnKey(KEY_INPUT_B))
	{
		UpdateStageData(now_stage);
		return new GameMain(now_stage);
	}
	//ステージの横幅を増やす
	//if (KeyInput::OnKey(KEY_INPUT_G))
	//{
	//	stage_width++;
	//	UpdateStage();
	//}
	return this;
}

void EditScene::Draw()const
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->Draw();
			if (select_data[i][j] == true)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x +BOX_SIZE, stage[i][j]->GetLocation().y + BOX_SIZE, 0xff0000, false);
			}
			if (STAGE_DATA[i][j] == 5)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_SIZE, stage[i][j]->GetLocation().y + BOX_SIZE, 0xff00ff , true);
			}
			if (STAGE_DATA[i][j] == 6)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_SIZE, stage[i][j]->GetLocation().y + BOX_SIZE, 0x00ffff, true);	
			}
		}
	}
	DrawBox(cursor.x, cursor.y, cursor.x + 500, cursor.y + 25, 0x000000, true);
	DrawBox(cursor.x, cursor.y, cursor.x + 500, cursor.y + 25, 0xffffff, false);
	DrawString(cursor.x+5, cursor.y+5, "0=無 1=地面 2=木 3=岩 4=雲 5=ザクロ 6=イルカ",0xffffff);
}

void EditScene::LoadStageData(int _stage)
{
	const char* a = "resource/dat/1stStageData.txt";
	switch (_stage)
	{
	case 0:
		a = "resource/dat/1stStageData.txt";
		break;
	case 1:
		a = "resource/dat/2ndStageData.txt";
		break;
	case 2:
		a = "resource/dat/3rdStageData.txt";
		break;
	case 3:
		a = "resource/dat/BossStageData.txt";
		break;
	}

	std::ifstream file(a);
	//ファイルが読み込めていたなら
	if (file)
	{
		file >> stage_width;
		file >> stage_height;
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				file >> STAGE_DATA[i][j];
			}
		}
	}
}


void EditScene::UpdateStageData(int _stage)
{
	const char* a = "resource/dat/1stStageData.txt";
	switch (_stage)
	{
	case 0:
		a = "resource/dat/1stStageData.txt";
		break;
	case 1:
		a = "resource/dat/2ndStageData.txt";
		break;
	case 2:
		a = "resource/dat/3rdStageData.txt";
		break;
	case 3:
		a = "resource/dat/BossStageData.txt";
		break;
	}
	std::ofstream file(a);
	//ファイルが読み込めていたなら
	if (file)
	{
		file << stage_width << "\n";
		file << stage_height << "\n";
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				file << STAGE_DATA[i][j] << "\n";
			}
		}
	}
}

void EditScene::UpdateStage()
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j] = new Stage(j * BOX_SIZE, i * BOX_SIZE, BOX_SIZE, BOX_SIZE, STAGE_DATA[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
		}
	}
}