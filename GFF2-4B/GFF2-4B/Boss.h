#pragma once
#include "CharaBase.h"
#include "GameMain.h"

//�{�X�{�̂̏��
enum BossState {
    Boss_M=0,
    Boss_C,
    Boss_Y,
};

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
    int Bossbody_ImgNum;//�v���C���[�����ǂ����ɋ��邩 0:�E�� 1:������ 2:����

    int timer;  //�e���[�V�����̎���
    int Explosion_ImgNum;//�����摜�؂�ւ��p
    int Expl_count;//

    float Boss_Arm_Rightx; //�E�rX���W
    float Boss_Arm_Righty; //�E�rY���W
    float Boss_Arm_Leftx; //���rX���W
    float Boss_Arm_Lefty; //���rY���W

    float Boss_Body_X; //�{��X���W
    float Boss_Body_Y; //�{��Y���W

    float Explosion_X;
    float Explosion_Y;
    int Excount;

    int Hand_Num;
    bool New_Hand_Flg;//�{�X�̎�𔭐�������p
    int Boss_state;
    int Boss_step;
    bool Once_Flg;
    int Boss_Handmove;//�{�X�̎�����Ƃ��̓����p
    bool Boss_Dieflg;//�{�X�{�̂����ʂƂ���true

    Boss();
    ~Boss();

    

    void Update(GameMain* main)override;
    void Draw()const override;
    int GetBossForm() { return Boss_Form; };
    void BossImgChange(GameMain* main);
    void Boss_MakeHand();
    void ExplosionAnim();
};
