#include "GameOver.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"

GameOver::GameOver()
{
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
		return new Title();
	}
	return this;
}

void GameOver::Draw() const
{

	DrawString(500, 400, "Ž€", 0xffffff);
}
