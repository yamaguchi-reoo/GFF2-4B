#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

Title::Title()
{
	//初期化
	Select = 0;
	Once = TRUE;

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
	return this;
}

void Title::Draw()const
{
	DrawString(150, 100, "禊", 0xffffff);

	//メニューの描画
	DrawString(730, 260, "開始", 0xffffff);
	//DrawString(730, 320, "ヘルプ", 0xffffff);
	DrawString(730, 340/*400*/, "終了", 0xffffff);
	//DrawFormatString(730, 410/*400*/,0x00ff00, "%d",Select);


	////カーソルの描画
	//int select_y = 230 + Select * 80;
	//カーソル表示
	DrawTriangle(670, 245 + Select * 80, 700, 265 + Select * 80, 670, 285 + Select * 80, 0xff0000, TRUE);
}
