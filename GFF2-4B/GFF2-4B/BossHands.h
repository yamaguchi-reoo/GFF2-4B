#pragma once
#include "CharaBase.h"

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

    //受け取った値によってCMYのサイズ変更用
    int hands_height[3] = { 190,190,190 };
    int hands_width[3] = { 190,190,190 };

    int Hands_img[IMGMAX];

    //Mの拳が降りてくるX座標
    int Magentax[10] = { 1000,100,500 };

    int switching;

    int bhandx;
    int bhandy;
    int down_hand;

    bool hitflg=false;
    bool onceflg=true;
    int count;
    bool Hit_Once;

    int Attack_Num;//ボスの手が今何の攻撃しているか

    //ひまわり用
    SunFlowerState sf_state;
    bool pos;                //自分の現在地(false = 右、true = 左)
    float sf_speed;          //移動速度
    float angle_width;       //弾を撃つ方向決定用
    float angle_height;      //弾を撃つ方向決定用
    float move_angle;        //移動の角度
    float bullet_angle;      //弾の角度
    float acceleration;      //移動の加速度
    int timer;               //各モーションの時間
    int attack_cd;           //弾を撃つ頻度

    BossHands(int _who);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);
    void HandsYellow(GameMain* main);

    void ApplyDamage(int num);
};

