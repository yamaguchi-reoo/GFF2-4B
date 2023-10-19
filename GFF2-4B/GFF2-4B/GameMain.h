#pragma once
#include "AbstractScene.h"
#include "Stage.h"

class GameMain :
    public AbstractScene
{
private:
    Stage* stage;   //床のオブジェクト
    int flg;
public:
    //コンストラクタ
    GameMain();
    //デストラクタ
    ~GameMain();

    // 描画以外の更新を実装
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

