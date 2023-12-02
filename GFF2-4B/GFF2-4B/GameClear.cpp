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
		printf("%sがありません。", &err);
	}
}

GameClear::GameClear(int _stage_num)
{
	//カットイン演出用画像
	ImageLoad(cut_in01, "resource/images/GameClear/CutIn01.png");
	ImageLoad(cut_in02, "resource/images/GameClear/CutIn02.png");
	
	//背景画像用変数
	ImageLoad(clear_back_image, "resource/images/GameClear/GameClearImage.png");

	//カットイン01の座標変数
	cut_in01_loc.x = 0.0f;			//X座標
	cut_in01_loc.y = 0.0f;			//Y座標

	//カットイン02の座標変数
	cut_in02_loc.x = 0.0f;			//X座標
	cut_in02_loc.y = 0.0f;			//Y座標

	stage_num = _stage_num;			//stage数情報格納用変数
}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{
	//X座標が300以下かつ-300以上なら4ずつ動かす
	if (cut_in01_loc.x >= -CUTIN_POS_TIMING && cut_in02_loc.x <= (CUTIN_POS_TIMING))
	{
		cut_in01_loc.x += -4.f;
		cut_in02_loc.x += 4.f;
	}
	//X座標が300以上かつ-300以下なら30ずつ動かす
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


