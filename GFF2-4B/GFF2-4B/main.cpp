#include "DxLib.h"
#include "SceneManager.h"
#include "FpsController.h"
#include "PadInput.h"
#include "SoundManager.h"
#include "common.h"
#include "Title.h"

#define FRAMERATE 60.0 //フレームレート
//メインプログラム 開始

int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
    SetMainWindowText("禊(misogi)");         // ウィンドウタイトルを設定

    ChangeWindowMode(TRUE);                        // ウインドウモードで起動

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ

    if (DxLib_Init() == -1) return -1;             // DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);                 // 描画先画面を裏にする（ダブルバッファリング）

    //音声データ読み込み
    SoundManager::LoadSound();

    // タイトル シーンオブジェクト作成
    SceneManager* sceneMng = new SceneManager((AbstractScene*) new Title());

    //fps制御
    FpsController* FPSC= new FpsController(FRAMERATE, 800);

    // ゲームループし、シーンマネジャーでシーンの更新
    while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr))
    {
        ClearDrawScreen(); // 画面の初期化

        PadInput::UpdateKey();//パッドの入力処理
        KeyInput::UpdateKey();//キーボードの入力処理
        SoundManager::UpdateSound();    //音声データの更新処理

        // シーンマネジャーでシーンの描画開始
        sceneMng->Draw();

        FPSC->All();
#ifdef _DEBUG
        FPSC->Disp();
#endif

        //強制終了
        //Escapeキーまたはバックボタンを押したら強制終了
        if(PadInput::OnButton(XINPUT_BUTTON_BACK)) {  
            break;
        }
        ScreenFlip(); // 裏画面の内容を表画面に反映する

    };

    SoundManager::DeleteSound(); //音声データの削除
    DxLib_End(); // DXライブラリ使用の終了処理
    return 0;    // プログラムの終了
};