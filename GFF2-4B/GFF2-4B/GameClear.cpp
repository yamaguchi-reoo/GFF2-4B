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
	


	stage_num = _stage_num;			//stage数情報格納用変数
}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{

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
	SetFontSize(48);
	DrawString(500, 400, "Clear", 0xffffff);
	DrawGraph(0, 0, cut_in01, TRUE);
	DrawGraph(0, 0, cut_in02, TRUE);
}
