#include "EditScene.h"
#include <fstream>
#include <iostream>
#include <string>

#include "GameMain.h"

Location camera_location = { 0,0 };

EditScene::EditScene(int _stage)
{
	now_stage = _stage;
	current_type = 0;
	tool_location.x = 100;
	tool_location.y = 0;
	tool_size.width = (OBJECT_TYPE_NUM * 50) + 50;
	tool_size.height = 100;
	tool_pickup_flg = false;
	LoadStageData(now_stage);
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
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
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			delete stage[i][j];
		}
	}
}

AbstractScene* EditScene::Update()
{
	//�J�[�\���̈ʒu�X�V
	cursor = KeyInput::GetMouseCursor();
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Update();
			stage[i][j]->SetScreenPosition(camera_location);
			switch (ChechSelectErea(i, j))
			{
			case STAGE_EDIT:
				//���Z�b�g���Ă���I�����ꂽselect_data��true�ɂ���
				ResetSelectData();
				select_data[i][j] = true;

				//�ς��悤�Ƃ��Ă���X�e�[�W�̃f�[�^���ύX��̃f�[�^�ƈꏏ�łȂ��Ȃ�
				if (stage_data[i][j] != current_type)
				{
					//�ЂƂO�̏�Ԃ�ێ�
					if (KeyInput::OnMouse(MOUSE_INPUT_LEFT))
					{
						SaveOldData();
					}
					//�X�V
					if (KeyInput::OnPressedMouse(MOUSE_INPUT_LEFT))
					{
						stage_data[i][j] = current_type;
					}
				}
				//�ς��悤�Ƃ��Ă���X�e�[�W�̃f�[�^���ύX��̃f�[�^�ƈꏏ�łȂ��Ȃ�
				if (stage_data[i][j] != 0)
				{
					//�ЂƂO�̏�Ԃ�ێ�
					if (KeyInput::OnMouse(MOUSE_INPUT_RIGHT))
					{
						SaveOldData();
					}
					//�X�V
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
				//����œ�����
				if (KeyInput::OnPressedMouse(MOUSE_INPUT_RIGHT))
				{
					tool_pickup_flg = true;
				}
				break;
			default:
				break;
			}
		}
	}
	//����œ�����
	if (tool_pickup_flg == true)
	{
		MoveInsideScreen();
	}
	if (KeyInput::OnReleaseMouse(MOUSE_INPUT_RIGHT))
	{
		tool_pickup_flg = false;
	}

	//���������
	if (KeyInput::OnPresed(KEY_INPUT_LCONTROL) && KeyInput::OnKey(KEY_INPUT_Z))
	{
		for (int i = 0; i < stage_height_num; i++)
		{
			for (int j = 0; j < stage_width_num; j++)
			{
				stage_data[i][j] = old_stage_data[i][j];
			}
		}
	}

	//�X�e�[�W�̍X�V
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->SetStageType(stage_data[i][j]);
		}
	}

	//�J�������W�𓮂���
	if (KeyInput::OnPresed(KEY_INPUT_W))
	{
		camera_location.y -= 10;
	}
	if (KeyInput::OnPresed(KEY_INPUT_A))
	{
		camera_location.x -= 10;
	}
	if (KeyInput::OnPresed(KEY_INPUT_S))
	{
		camera_location.y += 10;
	}
	if (KeyInput::OnPresed(KEY_INPUT_D))
	{
		camera_location.x += 10;
	}

	if (KeyInput::OnKey(KEY_INPUT_G))
	{
		UpdateStageWidth(+1);
	}
	if (KeyInput::OnKey(KEY_INPUT_F))
	{
		UpdateStageWidth(-1);
	}
	//�Q�[�����C���ɖ߂�
	if (KeyInput::OnKey(KEY_INPUT_B))
	{
		UpdateStageData(now_stage);
		return new GameMain(now_stage);
	}
	//�S������
	if (KeyInput::OnKey(KEY_INPUT_0))
	{
		SaveOldData();
		for (int i = 0; i < stage_height_num; i++)
		{
			for (int j = 0; j < stage_width_num; j++)
			{
				stage_data[i][j] = 0;
			}
		}
	}
	return this;
}

