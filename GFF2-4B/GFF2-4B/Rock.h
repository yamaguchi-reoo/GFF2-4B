#pragma once
#include "BoxCollider.h"

class GameMain;

class Rock :
    public BoxCollider
{
private:
    float Rock_x;    //岩ｘ
    float Rock_y;    //岩ｙ
    float Rock_Movex;    //岩ｘ
    float Rock_Movey;    //岩ｙ
    float Set_Rock_x;   //X座標出現位置格納用
    float Set_Rock_y;   //Y座標出現位置格納用
    int Rock_img;  //岩画像
    float timer;
    float g;//重力加速度
    float sita; //角度θ
    float V_zero; //初速度ｖ０

    int who;

public:
    Rock(int _who,float x,float y);
    ~Rock();

    void Update(GameMain* main);     //更新処理
    void Draw() const; //描画処理
    AttackData RockAttactData();
    void RockAttack(GameMain* main);
    float GetRockx() { return Rock_x; };
    float GetRocky() { return Rock_y; };
};

