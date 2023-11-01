#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Attack.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"
#include "bamboo.h"
#include "Scroll.h"
#include "PowerGauge.h"
#include "PlayerHP.h"
#include "Boss.h"
#include "BossHands.h"

//effect
#include "Effect.h"

#define ATTACK_NUM 100   //画面に存在できる最大の攻撃数

class Player;

class GameMain :
    public AbstractScene
{
private:
    Player* player;    //プレイヤーのオブジェクト
    Stage* stage[FLOOR_NUM];   //床のオブジェクト
    Attack* attack[ATTACK_NUM];     //攻撃のオブジェクト

    //エネミー
    Zakuro* zakuro;    //ザクロ
    Himawari* himawari;//ひまわり
    Iruka* iruka;      //イルカ

    Boss* boss; //ボス
    BossHands* hands;//ボスの腕

    Bamboo* bamboo[BAMBOO_NUM];
    SceneScroll* scene_scroll;  //スクロールクラスのオブジェクト

    PowerGauge* powergauge;  //強化ゲージのオブジェクト
    PlayerHP* playerhp;  //プレイヤーHPUIのオブジェクト

    Effect* effect;     //しぶきエフェクトのオブジェクト

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

    //攻撃を発生させる(_location = 攻撃したプレイヤーor敵の中心座標  _direction = 攻撃する方向(0=右 1=左))
    void SpawnAttack(AttackData _attackdata);

    //各当たり判定の処理
    void HitCheck();
};

