#include "Result.h"
#include "SelectStage.h"
#include "Dxlib.h"

Result::Result()
{
}

Result::~Result()
{
}

// �`��ȊO�̍X�V������
AbstractScene* Result::Update()
{
	return this;
}

//�`��Ɋւ��邱�Ƃ�����
void Result::Draw() const
{
	DrawFormatString(0, 0, 0xffffff, "���U���g���");
}