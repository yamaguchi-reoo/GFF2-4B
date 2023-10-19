#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"

class Himawari;

class GameMain :
    public AbstractScene
{
private:
    Player* player; //プレイヤーのオブジェクト
    Stage* stage;   //床のオブジェクト
    Zakuro* zakuro;
    Himawari* himawari;
    int flg;        //
    int count;      //実験用

    
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

