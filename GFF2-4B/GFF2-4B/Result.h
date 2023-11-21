#pragma once
#include "AbstractScene.h"
#define PI    3.1415926535897932384626433832795f

class Result :public AbstractScene
{
private:
	int score; //�X�R�A
	int draw_score; //�`��p�X�R�A
	int img[8];//�摜�p�ϐ�
	int num_img[10]; //�����摜�p�ϐ�
	int x1,x2; //�����A�j���[�V�����p
	int anim_flg; //�����A�j���[�V�����p
	int zakuro_num; //�a�����U�N���̐�
	int iruka_num;  //�a�����C���J�̐�
	int himawari_num; //�a�����q�}�����̐�

public:
	//�R���X�g���N�^
	Result();

	//�f�X�g���N�^
	~Result();

	// �`��ȊO�̍X�V������
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

	//�����̃A�j���[�V����
	void AnimMakimono(void);

	
};
