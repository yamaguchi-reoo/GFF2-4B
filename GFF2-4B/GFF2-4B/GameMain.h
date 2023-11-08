#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Attack.h"
#include "StageData.h"
#include "Stage.h"
#include "Himawari.h"
#include "Zakuro.h"
#include "Iruka.h"
#include "bamboo.h"
#include "Scroll.h"
#include "PowerGauge.h"
#include "PlayerHP.h"

//effect
#include "Effect.h"

class Player;

class GameMain :
    public AbstractScene
{
private:
    int STAGE_DATA[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    Player* player;                     //プレイヤーのオブジェクト
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];   //床のオブジェクト
    Attack* attack[ATTACK_NUM];     //攻撃のオブジェクト

    //エネミー
    Zakuro* zakuro[ZAKURO_MAX];    //ザクロ
    Himawari* himawari[HIMAWARI_MAX];//ひまわり
    Iruka* iruka[IRUKA_MAX];      //イルカ

    Bamboo* bamboo[BAMBOO_NUM];
    SceneScroll* scene_scroll;  //スクロールクラスのオブジェクト

    PowerGauge* powergauge;  //強化ゲージのオブジェクト
    PlayerHP* playerhp;  //プレイヤーHPUIのオブジェクト

    Effect* effect[SPLASH_MAX];     //しぶきエフェクトのオブジェクト

    int flg;               //
    int count[2];          //実験用
    bool onfloor_flg;      //実験用
    int who;                //誰が攻撃したか判断する用

    int stage_width;        //ステージのブロックの横の個数 
    int stage_height;       //ステージのブロックの縦の個数

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

    //ステージファイルを読み込む
    void LoadStageData();
};

