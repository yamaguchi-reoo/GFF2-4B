#include "Result.h"
#include "SelectStage.h"
#include "Score.h"
#include "PadInput.h"

//コンストラクタ
Result::Result()
{
	score = Score::GetScore();
	draw_score = 0;
}

//デストラクタ
Result::~Result()
{
}

// 描画以外の更新を実装
AbstractScene* Result::Update()
{

	//スコアを少しずつ増やす(画面表示)
	if (score > draw_score)
	{
		draw_score += 30;
	}
	else if (score < draw_score)
	{
		draw_score = score;
	}

	if (draw_score == score)
	{

		//Aボタンが押されたらステージ選択画面に遷移
		if (
#ifdef _DEBUG
			PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
			PadInput::OnButton(XINPUT_BUTTON_A)
#endif
			)
		{
			Score::SetScore();
			return new SelectStage();
		}
	}

	return this;
}

//描画に関することを実装
void Result::Draw() const
{
	SetFontSize(60);
	DrawFormatString(440, 290, 0xffffff, "得点：%06d",draw_score);
}