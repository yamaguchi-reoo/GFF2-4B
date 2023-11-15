#include "Score.h"
#include "PadInput.h"

int Score::total_score = 0;

//コンストラクタ
Score::Score()
{
	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	font_handle = LoadFontDataToHandle("resource/font/Misogi.dft", 0);
	score_img[0] = LoadGraph("resource/images/Score_UI.png");
	score_img[1] = LoadGraph("resource/images/Tokuten.png");
	draw_score = 0;
}

//デストラクタ
Score::~Score()
{
	// 作成したフォントデータを削除する
	DeleteFontToHandle(font_handle);
}

//更新処理
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

//描画処理
void Score::Draw() const
{
#ifdef _DEBUG

	//DrawFormatString(160, 30, 0xffffff, "%d", font_handle);

#endif // _DEBUG

	//UI背景表示
	DrawGraph(155, 10, score_img[0], TRUE);

	//スコア表示
	DrawGraph(205, 29, score_img[1], TRUE);
	DrawFormatStringToHandle(288, 27, 0x000000, font_handle, "%06d", draw_score);
}

//トータルスコアに加算(引数:加算するスコアの数値)
void Score::AddScore(int score)
{
	total_score += score;
}

void Score::SetScore()
{
	total_score = 0;
}


