#pragma once
class LockPlayer
{
private:
    bool lock_flg; //�����퓬���̃t���O
    int grass_lx;  //���̑���X���W
    int grass_rx;  //�E�̑���X���W
    bool grass_flg;//���̃A�j���[�V�����t���O
    int img;    //���A���̉摜
    int enemy_cnt; //�G�̐������ԃJ�E���g
    int create_en; //���������G�̐�
    int attack_en; //�a�����G�̐�

public:
    //�R���X�g���N�^
    LockPlayer();

    //�f�X�g���N�^
    ~LockPlayer();

    //�X�V����
    void Update();

    //�`�揈��
    void Draw()const;

    //�v���C���[�������퓬�]�[���ɕ����߂��Ă��邩(true:���� false:���Ȃ�)
    void SetLockFlg(bool _flg) { lock_flg = _flg; }

    bool GetLockFlg() { return lock_flg; }
    bool GetGrassFlg() { return grass_flg; }


    //���������G�̐����J�E���g
    void CntCreateEn() { create_en++; }

    //�a�����G�̐����J�E���g
    void CntAttackEn() { attack_en++; }

    //���̃A�j���[�V����
    void GrassAnim();

};

