#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"
#include "bamboo.h"
#include "Scroll.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;    //プレイヤーのオブジェクト
    Stage* stage[2];   //床のオブジェクト

    //エネミー
    Zakuro* zakuro;    //ザクロ
    Himawari* himawari;//ひまわり
    Iruka* iruka;      //イルカ

    Bamboo* bamboo[BAMBOO_NUM];
    //SceneScroll* scene_scroll;  //スクロールクラスのオブジェクト

    int flg;        //
    int count[2];      //実験用
    bool onfloor_flg;      //実験用
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

