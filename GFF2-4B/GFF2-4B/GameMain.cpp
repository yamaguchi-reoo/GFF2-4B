#include "GameMain.h"
#include "Dxlib.h"
#include "PadInput.h"

GameMain::GameMain()
{
	stage = new Stage();
	zakuro = new Zakuro();
	himawari = new Himawari();
	flg = false;
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	//°‚ÌXV
	stage->Update();
	if (KeyInput::OnKey(KEY_INPUT_A)) {
		flg = true;
	}
	return this;
}

void GameMain::Draw() const
{
	
	SetFontSize(42);
	DrawString(400, 0, "GameMain", 0xffffff);

	//°‚Ì•`‰æ
	stage->Draw();
	if (flg == true) {
		DrawString(300, 300,"flg", 0xffffff);
	}
	zakuro->Draw();
	himawari->Draw();
}
