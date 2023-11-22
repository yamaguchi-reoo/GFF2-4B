#include "Vine.h"

//�R���X�g���N�^
Vine::Vine(int x)
{
	location.x = x;
	location.y = 0;
	erea.height = 650;
	erea.width = 120;
	vine_flg = false;
	img = LoadGraph("resource/images/KUKYOTR.png");
}

//�f�X�g���N�^
Vine::~Vine()
{
}

//�X�V����
void Vine::Update()
{
	////���̃A�j���[�V����
	//if (vine_flg == false)
	//{//�͂���
	//	VineAnimStart();
	//}
	//else
	//{//�����
	//	VineAnimEnd();
	//}

}

//�`�揈��
void Vine::Draw() const
{
	//��
	DrawGraph(local_location.x, local_location.y, img, TRUE);
}

//���̃A�j���[�V����(��������)
void Vine::VineAnimStart()
{
	//����������͂₷
	if (location.y > 70)
	{
		location.y -= 35;
	}
	else
	{
		vine_flg = true;
	}
}

//���̃A�j���[�V����(�ォ�牺��)
void Vine::VineAnimEnd()
{
	if(location.y > 1290)
	{
		location.y += 35;
	}
	else
	{
		vine_flg = false;
	}
}