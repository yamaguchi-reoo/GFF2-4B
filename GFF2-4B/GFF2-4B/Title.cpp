#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "SelectStage.h"

Title::Title()
{
	//初期化
	Select = 1;
	Once = TRUE;

}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	//十字キー↑入力
	if (PadInput::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		Select--;
		if (Select < 0)Select = 1;
	}
	//十字キー↓入力
	if (PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		Select++;
		if (Select > 1)Select = 0;
	}

	//Lスティック上入力
	if (PadInput::TipLeftLStick(STICKL_X) <= 1 && Once == TRUE)
	{
		Select--;
		if (Select < 0)Select = 1;
		Once = FALSE;
	}

	//Lスティック下入力
	if (PadInput::TipLeftLStick(STICKL_X) >= -1 && Once == TRUE)
	{
		Select++;
		if (Select > 1)Select = 0;
		Once = FALSE;
	}

	//Lスティックが元に戻されたらOnceをリセット
	if (Once == FALSE && PadInput::TipLeftLStick(STICKL_X) >= 1 && PadInput::TipLeftLStick(STICKL_X) <= -1)
	{
		Once = TRUE;
	}

	if (PadInput::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//ゲーム画面へ
		case TITLE_MENU::GAME_START:

			return new SelectStage();
			//エンド画面へ
		case TITLE_MENU::GAME_END:

			//return new End();
			//StopSoundMem(TitleBGM);
			break;
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
