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
	if (PadInput::OnPressed(XINPUT_BUTTON_A))
	{
		return new Title();
	}
	return this;
}

void GameOver::Draw() const
{

	DrawString(500, 400, "Ž€", 0xffffff);
}
