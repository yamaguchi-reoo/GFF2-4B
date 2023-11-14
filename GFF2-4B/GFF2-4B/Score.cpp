#include "Score.h"
#include "PadInput.h"

Score::Score()
{
	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	font_handle = LoadFontDataToHandle("resource/font/Misogi.dft", 0);
	score_img = LoadGraph("resource/images/Score_UI.png");

	total_score = 0;
	draw_score = 0;
}

Score::~Score()
{
	// 作成したフォントデータを削除する
	DeleteFontToHandle(font_handle);
}

void Score::Update()
{
#ifdef _DEBUG

	//５を押したらスコア加算
	if (KeyInput::OnKey(KEY_INPUT_5))
	{
		total_score += 135;
	}

#endif // _DEBUG

	//スコアを少しずつ増やす(画面表示)
	if (total_score > draw_score)
	{
		draw_score += 4;
	}
	else if (total_score < draw_score)
	{
		draw_score = total_score;
	}
}

void Score::Draw() const
{
#ifdef _DEBUG

	//DrawFormatString(160, 30, 0xffffff, "%d", font_handle);

#endif // _DEBUG

	//UI背景表示
	DrawGraph(155, 10, score_img, TRUE);

	//スコア表示
	DrawFormatStringToHandle(210, 26, 0x000000, font_handle, "点数:%6d", draw_score);
}

void Score::AddScore(int score)
{
	total_score += score;
}
