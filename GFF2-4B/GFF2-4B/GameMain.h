#pragma once
#include "AbstractScene.h"
#include "SelectStage.h"
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
#include "Boss.h"
#include "BossHands.h"
#include "Rock.h"
#include "Effect.h"
#include "LoadingScene.h"
#include "Score.h"
#include "SighBoard.h"
#include "HealItem.h"
#include "Koban.h"
#include "Jar.h"

class Player;

class GameMain :
    public AbstractScene
{
private:
    int old_stage;//前のステージ数　デバック用

    int now_stage;      //現在のステージ数
    bool game_over_flg;     //ゲームオーバーの条件を満たしたらフラグを立てる
    int STAGE_DATA[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];
    Player* player;                     //プレイヤーのオブジェクト
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];   //床のオブジェクト
    Attack* attack[ATTACK_NUM];     //攻撃のオブジェクト

    //エネミー
    Zakuro* zakuro[ZAKURO_MAX];    //ザクロ
    Himawari* himawari[HIMAWARI_MAX];//ひまわり
    Iruka* iruka[IRUKA_MAX];      //イルカ

    Boss* boss; //ボス
    BossHands* hands;//ボスの腕
    int Check_Num;
    Rock* rock[2];//岩

    Bamboo* bamboo[BAMBOO_MAX];
    SceneScroll* scene_scroll;  //スクロールクラスのオブジェクト

    PowerGauge* powergauge;  //強化ゲージのオブジェクト
    PlayerHP* playerhp;  //プレイヤーHPUIのオブジェクト
    HealItem* heal[ITEM_MAX];     //回復アイテム
    Koban* koban; //小判
    Score* score; //スコアUIのオブジェクト

    Jar* jar[JAR_MAX]; //壺

    Effect* effect;     //しぶきエフェクトのオブジェクト

    SelectStage* select_stage; //ステージ選択画面のオブジェクト
    Loading* loading_scene;    //LoadingSceneのオブジェクト

    SighBoard* sighboard[SIGH_BOARD_NUM];      //看板のオブジェクト

    int flg;               //
    int count[2];          //実験用
    int who;                //誰が攻撃したか判断する用
    
    int stage_width_num;    //ステージブロックの横数
    int stage_height_num;   //ステージブロックの縦数
    int stage_width;        //ステージ横幅
    bool camera_lock_flg;   //カメラが動けるか判断(強制戦闘時以外)
    bool lock_pos_set_once; //カメラのロック位置設定用
    Location lock_pos;      //カメラが動けない時に画面揺れが発生した時、カメラの位置が戻る場所
    int impact_timer;               //画面揺れ演出

    int item_rand;

    int lock_flg; //強制戦闘時のフラグ
    int vine_y;   //蔓のY座標
    int vine_x1;  //左の草のX座標
    int vine_x2;  //右の草のX座標
    int vine_img[2]; //蔓、草の画像
    int venemy_cnt;  //敵の生成時間カウント
    int venemy_num1; //強制戦闘時に生成した敵の数
    int venemy_num2; //強制戦闘時に斬った敵の数

public:
    bool Hands_Delete_Flg; //ボスの腕消す用

    //コンストラクタ(_stage＝読み込むステージ)
    GameMain(int _stage);
    //デストラクタ
    ~GameMain();

    // 描画以外の更新を実装
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //攻撃を発生させる(_location = 攻撃したプレイヤーor敵の中心座標  _direction = 攻撃する方向(0=右 1=左))
    void SpawnAttack(AttackData _attackdata);

    //各当たり判定(プレイヤーと床以外)の処理
    void HitCheck(GameMain* main);

    //プレイヤーと床の当たり判定処理
    void PlayerFloorHitCheck();

    //ステージファイルを読み込む
    void LoadStageData(int _stage);

    //次のステージへ遷移する
    void SetStage(int _stage);

    //カメラ座標の更新
    void CameraLocation(Location _location);

    //カメラ座標を初期地点に戻す
    void ResetCamera();

    //ボスにプレイヤーの座標を渡す用
    Location GetPlayerLocation();

    //カメラを揺らす用の変数を設定する(_power = 揺れている時間と強度)
    void ImpactCamera(int _power);

    //カメラの更新＆カメラを揺らす
    void UpdateCamera();

    //ゲームオーバーのフラグを立てる
    void SetGameOver() { game_over_flg = true; }
    //エネミーのPushを関数化
    template <class T>
    void ProcessCharacterCollision(T* character, Stage* stageObject, int index);
    //竹とエネミーの当たり判定
    template <class T>
    void HitBamboo(T* character);
    //エネミーの攻撃を受ける処理
    template <class T>
    void ProcessAttack(Attack* attack, T* character, Effect* effect/*,HealItem* heal, Koban* koban*/);
    //アイテムのランダム出現
    template<class T>
    void ItemSpwanRand(T* character);

    
    //蔓内での敵生成処理
    void VineEnemy(void);
};

