#include "GameOver.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"
#include "Score.h"
#include "SelectStage.h"
#include "GameMain.h"

//画像読込初期化用関数
void GameOver::ImageLoad(int& _handle,const char* _file_name)
{
	try 
	{
		_handle = LoadGraph(_file_name);
		if (_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (int& err)
	{
		printf("%dがありません。", err);
	}
}

GameOver::GameOver(int _stage_num)
{
	ImageLoad(game_over_image, "resource/font/GameOverFont.png");
	ImageLoad(game_continue_image, "resource/font/GameContinueFont.png");
	ImageLoad(player_lose_image, "resource/font/PlayerLoseFont.png");
	select_count = 0;
	once_flg = TRUE;
	stage_num = _stage_num;
}

GameOver::~GameOver()
{
}

AbstractScene* GameOver::Update()
{
	//Lスティック上入力
	if (PadInput::TipLeftLStick(STICKL_Y) > 0.8f &&
		PadInput::TipLeftLStick(STICKL_Y) < 1.0f &&
		once_flg == TRUE)
	{
		once_flg = FALSE;
		select_count--;
		if (select_count < 0)select_count = 1;
	}
	//Lスティック上入力
	if (PadInput::TipLeftLStick(STICKL_Y) > -1.0f &&
		PadInput::TipLeftLStick(STICKL_Y) < -0.8f &&
		once_flg == TRUE)
	{
		once_flg = FALSE;
		select_count--;
		if (select_count < 0)select_count = 1;
	}
	//Lスティックが元に戻されたらOnceをリセット
	if (once_flg == FALSE &&
		PadInput::TipLeftLStick(STICKL_Y) <= 0.1f &&
		PadInput::TipLeftLStick(STICKL_Y) >= -0.1f)
	{
		once_flg = TRUE;
}
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
	{
		switch (static_cast<GAME_OVER_MENU>(select_count))
		{
		case GAME_OVER_MENU::GAME_MAIN:
			return new GameMain(stage_num);

		case GAME_OVER_MENU::GAME_SELECT:
			return new SelectStage;

		}
		//スコアの初期化
		Score::ResetScore();
	}
	return this;
}

void GameOver::Draw() const
{
	DrawTriangle(460, 380 + (select_count * 80), 460, 430 + (select_count * 80), 500, 405 + (select_count * 80), 0x000ff0, TRUE);
	DrawGraph(530, 460, game_over_image, FALSE);
	DrawGraph(530, 360, game_continue_image, FALSE);
	DrawGraph(400, 50, player_lose_image, FALSE);
}
