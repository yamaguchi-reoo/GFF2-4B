#include"DxLib.h"

#define FRAMERATE 60.0 //フレームレート

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("GFF2-4B");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	SetGraphMode(1920, 1280, 32);	//画面サイズの設定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	// ゲームループ
	while ((ProcessMessage() == 0)) {
		ScreenFlip();			// 裏画面の内容を表画面に反映
	}
	return 0;
}