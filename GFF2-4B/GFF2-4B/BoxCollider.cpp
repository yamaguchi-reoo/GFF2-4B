#include "BoxCollider.h"

//BoxCollider�Ƃ̓����蔻��
bool BoxCollider::HitBox(BoxCollider* bCollider)
{
	bool ret = false; //�Ԃ�l

	//�����̓����蔻��͈̔�
	float mx1 = location.x;
	float my1 = location.y;
	float mx2 = mx1 + erea.width;
	float my2 = my1 + erea.height;

	//����̓����蔻��͈̔�
	float px1 = bCollider->GetLocation().x;
	float py1 = bCollider->GetLocation().y;
	float px2 = px1 + bCollider->GetErea().width;
	float py2 = py1 + bCollider->GetErea().height;

	if ((mx1 < px2) && (px1 < mx2) && (my1 < py2) && (py1 < my2)) //�����蔻��
	{
		ret = true;
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