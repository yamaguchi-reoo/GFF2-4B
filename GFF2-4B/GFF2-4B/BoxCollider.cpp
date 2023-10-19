#include <math.h>
#include "BoxCollider.h"

int BoxCollider::HitBox(BoxCollider* bCollider)
{
	//bool ret = 0; //�Ԃ�l

	////�����̓����蔻��͈̔�
	//float my_x[2]{ 0,0 };
	//float my_y[2]{ 0,0 };

	////����̓����蔻��͈̔�
	//float sub_x[2]{ 0,0 };
	//float sub_y[2]{ 0,0 };

	////�����̓����蔻��͈̔͂̌v�Z
	//my_x[0] = location.x;
	//my_y[0] = location.y;
	//my_x[1] = my_x[0] + erea.width;
	//my_y[1] = my_y[0] + erea.height;

	////����̓����蔻��͈̔͂̌v�Z
	//sub_x[0] = bCollider->GetLocation().x;
	//sub_y[0] = bCollider->GetLocation().y;
	//sub_x[1] = sub_x[0] + bCollider->GetErea().width;
	//sub_y[1] = sub_y[0] + bCollider->GetErea().height;

	////StageFloor�̉��͈͓̔�
	//if (my_x[0] < sub_x[1] &&
	//	sub_x[0] < my_x[1])
	//{
	//	//Player��StageFloor��艺�֍s�����Ƃ����ꍇ
	//	if (my_y[1] > sub_y[0] &&
	//		my_y[0] < sub_y[0])
	//	{
	//		ret = 1;
	//	}

	//	//Player��StageFloor����֍s�����Ƃ����ꍇ
	//	if (my_y[0] < sub_y[1] &&
	//		my_y[1] > sub_y[1])
	//	{
	//		ret = 2;
	//	}
	//}

	////StaegFloor�̏c�͈͓̔�
	//if (my_y[0] < sub_y[1] &&
	//	sub_y[0] < my_y[1])
	//{
	//	//Player��StageFloor���E�֍s�����Ƃ����ꍇ
	//	if (my_x[1] > sub_x[0] &&
	//		my_x[0] < sub_x[0])
	//	{
	//		ret = 4;
	//	}
	//	//Player��StageFloor��荶�֍s�����Ƃ����ꍇ
	//	if (my_x[0] < sub_x[1] &&
	//		my_x[1]>sub_x[1])
	//	{
	//		ret = 3;
	//	}
	//}

	//return ret;
	int ret = 0;

	//�����̍�����W
	float my_x = location.x;
	float my_y = location.y;
	//�����̒������W
	float my_cx = my_x + (erea.width / 2);
	float my_cy = my_y + (erea.height / 2);
	//�����̕��ƍ����̔���
	float my_harf_width = erea.width / 2;
	float my_harf_height = erea.height / 2;

	//����̍�����W
	float sub_x = bCollider->GetLocation().x;
	float sub_y = bCollider->GetLocation().y;
	//����̒������W
	float sub_cx = sub_x + (bCollider->GetErea().width / 2);
	float sub_cy = sub_y + (bCollider->GetErea().height / 2);
	//����̕��ƍ����̔���
	float sub_harf_width = bCollider->GetErea().width / 2;
	float sub_harf_height = bCollider->GetErea().height / 2;

	//�����Ƒ���̒��S���W�̍�
	float diff_x = my_cx - sub_cx;
	float diff_y = my_cy - sub_cy;

	//�����蔻��̉��Z
	if (fabsf(diff_x) < my_harf_width + sub_harf_width &&
		fabsf(diff_y) < my_harf_height + sub_harf_height)
	{
		if (diff_y < -sub_harf_height)
		{
			ret = 1;
		}
		else
		{
			ret = 2;
		}
		//�����Ƒ���̒��SY���W�̍������ȓ��{�����Ƒ���̒��SX���W���{�Ȃ獶�̕ǂɓ������Ă���Ƃ�������
		//if (diff_y < sub_harf_height)
		//{
		//	ret = 3;
		//}
	}
	return ret;
}

//���S���W�̎擾
Location BoxCollider::GetLocation()const
{
	return location;
}

//���a�̎擾
Erea BoxCollider::GetErea()const
{
	return erea;
}

//���S���W�̐ݒ�
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}