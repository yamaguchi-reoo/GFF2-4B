#pragma once
#include "BoxCollider.h"

class SighBoard :
    public BoxCollider

{
private:
    bool disp_flg;  //チュートリアルを出すか判断
    int disp_type;  //どの看板を出すか判断
public:
    //コンストラクタ
    SighBoard(float pos_x, float pos_y,int type);
    //デストラクタ
    ~SighBoard();
    void Update(Location _player_location);
    void Draw()const;
};


