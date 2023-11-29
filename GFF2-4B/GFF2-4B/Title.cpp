#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

//画像読込初期化用関数
void Title::ImageLoad(int& _handle, const char* _file_name)
{
	try
	{
		_handle = LoadGraph(_file_name);
		if (_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%sがありません。", &err);
	}
}

Title::Title()
{
	//初期化
	Select = 0;
	Once = TRUE;
	title_alpha = 0;
	title_x = 0;
	font_alpha = 0;

	//文字画像初期化(禊)
	ImageLoad(title_font, "resource/font/TitleFont.png");

	//画像初期化(開始)
	ImageLoad(game_start_image, "resource/font/GameStartFont.png");
	ImageLoad(game_start_select, "resource/font/GameStartSelect.png");
	//画像初期化(終了)
	ImageLoad(game_finish_image, "resource/font/GameFinishFont.png");
	ImageLoad(game_finish_select, "resource/font/GameFinishSelect.png");
}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	//十字キー↑入力
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_DPAD_UP) || KeyInput::OnKey(KEY_INPUT_W)
#else
		PadInput::OnButton(XINPUT_BUTTON_DPAD_UP)
#endif
		)
	{
		Select--;
		if (Select <= -1)Select = 1;
	}
	//十字キー↓入力
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN) || KeyInput::OnKey(KEY_INPUT_S)
#else
		PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN)
#endif
		)
	{
		Select++;
		if (Select > 1)Select = 0;
	}

	//Lスティック上入力
	if (PadInput::TipLeftLStick(STICKL_Y) > 0.8f && 
		PadInput::TipLeftLStick(STICKL_Y) < 1.0f &&
		Once == TRUE)
	{
		Once = FALSE;
		Select--;
		if (Select < 0)Select = 1;
	}

	//Lスティック下入力
	if (PadInput::TipLeftLStick(STICKL_Y) > -1.f && 
		PadInput::TipLeftLStick(STICKL_Y) < -0.8f && 
		Once == TRUE)
	{
		Once = FALSE;
		Select++;
		if (Select > 1)Select = 0;
	}

	//Lスティックが元に戻されたらOnceをリセット
	if (Once == FALSE && 
		PadInput::TipLeftLStick(STICKL_Y) <= 0.1f &&
		PadInput::TipLeftLStick(STICKL_Y) >= -0.1f)
	{
		Once = TRUE;
	}
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//ゲーム画面へ
		case TITLE_MENU::GAME_START:

			return new SelectStage();
			//エンド画面へ
		case TITLE_MENU::GAME_END:
			
			return nullptr;
		default:
			break;
		}
	}
	if (title_x <= 100) { title_x += 1; }
	title_alpha += 1;
	if(title_alpha >= 150){ font_alpha += 2.5; }
	return this;
}

void Title::Draw()const
{
	//透明度設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);
	//タイトル画像表示
	DrawGraph(title_x, 25, title_font, TRUE);
	//透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/***** 選択画像描画 *****/
	if (title_x >= 100)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, font_alpha);
		//文字描画(開始)
		if (Select == 0) { DrawGraph(850, 495, game_start_select, TRUE); }
		if (Select == 1) { DrawGraph(850, 495, game_start_image, TRUE); }
		//文字描画(終了)
		if (Select == 0) { DrawGraph(850, 575, game_finish_image, TRUE); }
		if (Select == 1) { DrawGraph(850, 575, game_finish_select, TRUE); }
		//カーソルの表示
		DrawTriangle(790, 500 + (Select * 90), 820, 520 + (Select * 90), 790, 540 + (Select * 90), 0xff0000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}
