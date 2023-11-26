#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;

//ひまわりの状態
enum BossHimawariState {
    SF_WAIT = 0,
    SF_MOVE,
    SF_DOWN
};

//いるかの状態
enum BossIrukaState {
    D_WAIT = 0,
    D_MOVE,
    D_RISE,
    D_DASH,
    D_DOWN
};

//ザクロの状態
enum BossZakuroState {
    Z_ANIM_UP=0,
    Z_ANIM_FALLING,
    Z_ANIM_DEAD,
    Z_MOVE,
    Z_JUMP_RIGHT,
    Z_JUMP_LEFT,
    Z_FALLING
};

class BossHands :
    public CharaBase
{
private:
#define STOPBOSS (160)  //ボスが次の行動に行くまでの時間
#define IMGMAX (5)      //ボスの画像最大数
public:
    //全腕共通で使う
    int frame;                      //何フレーム経ったか保存する用
    int Hands_who;                  //どの腕を出すか用 0:マゼンタ 1:シアン 2:イエロー
    int Attack_Num;                 //攻撃のデータどれ送るか識別用
    bool Death_Flg = false;         //HPが0になったらON
    int Death_Anim;                 //死亡アニメーション切り替え用
    int Boss_Form;                  //ボスの状態が何か受け取る
    bool HitJumpAttack = false;     //ジャンプ攻撃多段ヒット防止
    bool Power_Up;                  //強化状態か？
    int Hands_Img_num;              //画像切り替え用

    /*ザクロ拳*/
    //受け取った値によってCMYのサイズ変更用
    BossZakuroState zakuro_state;
    int hands_height[3] = { 360,190,190 };
    int hands_width[3] = { 360,190,190 };
    int Hands_img[IMGMAX];
    int Zakuro_img[IMGMAX];

    int Zakuro_Imgnum;//ザクロの画像切り替え用
    int Zakuro_Direction;//ザクロの向き　右:0 左:1
    float Magentax[10] = { 1000,100,500 };    //Mの拳が降りてくるX座標
    int switching;                  //拳出現位置セット用
    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Rock_Once;                 //岩出現位置一度だけ格納する用

    //ザクロジャンプ用
    float Zakuro_Movex;    //移動したザクロｘ
    float Zakuro_Movey;    //移動したザクロｙ
    float Set_Zakuro_x;   //ザクロジャンプ開始位置格納用
    float Set_Zakuro_y;   //ザクロジャンプ開始位置格納用
    float time;
    float g;//重力加速度
    float sita; //角度θ
    float V_zero; //初速度ｖ０
    float pi = 3.1415f;
    

    //いるか
    BossIrukaState iruka_state;     //いるかの状態
    Location turu_location;         //つる描画位置
    bool rare_flg;                  //没挙動を低確率でする
    float iruka_rad;                //いるかの角度計算用
    float turu_angle;               //つる角度
    float turu_rad;                 //つるの描画角度計算用
    int turu_img;                   //つる画像用
    int ref_num;                    //いるかが壁に跳ね返った回数
    int tackle_num;                 //いるかが攻撃した回数

    //ひまわり
    BossHimawariState hima_state;        //ひまわりの状態
    bool pos;                       //自分の現在地(false = 右、true = 左)
    float sf_speed;                 //移動速度
    float angle_width;              //弾を撃つ方向決定用
    float angle_height;             //弾を撃つ方向決定用
    float rad;                      //計算用
    float move_angle;               //移動の角度
    float bullet_angle;             //弾の角度
    int attack_cd;                  //弾を撃つ頻度
    int attack_combo;               //弾を連続で撃つ用
    int attack_num;                 //弾を連続で撃つ用
    int move_count;                 //何回移動したかを測定する   

    //いるかひまわり共用
    float acceleration;             //移動の加速度
    float face_angle;               //顔の角度
    int timer;                      //各モーションの時間

    BossHands(int _who);
    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);

    //マゼンタ（ザクロ）用関数
    void MagentaInit();                     //マゼンタ（ザクロ）で使う変数初期化
    void HandsMagenta(GameMain* main);      //マゼンタ（ザクロ）の更新

    //シアン（イルカ）用関数
    void CyanInit();                        //シアン（イルカ）で使う変数初期化
    void HandsCyan(GameMain* main);         //シアン（イルカ）の更新
    float GetRandAngle(int _wall);          //反射した壁に応じて、反射した時の角度をランダムに決定する

    //イエロー（ひまわり）用関数
    void YellowInit();                      //イエロー（ひまわり）で使う変数初期化
    void HandsYellow(GameMain* main);       //イエロー（ひまわり）の更新


    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };
};

