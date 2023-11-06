#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "StageData.h"
#include "Stage.h"
#include "PadInput.h"

class EditScene :
    public AbstractScene
{
private:
    CURSOR cursor;      //マウスカーソル
    int STAGE_DATA[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];   //床のオブジェクト

    bool select_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    int flg;               //
    int count[2];          //実験用
    bool onfloor_flg;      //実験用

    int stage_width;        //ステージのブロックの横の個数 
    int stage_height;       //ステージのブロックの縦の個数
public:
    //コンストラクタ
    EditScene();
    //デストラクタ
    ~EditScene();

    // 描画以外の更新を実装
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //ステージを生成する
    void LoadStageData();

    //ステージのファイルを更新する
    void UpdateStageData();

    //ステージの再読み込み
    void UpdateStage();
};


