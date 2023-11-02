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
    int STAGE_DATA[STAGE_HEIGHT][STAGE_WIDTH];
    Stage* stage[STAGE_HEIGHT][STAGE_WIDTH];   //床のオブジェクト

    bool select_data[STAGE_HEIGHT][STAGE_WIDTH];
    int flg;               //
    int count[2];          //実験用
    bool onfloor_flg;      //実験用
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
    void CreateStage();

    //ステージのファイルを更新する
    void UpdateStageData();
};


