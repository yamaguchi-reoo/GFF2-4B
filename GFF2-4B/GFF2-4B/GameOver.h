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

    //文字画像変数
    int game_finish_font;       //文字画像(終了:未選択状態)
    int game_finish_select;     //文字画像(終了:選択状態)
    int game_continue_font;     //文字画像(続行:未選択状態)
    int game_continue_select;   //文字画像(続行:選択状態)
    //文字画像変数
    int goal_lose_image;        //文字画像(到達失敗)
    int boss_stage_lose_image;  //文字画像(討伐失敗)
    //背景画像
    int back_death_image;       //背景画像(Playerが倒れている画像)
    //カーソル用変数
    int select_count;           //セレクト用のカーソルの動いた数をカウントする変数
    int once_flg;               //カーソルが動いたかどうかを確認するためのフラグ
    //stage数情報取得用変数
    int stage_num;              //ステージ数の確保
    //透明度用変数
    float alpha;                //画像のY座標

public:

    //コンストラクタ
    GameOver(int _stage_num);
    //デストラクタ
    ~GameOver();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //画像読込専用関数
    void ImageLoad(int& _handle, const char* _file_name);
};

