#pragma once
#include "BoxCollider.h"
class Vine :public BoxCollider
{
private:
	bool vine_flg; //���̃A�j���[�V�����t���O
	int img;       //���̉摜

public:
	//�R���X�g���N�^(����:�\������X���W)
	Vine(int x);

	//�f�X�g���N�^
	~Vine();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw()const;

	//�v���C���[�������퓬�]�[���ɕ����߂��Ă��邩(true:���� false:���Ȃ�)
	bool GetVineFlg() { return vine_flg; }

	//���̃A�j���[�V����(��������)
	void VineAnimStart();

	//���̃A�j���[�V����(�ォ�牺��)
	void VineAnimEnd();
};

