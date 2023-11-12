#pragma once
#include "BoxCollider.h"

class GameMain;
class BossHands;

class Rock :
    public BoxCollider
{
private:
    //Mの拳が降りてくるX座標
    float Rock_X[10] = { 1000,100,500,600 };


    float Rock_Movex;    //移動した岩ｘ
    float Rock_Movey;    //移動した岩ｙ
    float Set_Rock_x;   //X座標出現位置格納用
    float Set_Rock_y;   //Y座標出現位置格納用
    int Rock_img;  //岩画像
    float timer;
    float g;//重力加速度
    float sita; //角度θ
    float V_zero; //初速度ｖ０

    int Set_xnum;//岩出現座標受け取り
    
    BossHands* hands;

public:
    bool Rock_Delete;//岩を消す用

    Rock(int _who,int Set_Xnum);
    ~Rock();

    void Update(GameMain* main);     //更新処理
    void Draw() const; //描画処理
    AttackData RockAttactData();
    void RockAttack(GameMain* main);
};

