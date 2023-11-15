#include "GameClear.h"
#include "PadInput.h"
#include "Title.h"
#include "Result.h"

GameClear::GameClear()
{
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
}
