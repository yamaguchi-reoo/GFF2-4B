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

	//stage数情報格納用変数
	stage_num = _stage_num;

	//α成分用変数
	heading_alpha = 0.0f;
	choise_alpha = 0.0f;

	heading_y = 0.f;
}

GameOver::~GameOver()
{
}

AbstractScene* GameOver::Update()
{
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
	{
		heading_alpha += 100.f;

		if (heading_y <= 80){ heading_y += 40; }
		
		choise_alpha += 20.f;
	}
	if (150 <= heading_alpha)
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

	//------ 画像透明度に関する処理 ------//

	//タイトル画像のY座標が350以下ならY座標に加算する
	if (heading_y <= 80.f) { heading_y += 0.25f; }

	//見出し画像のα成分に加算を行う
	heading_alpha += 1.f;

	//見出し画像のα成分が150より大きくなったら選択画像のα成分に加算を行う
	if (heading_alpha >= 150) { choise_alpha += 2.5f; }

	return this;
}

void GameOver::Draw() const
{
	//見出し透明度設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)heading_alpha);
	//背景画像表示
	DrawGraph(0, 0, back_death_image, TRUE);

	//stage(１～３)で死亡した場合の画像を表示
	if (stage_num != 3) { DrawGraphF(250, heading_y, goal_lose_image, TRUE); }

	//stage(Boss)で死亡した場合の画像を表示
	if (stage_num == 3) { DrawGraphF(250, heading_y, boss_stage_lose_image, TRUE); }

	//透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	if (heading_alpha >= 100)
	{
		//選択肢画像とカーソル透明度設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)choise_alpha);

		//文字描画(続行)
		if (select_count == 0) { DrawGraph(530, 350, game_continue_select, TRUE); }

		if (select_count == 1) { DrawGraph(530, 350, game_continue_font, TRUE); }

		//文字描画(終了)
		if (select_count == 0) { DrawGraph(530, 450, game_finish_font, TRUE); }

		if (select_count == 1) { DrawGraph(530, 450, game_finish_select, TRUE); }

		//カーソル表示
		DrawTriangle(460, 380 + (select_count * 80), 460, 430 + (select_count * 80), 500, 405 + (select_count * 80), 0x000ff0, TRUE);
		//描画ブレンドをNoBlendにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}