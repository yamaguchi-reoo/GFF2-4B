#pragma once
#include "AbstractScene.h"

class Loading :public AbstractScene
{
private:
	int loading_image;		//�Ǎ��p�摜
	int loading_time;		//�Ǎ����ԗp�ϐ�
	int loading_mark_time;	//�E(�����_)�҂����ԗp�ϐ�
	//int load_mark_image;	//�Ǎ����L���\���p�ϐ�

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