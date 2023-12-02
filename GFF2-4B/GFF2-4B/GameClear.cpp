#include "GameClear.h"
#include "PadInput.h"
#include "Title.h"
#include "Result.h"

void GameClear::ImageLoad(int& _handle, const char* _file_name)
{
	try 
	{
		_handle = LoadGraph(_file_name);
		if(_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%s������܂���B", &err);
	}
}

GameClear::GameClear(int _stage_num)
{
	//�J�b�g�C�����o�p�摜
	ImageLoad(cut_in01, "resource/images/GameClear/CutIn01.png");
	ImageLoad(cut_in02, "resource/images/GameClear/CutIn02.png");
	
	//�w�i�摜�p�ϐ�
	ImageLoad(clear_back_image, "resource/images/GameClear/GameClearImage.png");

	//�J�b�g�C��01�̍��W�ϐ�
	cut_in01_loc.x = 0.0f;			//X���W
	cut_in01_loc.y = 0.0f;			//Y���W

	//�J�b�g�C��02�̍��W�ϐ�
	cut_in02_loc.x = 0.0f;			//X���W
	cut_in02_loc.y = 0.0f;			//Y���W

	stage_num = _stage_num;			//stage�����i�[�p�ϐ�
}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{
	//X���W��300�ȉ�����-300�ȏ�Ȃ�4��������
	if (cut_in01_loc.x >= -CUTIN_POS_TIMING && cut_in02_loc.x <= (CUTIN_POS_TIMING))
	{
		cut_in01_loc.x += -4.f;
		cut_in02_loc.x += 4.f;
	}
	//X���W��300�ȏォ��-300�ȉ��Ȃ�30��������
	if (cut_in01_loc.x <= -CUTIN_POS_TIMING && cut_in02_loc.x >= (CUTIN_POS_TIMING))
	{
		cut_in01_loc.x += -50.f;
		cut_in02_loc.x += 50.f;
	}
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		) {
		return new Result();
	}

	return this;
}

void GameClear::Draw() const
{
	DrawGraph(0, 0, clear_back_image, TRUE);

	DrawGraphF(cut_in01_loc.x, cut_in01_loc.y, cut_in01, TRUE);
	DrawGraphF(cut_in02_loc.x, cut_in02_loc.y, cut_in02, TRUE);
}


