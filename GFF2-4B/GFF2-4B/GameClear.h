#pragma once
#include "AbstractScene.h"
#include "common.h"

//カットイン01座標
struct CutIn01Pos { float x; float y; };
//カットイン02座標
struct CutIn02Pos { float x; float y; };

class GameClear :
    public AbstractScene
{
private:

    //---- 構造体の変数化 ----//

    CutIn01Pos cut_in01_loc;
    CutIn02Pos cut_in02_loc;

    //--- カットイン画像保存用変数 ---//
    int cut_in01;           //カットイン画像1
    int cut_in02;           //カットイン画像2

    //画像文字(到達完了)変数
    int stage_goal_image;   //文字画像(到達成功)
    int boss_beat_image;    //文字画像(討伐成功)

    //背景画像用変数
    int clear_back_image;   //背景画像

    //stage数取得用変数
    int stage_num;          //stage数の情報を確保する変数

public:

    //コンストラクタ
    GameClear(int _stage_num);
    //デストラクタ
    ~GameClear();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //画像読込用関数
    void ImageLoad(int& _handle, const char* _file_name);
};