void EditScene::Draw()const
{
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			stage[i][j]->Draw();
			if (select_data[i][j] == true)
			{
				DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x +BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0xff0000, false);
			}
			if (stage_data[i][j] == 5)
			{
				DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0xff00ff , true);
			}
			if (stage_data[i][j] == 6)
			{
				DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0x00ffff, true);
			}
			if (stage_data[i][j] == 7)
			{
				DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0xffff00, true);
			}
		}
	}
	int old_size = GetFontSize();
	SetFontSize(16);
	DrawBoxAA(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0x000000, true);
	DrawBoxAA(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0xffffff, false);
	DrawStringF(tool_location.x, tool_location.y + 60, "���N���b�N�őI�����z�u", 0xffffff);
	DrawStringF(tool_location.x, tool_location.y + 80, "ctrl+z�ň�߂�", 0xffffff);
	DrawStringF(tool_location.x + tool_size.width-270, tool_location.y + 80, "B�L�[�ŕۑ����Q�[�����C���֖߂�", 0xffffff);
	//���ݑI�𒆂̃I�u�W�F�N�g�𕪂���₷��	
	for (int i = 0; i < OBJECT_TYPE_NUM; i++)
	{
		DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, true);
		DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, false);
		if (current_type == i)
		{
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, true);
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, false);
		}
		if (current_type == i)
		{
			DrawFormatStringF(tool_location.x + (i * 50), tool_location.y + 15, 0x000000, "%s", obj_string[i]);
		}
		else
		{
			DrawFormatStringF(tool_location.x + (i * 50), tool_location.y + 15, 0xffffff, "%s", obj_string[i]);
		}
	}
	SetFontSize(old_size);
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
		file >> stage_width_num;
		file >> stage_height_num;
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < stage_height_num; i++)
		{
			for (int j = 0; j < stage_width_num; j++)
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
	//�t�@�C�����ǂݍ��߂Ă����Ȃ�
	if (file)
	{
		file << stage_width_num << "\n";
		file << stage_height_num << "\n";
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < stage_height_num; i++)
		{
			for (int j = 0; j < stage_width_num; j++)
			{
				file << stage_data[i][j]<< "\n";
			}
		}
	}
}

void EditScene::UpdateStageWidth(int _width)
{
	stage_width_num += _width;
	//�g���̏���Ək���̉���
	if (stage_width_num > MAX_STAGE_WIDTH)
	{
		stage_width_num = MAX_STAGE_WIDTH;
	}
	if (stage_width_num <= 0)
	{
		stage_width_num = 1;
	}

	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			if (stage_data[i][j] < 0)
			{
				stage_data[i][j] = 0;
			}
			stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, stage_data[i][j]);
			stage[i][j]->SetDebugFlg();
			select_data[i][j] = false;
			//if (stage[i][j] == nullptr)
			//{
			//	stage[i][j] = new Stage(j * BOX_WIDTH, i * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, stage_data[i][j]);
			//	stage[i][j]->SetDebugFlg();
			//	select_data[i][j] = false;
			//}
		}
	}
}

void EditScene::SaveOldData()
{
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			old_stage_data[i][j] = stage_data[i][j];
		}
	}
}

int EditScene::ChechSelectErea(int _i, int _j)
{
	//�J�[�\�����c�[���{�b�N�X�����ǂ������f
	if (cursor.x > tool_location.x && cursor.x < tool_location.x + tool_size.width && cursor.y>tool_location.y && cursor.y < tool_location.y + tool_size.height)
	{
		return TOOL_BOX;
	}
	//�c�[���{�b�N�X������ł��Ȃ���΃c�[���{�b�N�X�O�̏���
	else if (cursor.x > stage[_i][_j]->GetLocalLocation().x && cursor.x<stage[_i][_j]->GetLocalLocation().x + BOX_WIDTH && cursor.y>stage[_i][_j]->GetLocalLocation().y && cursor.y < stage[_i][_j]->GetLocalLocation().y + BOX_HEIGHT && tool_pickup_flg == false)
	{
		return STAGE_EDIT;
	}
	else
	{
		return -1;
	}
}

void EditScene::MoveInsideScreen()
{
	tool_location.x = cursor.x - (tool_size.width / 2);
	if (tool_location.x < 0)
	{
		tool_location.x = 0;
	}
	else if (tool_location.x + tool_size.width > SCREEN_WIDTH)
	{
		tool_location.x = SCREEN_WIDTH - tool_size.width;
	}

	tool_location.y = cursor.y - (tool_size.height / 2);
	if (tool_location.y < 0)
	{
		tool_location.y = 0;
	}
	else if (tool_location.y + tool_size.height > SCREEN_HEIGHT)
	{
		tool_location.y = SCREEN_HEIGHT - tool_size.height;
	}
}

void EditScene::ResetSelectData()
{
	for (int i = 0; i < stage_height_num; i++)
	{
		for (int j = 0; j < stage_width_num; j++)
		{
			select_data[i][j] = false;
		}
	}
}