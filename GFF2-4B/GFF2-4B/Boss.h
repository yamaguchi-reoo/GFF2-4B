#pragma once
#include "CharaBase.h"
class Boss :
    public CharaBase
{
private:
    int Boss_MainBody[10];//�{�X�{�̂̉摜
    int Boss_MainArm[10];//�{�X�{�̘r�̉摜
    int Explosion[10];//����

    enum bosshand
    {
    };

public:
    int Count_Death;//�r��������ꂽ���J�E���g�p
    int Boss_Form;//���ǂ̌`�Ԃ� 0:���`�� 1:���`�� 3:�ŏI�`��
    int Boss_Check_Playerx;//�v���C���[�����ǂ����ɋ��邩 0:�E�� 1:������ 2:����

    int timer;  //�e���[�V�����̎���

    int Boss_Arm_Rightx; //�E�rX���W
    int Boss_Arm_Righty; //�E�rY���W

    bool New_Hand_Flg;//�{�X�̎�𔭐�������p

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
    void BossImgChange();

};

