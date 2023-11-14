#include "Score.h"
#include "DxLib.h"

Score::Score()
{
	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	font_handle = LoadFontDataToHandle("Misogi.dft", 1);

	total_score = 0;
}

Score::~Score()
{
	// 作成したフォントデータを削除する
	DeleteFontToHandle(font_handle);
}

void Score::Update()
{
}

void Score::Draw() const
{
	// 作成したフォントで画面左上に『Ｈｅｌｌｏｗ！！』と白色の文字列を描画する
	DrawStringToHandle(160, 30, "得点:", 0xffffff, font_handle);
}
