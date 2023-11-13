#include "Score.h"
#include "DxLib.h"

Score::Score()
{
	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	FontHandle = LoadFontDataToHandle("Misogi.dft", 1);

	Score = 0;
}

Score::~Score()
{
	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle);
}

void Score::Update()
{
}

void Score::Draw() const
{
	// 作成したフォントで画面左上に『Ｈｅｌｌｏｗ！！』と白色の文字列を描画する
	DrawStringToHandle(0, 0, "得点:〇〇〇", GetColor(255, 255, 255), FontHandle);
}
