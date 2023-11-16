#pragma once
#include "AbstractScene.h"
class GameOver :
    public AbstractScene
{
private:
    int game_over_image;        //文字列(ゲーム終了用)画像
    int game_continue_image;    //文字列(ゲーム続行用)画像
    int player_lose_image;      //playerが敗北したシーンで表示する画像

public:

    GameOver();
    ~GameOver();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    void ImageLoad(int& _handle, const char* _file_name);
};

