#pragma once
#include "AbstractScene.h"
#include "DxLib.h"

class Credit :public AbstractScene
{
private:

	int end_roll01_image;
	int end_roll02_image;
	int end_roll03_image;
	int end_roll04_image;
	int end_roll05_image;
	int end_roll_makimono;
	int credit_navigation;

	int credit_timer;

	int credit_alpha;

	int alpha_sub_flg;

public:
	//�R���X�g���N�^
	Credit();

	//�f�X�g���N�^
	~Credit();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update()override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const override;

	void ImageLoad(int& _handle, const char* _file_name);
};