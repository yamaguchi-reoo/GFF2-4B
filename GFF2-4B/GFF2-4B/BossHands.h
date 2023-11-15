#pragma once
#include "CharaBase.h"
#include "Rock.h"

class Boss;


//ひまわりの状態
enum SunFlowerState {
    WAIT = 0,
    MOVE,
    DOWN
};

class BossHands :
    public CharaBase
{
private:
#define STOPBOSS (160)  //ボスが次の行動に行くまでの時間
#define IMGMAX (5)      //ボスの画像最大数
public:

    /*ザクロ拳*/
    //受け取った値によってCMYのサイズ変更用
    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int Hands_img[IMGMAX];
    int Hands_Img_num;//画像切り替え用
    int hi[3];

    //Mの拳が降りてくるX座標
    float Magentax[10] = { 1000,100,500 };

    /*イルカ*/
    int Direction;  //0:左向き 1:右向き

    int switching;//拳出現位置セット用

    bool hitflg=false;
    bool onceflg=true;
    int count;

    bool HitJumpAttack = false;//ジャンプ攻撃多段ヒット防止
    bool Death_Flg = false;//HPが0になったらON
    int Death_Anim;//死亡アニメーション切り替え用
    
    bool Power_Up;   //強化状態か？
    bool Rock_Once; //岩出現位置一度だけ格納する用
    Location turu_location;  //つる描画位置
    float turu_angle;        //つる角度
    int turu_img;            //つる画像用

    //ボスの状態が何か受け取る
    int Boss_Form;

    //どの腕を出すか用 0:マゼンタ 1:シアン 2:イエロー
    int Hands_who;

    int Attack_Num;//攻撃のデータどれ送るか識別用

    //ひまわり用
    SunFlowerState sf_state;
    bool pos;                //自分の現在地(false = 右、true = 左)
    float sf_speed;          //移動速度
    float angle_width;       //弾を撃つ方向決定用
    float angle_height;      //弾を撃つ方向決定用
    float rad;               //計算用
    float face_angle;        //顔の角度
    float move_angle;        //移動の角度
    float bullet_angle;      //弾の角度
    float acceleration;      //移動の加速度
    int timer;               //各モーションの時間
    int attack_cd;           //弾を撃つ頻度
    int attack_combo;        //弾を連続で撃つ用
    int attack_num;          //弾を連続で撃つ用
    int move_count;          //何回移動したかを測定する     

    BossHands(int _who);
    BossHands(int _who,Boss* boss);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void HandsCyan(GameMain* main);
    void HandsYellow(GameMain* main);

    void ApplyDamage(int num);
    float GetHandsY() { return location.y; };
    float GetHandsX() { return location.x; };

    //反射した壁に応じて、反射した時の角度をランダムに決定する
    float GetRandAngle(int _wall);
};

