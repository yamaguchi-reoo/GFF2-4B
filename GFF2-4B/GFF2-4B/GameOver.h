#pragma once
#include "AbstractScene.h"

enum class GAME_OVER_MENU
{
    GAME_MAIN = 0,
    GAME_SELECT
};
class GameOver :
    public AbstractScene
{
private:

    int game_over_image;        //文字列(ゲーム終了用)画像
    int game_continue_image;    //文字列(ゲーム続行用)画像
    int player_lose_image;      //playerが敗北したシーンで表示する画像
    int select_count;           //セレクト用のカーソルの動いた数をカウントする変数
    int once_flg;               //カーソルが動いたかどうかを確認するためのフラグ

public:

    //コンストラクタ
    GameOver();
    //デストラクタ
    ~GameOver();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //画像読込専用関数
    void ImageLoad(int& _handle, const char* _file_name);
};

