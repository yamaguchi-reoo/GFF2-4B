#pragma once
#include "AbstractScene.h"

class Result :public AbstractScene
{
private:
	int score; //�X�R�A
	int draw_score; //�`��p�X�R�A
	int score_img[2];//�摜�p�ϐ�
	int num_img[10]; //�����摜�p�ϐ�

public:
	//�R���X�g���N�^
	Result();

	//�f�X�g���N�^
	~Result();

	// �`��ȊO�̍X�V������
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};
