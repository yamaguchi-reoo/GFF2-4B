#include "Scroll.h"

SceneScroll::SceneScroll()
{
	stage_image = LoadGraph("resource/images/SampleStage2.png");
	try
	{
		if (stage_image == -1)
		{
			throw"resource/images/SampleStage2.png";
		}
	}
	catch (int& err)
	{
		printf("�G���[�R�[�h%d\n", err);
	}

	scroll_x = 0.0;		//�w�i�摜�̍��㒸�_����X���W
	scroll_y = 0.0;		//�w�i�摜�̍��㒸�_����Y���W
}
SceneScroll::~SceneScroll()
{
}
void SceneScroll::Update(Location player, float acs_l, float acs_r)
{
	//���X�N���[��
	if (player.x <= LEFT_END && scroll_x >= 0.01)
	{
		scroll_x += 6.0;
		ActionRangeBorder(player);
	}
	//�E�X�N���[��
	if (player.x >= RIGHT_END)
	{
		scroll_x -= 6.0;
		ActionRangeBorder(player);
	}
	PlayerScroll(player);
}
void SceneScroll::Draw()
{
	DrawGraph((int)scroll_x, 0, stage_image, FALSE);
}
ScrollData SceneScroll::PlayerScroll(Location player)
{
	ScrollData scroll_data{};
	if (player.x <= LEFT_END + 1)
	{
		//�X�N���[����������X���W�̍��[�Ƀv���C���[�����������ꍇ�A���W�������x�����ɂ���
		scroll_data.direction = true;
		scroll_data.move += 0.01;
	}
	if (player.x >= RIGHT_END + 1)
	{
		//�X�N���[����������X���W�̉E�[�Ƀv���C���[�����������ꍇ�A���W�������x�����ɂ���
		scroll_data.direction = false;
		scroll_data.move += 0.01;
	}
	return scroll_data;
}
int SceneScroll::ActionRangeBorder(Location player)
{
	if (player.x <= LEFT_END || player.x >= RIGHT_END)
	{
		return true;
	}
	else
	{
		return false;
	}
}