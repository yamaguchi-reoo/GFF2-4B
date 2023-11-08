#pragma once
#include "AbstractScene.h"
class GameOver :
    public AbstractScene
{
private:
public:

    GameOver();
    ~GameOver();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

