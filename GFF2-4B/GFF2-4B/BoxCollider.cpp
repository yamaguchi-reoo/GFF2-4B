#include "BoxCollider.h"

int BoxCollider::HitBox(BoxCollider* bCollider)
{
	bool ret = 0; //返り値

	//自分の当たり判定の範囲
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//相手の当たり判定の範囲
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + erea.width;
	my_y[1] = my_y[0] + erea.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = bCollider->GetLocation().x;
	sub_y[0] = bCollider->GetLocation().y;
	sub_x[1] = sub_x[0] + bCollider->GetErea().width;
	sub_y[1] = sub_y[0] + bCollider->GetErea().height;

	//StageFloorの横の範囲内
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//PlayerがStageFloorより下へ行こうとした場合
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			return 1;
		}

		//PlayerがStageFloorより上へ行こうとした場合
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			return 2;
		}
	}

	//StaegFloorの縦の範囲内
	else if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//PlayerがStageFloorより右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			return 4;
		}
		//PlayerがStageFloorより左へ行こうとした場合
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			return 3;
		}
	}

	return ret;
}

//中心座標の取得
Location BoxCollider::GetLocation()const
{
	return location;
}

//半径の取得
Erea BoxCollider::GetErea()const
{
	return erea;
}

//中心座標の設定
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}