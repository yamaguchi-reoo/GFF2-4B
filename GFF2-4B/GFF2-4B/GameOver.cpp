#include "GameOver.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Title.h"
#include "Score.h"

//âÊëúì«çûèâä˙âªópä÷êî
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
		printf("%dÇ™Ç†ÇËÇ‹ÇπÇÒÅB", err);
	}
}

GameOver::GameOver()
{
	ImageLoad(game_over_image, "resource/font/GameOverFont.png");
	ImageLoad(game_continue_image, "resource/font/GameContinueFont.png");
	ImageLoad(player_lose_image, "resource/font/PlayerLoseFont.png");
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
		Score::SetScore();
		return new Title();
	}
	return this;
}

void GameOver::Draw() const
{
	DrawTriangle(460, 460, 460, 510, 500, 485, 0x000ff0, TRUE);
	DrawGraph(530, 460, game_over_image, FALSE);
	DrawGraph(530, 360, game_continue_image, FALSE);
	DrawGraph(400, 50, player_lose_image, FALSE);
}
