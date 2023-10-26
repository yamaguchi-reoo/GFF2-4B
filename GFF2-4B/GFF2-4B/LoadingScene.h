#pragma once
#include "AbstractScene.h"
#include "GameMain.h"

class Loading :public AbstractScene
{
private:
	int loading_image;		//�Ǎ��p�摜

	int loading_time;		//�Ǎ����ԗp�ϐ�

public:
	//�R���X�g���N�^
	Loading();
	//�f�X�g���N�^
	~Loading();

	//�`��ȊO�̍X�V������
	AbstractScene* Update()override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const override;
};