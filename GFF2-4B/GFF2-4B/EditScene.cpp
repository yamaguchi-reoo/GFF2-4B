#include "EditScene.h"
#include <fstream>
#include <iostream>
#include <string>

#include "GameMain.h"

EditScene::EditScene(int _stage)
{
	now_stage = _stage;
	current_type = 0;
	tool_size.width = 500;
	tool_size.height = 100;
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
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
	//�J�[�\���̈ʒu�X�V
	cursor = KeyInput::GetMouseCursor();
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			stage[i][j]->Update();
			if (cursor.x > 0 && cursor.x < tool_size.width && cursor.y>0 && cursor.y < tool_size.height)
			{
				for (int i = 0; i < OBJECT_TYPE_NUM; i++)
				{
					if (cursor.x > (i * 50) && cursor.x < (i * 50) + 50 && cursor.y>0 && cursor.y < 50)
					{
						if (KeyInput::OnPressedMouse(MOUSE_INPUT_LEFT))
						{
							current_type = i;
						}
					}
				}
			}
			else if (cursor.x > stage[i][j]->GetLocation().x && cursor.x<stage[i][j]->GetLocation().x + BOX_WIDTH && cursor.y>stage[i][j]->GetLocation().y && cursor.y < stage[i][j]->GetLocation().y + BOX_HEIGHT)
			{
				select_data[i][j] = true;
				if (KeyInput::OnPressedMouse(MOUSE_INPUT_LEFT))
				{
					STAGE_DATA[i][j] = current_type;
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
	//�X�e�[�W�𓮂���
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
	//�Q�[�����C���ɖ߂�
	if (KeyInput::OnKey(KEY_INPUT_B))
	{
		UpdateStageData(now_stage);
		return new GameMain(now_stage);
	}
	//�X�e�[�W�̉����𑝂₷
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
			if (STAGE_DATA[i][j] == 5)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0xff00ff , true);
			}
			if (STAGE_DATA[i][j] == 6)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0x00ffff, true);
			}
			if (STAGE_DATA[i][j] == 7)
			{
				DrawBoxAA(stage[i][j]->GetLocation().x, stage[i][j]->GetLocation().y, stage[i][j]->GetLocation().x + BOX_WIDTH, stage[i][j]->GetLocation().y + BOX_HEIGHT, 0xffff00, true);
			}
		}
	}
	DrawBox(0, 0, tool_size.width, tool_size.height, 0x000000, true);
	DrawBox(0, 0, tool_size.width, tool_size.height, 0xffffff, false);
	DrawString(0, 70, "���N���b�N�őI�����z�u", 0xffffff);
	DrawString(300, 70, "B�L�[�ŃQ�[�����C��", 0xffffff);

	//���ݑI�𒆂̃I�u�W�F�N�g�𕪂���₷��	
	for (int i = 0; i < OBJECT_TYPE_NUM; i++)
	{
		DrawBox((i * 50), 0, (i * 50) + 50, 50, 0x000000, true);
		DrawBox((i * 50), 0, (i * 50) + 50, 50, 0xffffff, false);
		if (current_type == i)
		{
			DrawBox((i * 50), 0, (i * 50) + 50, 50, 0xffffff, true);
			DrawBox((i * 50), 0, (i * 50) + 50, 50, 0x000000, false);
		}
		switch (i)
		{
		case 0:
			if (current_type == i)
			{
				DrawString((i * 50) + 15, 15, "��", 0x000000);
			}
			else
			{
				DrawString((i * 50) + 15, 15, "��", 0xffffff);
			}
			break;
		case 1:
			if (current_type == i)
			{
				DrawString((i * 50) + 10, 15, "�n��", 0x000000);
			}
			else
			{
				DrawString((i * 50) + 10, 15, "�n��", 0xffffff);
			}
			break;
		case 2:
			if (current_type == i)
			{
				DrawString((i * 50) + 15, 15, "��", 0x000000);
			}
			else
			{
				DrawString((i * 50) + 15, 15, "��", 0xffffff);
			}
			break;
		case 3:
			if (current_type == i)
			{
				DrawString((i * 50) + 15, 15, "��", 0x000000);
			}
			else
			{
				DrawString((i * 50) + 15, 15, "��", 0xffffff);
			}
			break;
		case 4:
			if (current_type == i)
			{
				DrawString((i * 50) + 15, 15, "�_", 0x000000);
			}
			else
			{
				DrawString((i * 50) + 15, 15, "�_", 0xffffff);
			}
			break;
		case 5:
			if (current_type == i)
			{
				DrawString((i * 50), 15, "�U�N��", 0x000000);
			}
			else
			{
				DrawString((i * 50), 15, "�U�N��", 0xffffff);
			}
			break;
		case 6:
			if (current_type == i)
			{
				DrawString((i * 50), 15, "�C���J", 0x000000);
			}
			else
			{
				DrawString((i * 50), 15, "�C���J", 0xffffff);
			}
			break;
		case 7:
			if (current_type == i)
			{
				DrawString((i * 50)+20, 15, "�Ђ�", 0x000000);
			}
			else
			{
				DrawString((i * 50)+20, 15, "�Ђ�", 0xffffff);
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
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		file >> stage_width;
		file >> stage_height;
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
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
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		file << stage_width << "\n";
		file << stage_height << "\n";
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
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
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, STAGE_DATA[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
		}
	}
}