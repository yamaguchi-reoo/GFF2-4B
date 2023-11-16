#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    bool disp_flg;  //チュートリアルを出すか判断
    int disp_type;  //どの看板を出すか判断
    int sb_img[4];     //看板画像格納用
public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();
    void Update(Location _player_location);
    void Draw()const;
};


