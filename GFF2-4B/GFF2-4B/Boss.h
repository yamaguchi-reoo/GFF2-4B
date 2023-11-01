#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:

public:
    Boss();
    ~Boss();

    void Update(GameMain* main)override;
    void Draw()const override;

};

