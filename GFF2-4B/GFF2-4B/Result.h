#pragma once
#include "AbstractScene.h"

class Result :public AbstractScene
{
private:

public:
	Result();

	~Result();

	// �`��ȊO�̍X�V������
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

};

