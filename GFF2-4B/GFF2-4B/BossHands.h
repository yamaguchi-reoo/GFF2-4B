#pragma once
#include "CharaBase.h"
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
    int hi[3];
    int bosf[3];

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

    BossHands(int _who);
    ~BossHands();


    void Update(GameMain* main)override;
    void Draw()const override;
    
    AttackData BossAttactData();
    void BossAttack(GameMain* main);
    void HandsMagenta(GameMain* main);

    void ApplyDamage(int num);
};

