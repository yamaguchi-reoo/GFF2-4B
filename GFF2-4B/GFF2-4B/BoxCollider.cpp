#include "BoxCollider.h"

int BoxCollider::HitBox(BoxCollider* bCollider)
{
	bool ret = 0; //�Ԃ�l

	//�����̓����蔻��͈̔�
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//����̓����蔻��͈̔�
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + erea.width;
	my_y[1] = my_y[0] + erea.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = bCollider->GetLocation().x;
	sub_y[0] = bCollider->GetLocation().y;
	sub_x[1] = sub_x[0] + bCollider->GetErea().width;
	sub_y[1] = sub_y[0] + bCollider->GetErea().height;

	//StageFloor�̉��͈͓̔�
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//Player��StageFloor��艺�֍s�����Ƃ����ꍇ
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			return 1;
		}

		//Player��StageFloor����֍s�����Ƃ����ꍇ
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			return 2;
		}
	}

	//StaegFloor�̏c�͈͓̔�
	else if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//Player��StageFloor���E�֍s�����Ƃ����ꍇ
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			return 4;
		}
		//Player��StageFloor��荶�֍s�����Ƃ����ꍇ
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			return 3;
		}
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