#include <math.h>
#include "BoxCollider.h"

int BoxCollider::HitBox(BoxCollider* bCollider)
{
	//bool ret = 0; //返り値

	////自分の当たり判定の範囲
	//float my_x[2]{ 0,0 };
	//float my_y[2]{ 0,0 };

	////相手の当たり判定の範囲
	//float sub_x[2]{ 0,0 };
	//float sub_y[2]{ 0,0 };

	////自分の当たり判定の範囲の計算
	//my_x[0] = location.x;
	//my_y[0] = location.y;
	//my_x[1] = my_x[0] + erea.width;
	//my_y[1] = my_y[0] + erea.height;

	////相手の当たり判定の範囲の計算
	//sub_x[0] = bCollider->GetLocation().x;
	//sub_y[0] = bCollider->GetLocation().y;
	//sub_x[1] = sub_x[0] + bCollider->GetErea().width;
	//sub_y[1] = sub_y[0] + bCollider->GetErea().height;

	////StageFloorの横の範囲内
	//if (my_x[0] < sub_x[1] &&
	//	sub_x[0] < my_x[1])
	//{
	//	//PlayerがStageFloorより下へ行こうとした場合
	//	if (my_y[1] > sub_y[0] &&
	//		my_y[0] < sub_y[0])
	//	{
	//		ret = 1;
	//	}

	//	//PlayerがStageFloorより上へ行こうとした場合
	//	if (my_y[0] < sub_y[1] &&
	//		my_y[1] > sub_y[1])
	//	{
	//		ret = 2;
	//	}
	//}

	////StaegFloorの縦の範囲内
	//if (my_y[0] < sub_y[1] &&
	//	sub_y[0] < my_y[1])
	//{
	//	//PlayerがStageFloorより右へ行こうとした場合
	//	if (my_x[1] > sub_x[0] &&
	//		my_x[0] < sub_x[0])
	//	{
	//		ret = 4;
	//	}
	//	//PlayerがStageFloorより左へ行こうとした場合
	//	if (my_x[0] < sub_x[1] &&
	//		my_x[1]>sub_x[1])
	//	{
	//		ret = 3;
	//	}
	//}

	//return ret;
	int ret = 0;

	//自分の左上座標
	float my_x = location.x;
	float my_y = location.y;
	//自分の中央座標
	float my_cx = my_x + (erea.width / 2);
	float my_cy = my_y + (erea.height / 2);
	//自分の幅と高さの半分
	float my_harf_width = erea.width / 2;
	float my_harf_height = erea.height / 2;

	//相手の左上座標
	float sub_x = bCollider->GetLocation().x;
	float sub_y = bCollider->GetLocation().y;
	//相手の中央座標
	float sub_cx = sub_x + (bCollider->GetErea().width / 2);
	float sub_cy = sub_y + (bCollider->GetErea().height / 2);
	//相手の幅と高さの半分
	float sub_harf_width = bCollider->GetErea().width / 2;
	float sub_harf_height = bCollider->GetErea().height / 2;

	//自分と相手の中心座標の差
	float diff_x = my_cx - sub_cx;
	float diff_y = my_cy - sub_cy;

	//当たり判定の演算
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
		//自分と相手の中心Y座標の差が一定以内＋自分と相手の中心X座標が＋なら左の壁に当たっているということ
		//if (diff_y < sub_harf_height)
		//{
		//	ret = 3;
		//}
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