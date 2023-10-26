#pragma once
#include "CharaBase.h"
class Himawari :
    public CharaBase
{
private:

    bool direction;					//��̌���(0=�E���� 1=������)
    int attack_interval_count;

public:
    //�R���X�g���N�^
    Himawari();
    //�f�X�g���N�^
    ~Himawari();

    void Update(GameMain* main)override;
    void Draw()const override;

    AttackData CreateAttactData();

    void Attack(GameMain* main);
    
};

