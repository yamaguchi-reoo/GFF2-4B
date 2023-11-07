#include "EditScene.h"
#include <fstream>
#include <iostream>
#include <string>

#include "GameMain.h"

EditScene::EditScene(int _stage)
{
	now_stage = _stage;
	current_type = 0;
	tool_location.x = 100;
	tool_location.y = 0;
	tool_size.width = 500;
	tool_size.height = 100;
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, stage_data[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
		}
	}
	now_select_erea = 0;
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
			Location location = { 0,0 };
			stage[i][j]->SetScreenPosition(location);
			switch (ChechSelectErea(i, j))
			{
			case STAGE_EDIT:
				//リセットしてから選択されたselect_dataをtrueにする
				ResetSelectData();
				select_data[i][j] = true;

				//変えようとしているステージのデータが変更後のデータと一緒でないなら
				if (stage_data[i][j] != current_type)
				{
					//ひとつ前の状態を保持
					if (KeyInput::OnMouse(MOUSE_INPUT_LEFT))
					{
						SaveOldData();
					}
					//更新
					if (KeyInput::OnPressedMouse(MOUSE_INPUT_LEFT))
					{
						stage_data[i][j] = current_type;
					}
				}
				//変えようとしているステージのデータが変更後のデータと一緒でないなら
				if (stage_data[i][j] != 0)
				{
					//ひとつ前の状態を保持
					if (KeyInput::OnMouse(MOUSE_INPUT_RIGHT))
					{
						SaveOldData();
					}
					//更新
					if (KeyInput::OnPressedMouse(MOUSE_INPUT_RIGHT))
					{
						stage_data[i][j] = 0;
					}
				}
				break;
			case TOOL_BOX:
				for (int i = 0; i < OBJECT_TYPE_NUM; i++)
				{
					if (cursor.x > tool_location.x + (i * 50) && cursor.x < tool_location.x + (i * 50) + 50 && cursor.y>tool_location.y && cursor.y < tool_location.y + 50)
					{
						if (KeyInput::OnPressedMouse(MOUSE_INPUT_LEFT))
						{
							current_type = i;
						}
					}
				}
				//つかんで動かす
				if (KeyInput::OnPressedMouse(MOUSE_INPUT_RIGHT))
				{
					MoveInsideScreen();
				}
				break;
			default:
				break;
			}
		}
	}
	//操作取り消し
	if (KeyInput::OnPresed(KEY_INPUT_LCONTROL) && KeyInput::OnKey(KEY_INPUT_Z))
	{
		for (int i = 0; i < stage_height; i++)
		{
			for (int j = 0; j < stage_width; j++)
			{
				stage_data[i][j] = old_stage_data[i][j];
			}
		}
	}

	//ステージの更新
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->SetStageType(stage_data[i][j]);
		}
	}

	//ステージを動かす
	if (KeyInput::OnPresed(KEY_INPUT_W))
	{
		MoveAllStageObj(0, 10);
	}
	if (KeyInput::OnPresed(KEY_INPUT_A))
	{
		MoveAllStageObj(10, 0);
	}
	if (KeyInput::OnPresed(KEY_INPUT_S))
	{
		MoveAllStageObj(0, -10);
	}
	if (KeyInput::OnPresed(KEY_INPUT_D))
	{
		MoveAllStageObj(-10, 0);
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
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x +BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0xff0000, false);
			}
			if (stage_data[i][j] == 5)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0xff00ff , true);
			}
			if (stage_data[i][j] == 6)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0x00ffff, true);
			}
			if (stage_data[i][j] == 7)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0xffff00, true);
			}
		}
	}
	DrawBox(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0x000000, true);
	DrawBox(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0xffffff, false);
	DrawString(tool_location.x, tool_location.y + 70, "左クリックで選択＆配置", 0xffffff);
	DrawString(tool_location.x + 300, tool_location.y + 70, "Bキーでゲームメイン", 0xffffff);

	//現在選択中のオブジェクトを分かりやすく	
	for (int i = 0; i < OBJECT_TYPE_NUM; i++)
	{
		DrawBox(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, true);
		DrawBox(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, false);
		if (current_type == i)
		{
			DrawBox(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, true);
			DrawBox(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, false);
		}
		switch (i)
		{
		case 0:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "無", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "無", 0xffffff);
			}
			break;
		case 1:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 10, tool_location.y + 15, "地面", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 10, tool_location.y + 15, "地面", 0xffffff);
			}
			break;
		case 2:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "木", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "木", 0xffffff);
			}
			break;
		case 3:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "岩", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "岩", 0xffffff);
			}
			break;
		case 4:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "雲", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "雲", 0xffffff);
			}
			break;
		case 5:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "ザクロ", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 15, tool_location.y + 15, "ザクロ", 0xffffff);
			}
			break;
		case 6:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50), tool_location.y + 15, "イルカ", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50), tool_location.y + 15, "イルカ", 0xffffff);
			}
			break;
		case 7:
			if (current_type == i)
			{
				DrawString(tool_location.x + (i * 50) + 20, tool_location.y + 15, "ひま", 0x000000);
			}
			else
			{
				DrawString(tool_location.x + (i * 50) + 20, tool_location.y + 15, "ひま", 0xffffff);
			}
			break;
		default:
			break;
		}
	}
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
				file >> stage_data[i][j];
				old_stage_data[i][j] = stage_data[i][j];
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
				file << stage_data[i][j]<< "\n";
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
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, stage_data[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
		}
	}
}

void EditScene::SaveOldData()
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			old_stage_data[i][j] = stage_data[i][j];
		}
	}
}

int EditScene::ChechSelectErea(int _i, int _j)
{
	//カーソルがツールボックス内かどうか判断
	if (cursor.x > tool_location.x && cursor.x < tool_location.x + tool_size.width && cursor.y>tool_location.y && cursor.y < tool_location.y + tool_size.height)
	{
		return TOOL_BOX;
	}
	else if (cursor.x > stage[_i][_j]->GetLocation().x && cursor.x<stage[_i][_j]->GetLocation().x + BOX_WIDTH && cursor.y>stage[_i][_j]->GetLocation().y && cursor.y < stage[_i][_j]->GetLocation().y + BOX_HEIGHT)
	{
		//ツールボックス外なら
		return STAGE_EDIT;
	}
	else
	{
		return -1;
	}
}

void EditScene::MoveInsideScreen()
{
	if (tool_location.x < 0)
	{
		tool_location.x = 0;
	}
	else if (tool_location.x + tool_size.width > SCREEN_WIDTH)
	{
		tool_location.x = SCREEN_WIDTH - tool_size.width;
	}
	else
	{
		tool_location.x = cursor.x - (tool_size.width / 2);
	}
	if (tool_location.y < 0)
	{
		tool_location.y = 0;
	}
	else if (tool_location.y + tool_size.height > SCREEN_HEIGHT)
	{
		tool_location.y = SCREEN_HEIGHT - tool_size.height;
	}
	else
	{
		tool_location.y = cursor.y - (tool_size.height / 2);
	}
}

void EditScene::MoveAllStageObj(int _x, int _y)
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->MoveStage(_x, _y);
		}
	}

}

void EditScene::ResetSelectData()
{
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			select_data[i][j] = false;
		}
	}
}