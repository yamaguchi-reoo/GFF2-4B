#pragma once
#include "AbstractScene.h"
#include "DxLib.h"

class Credit :public AbstractScene
{
private:

	int credit_timer;

public:
	//�R���X�g���N�^
	Credit();

	//�f�X�g���N�^
	~Credit();

	//�`��ȊO�̍X�V������
	AbstractScene* Update()override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const override;
};