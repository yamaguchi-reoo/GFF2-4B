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
	catch (const char &err)
	{
		printf("%sがありません。", &err);
	}
}

GameOver::GameOver(int _stage_num)
{
	//画像初期化(開始)
	ImageLoad(game_finish_font, "resource/font/GameFinishFont.png");
	ImageLoad(game_finish_select, "resource/font/GameFinishSelect.png");
	
	//画像初期化(終了)
	ImageLoad(game_continue_font, "resource/font/GameContinueFont.png");
	ImageLoad(game_continue_select, "resource/font/GameContinueSelect.png");
	
	//画像初期化(到達失敗)
	ImageLoad(goal_lose_image, "resource/font/StageLoseFont.png");
	
	//画像初期化(討伐失敗)
	ImageLoad(boss_stage_lose_image, "resource/font/PlayerLoseFont.png");
	
	//背景画像初期化(Playerが倒れている画像)
	ImageLoad(back_death_image, "resource/images/BackDeathImage.png");
	
	select_count = 0;
	once_flg = TRUE;
	stage_num = _stage_num;
	alpha = 0.0f;
}

GameOver::~GameOver()
{
}

AbstractScene* GameOver::Update()
{
	if (200 <= alpha)
	{
		//Lスティック上入力
		//左スティックの傾き具合がY座標に0.8以上かつ
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
				//スコアの初期化
				Score::ResetScore();
				return new GameMain(stage_num);

			case GAME_OVER_MENU::GAME_SELECT:
				//スコアの初期化
				Score::ResetScore();
				return new SelectStage;

			}

		}
	}
	alpha += 0.8f;
	return this;
}

void GameOver::Draw() const
{
	//透明度設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//背景画像表示
	DrawGraph(0, 0, back_death_image, TRUE);
	//カーソル表示
	DrawTriangle(460, 380 + (select_count * 80), 460, 430 + (select_count * 80), 500, 405 + (select_count * 80), 0x000ff0, TRUE);

	//文字描画(続行)
	if (select_count == 0) { DrawGraph(530, 350, game_continue_select, TRUE); }
	if (select_count == 1) { DrawGraph(530, 350, game_continue_font, TRUE); }
	//文字描画(終了)
	if (select_count == 0) { DrawGraph(530, 450, game_finish_font, TRUE);}
	if (select_count == 1) { DrawGraph(530, 450, game_finish_select, TRUE); }

	//stage(１～３)で死亡した場合の画像を表示
	if (stage_num != 3){ DrawGraph(250, 50, goal_lose_image, TRUE); }
	//stage(Boss)で死亡した場合の画像を表示
	if (stage_num == 3){ DrawGraph(250, 50, boss_stage_lose_image, TRUE); }

	//透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
